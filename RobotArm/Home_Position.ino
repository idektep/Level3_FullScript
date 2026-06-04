void setServoHome(int& pos, int targetPos, int servo) {
  if (pos < targetPos) {
    pos++;
  } else if (pos > targetPos) {
    pos--;
  }
  idektep.setPWM(servo, 0, angleToPulse(pos));
  delay(1);  
}

void HomePos() {
  Home = 1;
  if (Home == 1) {
    setServoHome(pos1, 90, servo1);
    setServoHome(pos2, 90, servo2);
    setServoHome(pos3, 90, servo3);
    setServoHome(pos4, 30, servo4);
    setServoHome(pos5, 10, servo5);
  }
}