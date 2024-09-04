#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebSrv.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN 23  //pin DHT 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 0x27 or 0x3F 

#define Buzzer_Pin 18
#define LDR_Pin 34
int LDR_input = 0, lcd_mode = 0;
float temp, humi, ldr;
bool alarm_state = 0;
Adafruit_PWMServoDriver idektep = Adafruit_PWMServoDriver(0x40);
#define SERVOMIN 100
#define SERVOMAX 600

//-----------------------------------------------Set your device name and password.--------------------------------------//
const char *ssid = "IDEKTEP Lv.3";
const char *password = "88888888";
//-----------------------------------------------------------------------------------------------------------------------//

////////////////////////edit Parameter//////////////
int light_alarm = 400;  //*****แก้ระดับแสง
int temp_alarm = 35;    //******แก้อุณหภูมิ

unsigned long previousMillis1 = 0, previousMillis2 = 0;
const long lcd_refresh = 1000;

const int TrigPin = 5;   // Connect the trigger pin of first Ultrasonic sensor to Pin 34 of arduino
const int EchoPin = 35;  // Connect the eco pin of first Ultrasonic sensor to Pin 35 of arduino
long duration, Ultra;

//------------------------------Define address PCA Drive robot arm-----------------------------------//
#define servo1 0
#define servo2 1
#define servo3 2
#define servo4 3
#define servo5 4
#define servo6 5

int countFlag = 0;
const char *hold_flag = "99";

int delay_value = 10;
int Home = 0;  //Home
int poscountmax = 180;

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
int pos6 = 0;

int LA_V;
int LB_V;
int RA_V;
int RB_V;

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

#define R_ENA 15  //Adjust speed  //motor1
#define R_ENB 2   //Adjust speed //motor2
#define L_ENA 19  //Adjust speed //motor4
#define L_ENB 4   //Adjust speed //motor3

#define LED_R 16
#define LED_L 17

#define MR_IN1 12 //motor1
#define MR_IN2 13 //motor1
#define MR_IN3 32 //motor2
#define MR_IN4 33 //motor2

#define ML_IN1 27 //motor4
#define ML_IN2 14 //motor4
#define ML_IN3 25 //motor3
#define ML_IN4 26 //motor3

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
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
  stop();
}

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

//////////////////////////////////////////////////////
String LCDtext0 = "Test";       //16 charactor ข้อความบรรทัด0
String LCDtext1 = "88888888";  //16 charactor ข้อความบรรทัด1
//////////////////////////////////////////////////////////

void setup(void) {
  setUpPinModes();
  Serial.begin(115200);
  idektep.begin();
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  idektep.setPWMFreq(60);
  initWiFi();
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  server.begin();
  Serial.println("HTTP server started");
  dht.begin();
  lcd.begin();
  lcd.display();    //เปิดหน้าจอ
  lcd.backlight();  //เปิดไฟ backlight
  lcd.clear();      //ล้างหน้าจอ
  pinMode(Buzzer_Pin, OUTPUT);
  pinMode(LDR_Pin, INPUT);
  digitalWrite(Buzzer_Pin, LOW);
  lcd.noBacklight();
  
  adjectMotorSpeed(255, 255, 255, 255);// Please adject value of motor speed in range 120-255 <------- EDIT ME

  //  HomePosition Robot Arm
  pos1 = 90;
  pos2 = 90;
  pos3 = 90;
  pos4 = 90;
  pos5 = 90;
  pos6 = 90;
  idektep.setPWM(servo1, 0, angleToPulse(pos1));
  idektep.setPWM(servo2, 0, angleToPulse(pos2));
  idektep.setPWM(servo3, 0, angleToPulse(pos3));
  idektep.setPWM(servo4, 0, angleToPulse(pos4));
  idektep.setPWM(servo5, 0, angleToPulse(pos5));
  idektep.setPWM(servo6, 0, angleToPulse(pos6));
}

void loop() {
  processRobotArmMovement();
  ws.cleanupClients();
}
