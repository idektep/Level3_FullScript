#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

#include <ESPAsyncWebSrv.h>
#include <esp_now.h> 

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

//-----------------------------------------------Network & ESP-NOW Setup--------------------------------------//

const char *ssid = "______________";
const char *password = "______________";

// !!! เปลี่ยนตรงนี้เป็น MAC Address ของบอร์ดตัวบน (Robot Arm) !!!
uint8_t broadcastAddress[] = {0x94, 0x54, 0xC5, 0x75, 0xB3, 0xA4}; 

//-----------------------------------------------------------------------------------------------------------//

typedef struct struct_message {
  char command[15];
} struct_message;
struct_message myData;
esp_now_peer_info_t peerInfo;
// -------------------------------------------------------- //

#define DHTPIN 23  
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  

#define Buzzer_Pin 18
#define LDR_Pin 34
int LDR_input = 0, lcd_mode = 0;
float temp, humi, ldr;
bool alarm_state = 0;

////////////////////////edit Parameter//////////////
int light_alarm = 400;  
int temp_alarm = 35;    

unsigned long previousMillis1 = 0, previousMillis2 = 0;
const long lcd_refresh = 1000;

const int TrigPin = 5;   
const int EchoPin = 35;  
long duration, Ultra;

int countFlag = 0;
int LA_V, LB_V, RA_V, RB_V;

//--------------------------------------Define AGV------------------------------------------//
#define UP 1
#define DOWN 2
#define UP_LEFT 5
#define UP_RIGHT 6
#define DOWN_LEFT 7
#define DOWN_RIGHT 8
#define TURN_LEFT 9
#define TURN_RIGHT 10
#define STOP 0
#define ON_BUZZER 11
#define OFF_BUZZER 12

#define R_ENA 15  
#define R_ENB 2   
#define L_ENA 19  
#define L_ENB 4   

#define LED_R 16
#define LED_L 17

#define MR_IN1 12 
#define MR_IN2 13 
#define MR_IN3 32 
#define MR_IN4 33 

#define ML_IN1 27 
#define ML_IN2 14 
#define ML_IN3 25 
#define ML_IN4 26 

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

String LCDtext0 = "IDEKTEP Lv.3";       
String LCDtext1 = "Test";  

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void setUpPinModes(){
  pinMode(LED_L, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(MR_IN1, OUTPUT);
  pinMode(MR_IN2, OUTPUT);
  pinMode(MR_IN3, OUTPUT);
  pinMode(MR_IN4, OUTPUT);
  pinMode(ML_IN1, OUTPUT);
  pinMode(ML_IN2, OUTPUT);
  pinMode(ML_IN3, OUTPUT);
  pinMode(ML_IN4, OUTPUT);
  pinMode(L_ENA, OUTPUT);
  pinMode(L_ENB, OUTPUT);
  pinMode(R_ENA, OUTPUT);
  pinMode(R_ENB, OUTPUT);
}

void initWiFi() {
  Serial.print("Setting AP (Access Point)…");
  WiFi.mode(WIFI_AP_STA); 
  WiFi.softAP(ssid, password);
  Serial.println(ssid);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  digitalWrite(2, HIGH);
}

void setup(void) {
  Serial.begin(115200);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  
  initWiFi();
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  setUpPinModes();
  stop(); 

  dht.begin();
  lcd.init();
  lcd.display();    
  lcd.backlight();  
  lcd.clear();      
  pinMode(Buzzer_Pin, OUTPUT);
  pinMode(LDR_Pin, INPUT);
  digitalWrite(Buzzer_Pin, LOW);
  lcd.noBacklight();
  
  adjectMotorSpeed(255, 255, 255, 255);

  setupWebServer();
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  sensor_fn(); 
  lcd_fn();
  ws.cleanupClients();
}