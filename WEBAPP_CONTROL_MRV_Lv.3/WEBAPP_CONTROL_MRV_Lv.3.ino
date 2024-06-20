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
const char *ssid = "MRV";
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

#define FRONT_LEFT_MOTOR 3
#define FRONT_RIGHT_MOTOR 0
#define BACK_RIGHT_MOTOR 1
#define BACK_LEFT_MOTOR 2

#define L_ENA 4   // Adjust speed  //motor1
#define L_ENB 19  // Adjust speed //motor2
#define R_ENA 2   // Adjust speed //motor3
#define R_ENB 15  // Adjust speed //motor4

#define FORWARD 1
#define BACKWARD -1

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

struct MOTOR_PINS {
  int pinIN1;
  int pinIN2;
};

std::vector<MOTOR_PINS> motorPins = {
  { 12, 13 },  // FRONT_RIGHT_MOTOR
  { 32, 33 },  // BACK_RIGHT_MOTOR
  { 27, 14 },  // FRONT_LEFT_MOTOR
  { 25, 26 },  // BACK_LEFT_MOTOR
  { 19, 4 },   // LEFT_MOTOR_SPEED
  { 15, 2 },   // RIGHT_MOTOR_SPEED
};

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

//////////////////////////////////////////////////////
String LCDtext0 = "Test";       //16 charactor ข้อความบรรทัด0
String LCDtext1 = "88888888";  //16 charactor ข้อความบรรทัด1
//////////////////////////////////////////////////////////

void setUpPinModes() {
  for (int i = 0; i < motorPins.size(); i++) {
    pinMode(motorPins[i].pinIN1, OUTPUT);
    pinMode(motorPins[i].pinIN2, OUTPUT);
    rotateMotor(i, STOP);
  }
}

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
