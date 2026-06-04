#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver idektep = Adafruit_PWMServoDriver(0x40); 
#define SERVOMIN 155
#define SERVOMAX 650

#define servo1 0
#define servo2 1
#define servo3 2
#define servo4 3
#define servo5 4

int delay_value = 10;
int Home = 0; 

int pos1 = 90;
int pos2 = 90;
int pos3 = 90;
int pos4 = 30;
int pos5 = 10;

String hold_flag = "99"; 

// โครงสร้างกล่องข้อความสำหรับรับคำสั่ง
typedef struct struct_message {
  char command[15]; 
} struct_message;

struct_message myData;

int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

// ฟังก์ชัน Callback ทำงานอัตโนมัติเมื่อได้รับข้อมูลจากบอร์ดล่าง
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  hold_flag = String(myData.command);
  
  Serial.print("Received Command: ");
  Serial.println(hold_flag); 
}

void setup() {
  Serial.begin(115200);
  idektep.begin();
  idektep.setPWMFreq(60);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);

  pos1 = 90; pos2 = 90; pos3 = 90; pos4 = 30; pos5 = 10;

  idektep.setPWM(servo1, 0, angleToPulse(pos1));
  idektep.setPWM(servo2, 0, angleToPulse(pos2));
  idektep.setPWM(servo3, 0, angleToPulse(pos3));
  idektep.setPWM(servo4, 0, angleToPulse(pos4));
  idektep.setPWM(servo5, 0, angleToPulse(pos5));
  
  Serial.println("Upper ESP32 (Robot Arm) is Ready!");
}

void loop() {
  processRobotArmMovement();
}