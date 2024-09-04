void ledBlink(int delayTime) {
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_L, LOW);
  delay(delayTime);
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_L, HIGH);
  delay(delayTime);
}

void adjectMotorSpeed(int LA, int LB, int RA, int RB) {
  LA_V = LA;
  LB_V = LB;
  RA_V = RA;
  RB_V = RB;
}

void forward() {
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_L, HIGH);
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, HIGH);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH);
  digitalWrite(ML_IN4, LOW);
}

void backward() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, HIGH);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, HIGH);
}

void slide_left() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, HIGH);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, HIGH);
  digitalWrite(ML_IN4, LOW);
}

void slide_right() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, HIGH);
  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, HIGH);
}

void slide_left_front() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, HIGH);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH);
  digitalWrite(ML_IN4, LOW);
}

void slide_right_front() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, LOW);
}

void slide_left_back() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, LOW);
}

void slide_right_back() {
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, HIGH);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, HIGH);
}

void turn_left() {
  digitalWrite(LED_L, HIGH);
  digitalWrite(LED_R, LOW);
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, HIGH);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, HIGH);
}

void turn_right() {
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_L, LOW);
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, HIGH);
  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH);
  digitalWrite(ML_IN4, LOW);
}

void stop() {
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_L, LOW);
  analogWrite(L_ENA, LA_V);
  analogWrite(L_ENB, LB_V);
  analogWrite(R_ENA, RA_V);
  analogWrite(R_ENB, RB_V);
  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);
  digitalWrite(MR_IN4, LOW);
  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);
  digitalWrite(ML_IN4, LOW);
}

//------------------------------------------------------------------AGV Control Function -----------------------------------------------------------------------------//
void processAGVMovement(String inputValue) {
  //Serial.printf("Got value as %s %d\n", inputValue.c_str(), inputValue.toInt());
  switch (inputValue.toInt()) {
    case UP:
      forward();
      break;
    case DOWN:
      backward();
      break;
    case UP_LEFT:
      slide_left_front();
      break;
    case UP_RIGHT:
      slide_right_front();
      break;
    case DOWN_LEFT:
      slide_left_back();
      break;
    case DOWN_RIGHT:
      slide_right_back();
      break;
    case TURN_LEFT:
      turn_left();
      break;
    case TURN_RIGHT:
      turn_right();
      break;
    case ON_BUZZER:
      beep(1);
      break;
    case OFF_BUZZER:
      beep(0);
      break;
    case STOP:
      stop();
      break;
    default:
      stop();
      break;
  }
}
// ------------------------------------------------------------------------------
void beep(bool x) {
  if (x == 1) {
    digitalWrite(18, HIGH);
    lcd_mode = 1;
  } else {
    digitalWrite(18, LOW);
    lcd_mode = 0;
  }
}
// -------------------------------------------------------------------------------
void sensor_fn() {
  ////// รับค่า  Sensor DHT
  humi = dht.readHumidity();     //รับค่าความชื้น
  temp = dht.readTemperature();  //รับค่าอุณหภูมิ
  ////// รับค่า Sensor แสง
  LDR_input = analogRead(LDR_Pin);
  ldr = map(LDR_input, 0, 4095, 0, 500);

  if (temp >= temp_alarm) {
    alarm_beep();
  }
  if (ldr >= light_alarm) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }
  
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH);
  Ultra = microsecondsToCentimeters(duration);
  // Serial.print("Distance:");
  // Serial.println(Ultra);
}
// --------------------------------------------------------------------------
void lcd_fn() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis1 >= lcd_refresh) {
    previousMillis1 = currentMillis;
    lcd.clear();

    ////// แสดงค่า  Sensor DHT
    if (lcd_mode == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Temp : " + String(temp, 1) + " C");  //แสดงค่าอุณหภูมิ
      lcd.setCursor(0, 1);
      lcd.print("Humidity: " + String(humi, 1) + " %");  //แสดงค่าความซื้น
    } else {
      lcd.backlight();
      lcd.setCursor(0, 0);
      lcd.print(LCDtext0);
      lcd.setCursor(0, 1);
      lcd.print(LCDtext1);
    }
  }
}
// --------------------------------------------------------------------------
void alarm_beep() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis2 >= 500) {
    previousMillis2 = currentMillis;
    if (alarm_state == 0) {
      alarm_state = 1;
    } else {
      alarm_state = 0;
    }
    digitalWrite(Buzzer_Pin, alarm_state);
  }
}
