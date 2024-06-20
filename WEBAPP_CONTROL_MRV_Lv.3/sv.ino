//--------------------------------------------------------------Robot Arm Control Function----------------------------------------------------------------//
void processRobotArmMovement() {
  if (hold_flag == "TURN_RIGHT_RM") {
    M1_2();
  } else if (hold_flag == "TURN_LEFT_RM") {
    M1_1();
  } else if (hold_flag == "EXTEND") {
    M2_1();
  } else if (hold_flag == "RESTACK") {
    M2_2();
  } else if (hold_flag == "UPPER") {
    M3_1();
  } else if (hold_flag == "LOWER") {
    M3_2();
  } else if (hold_flag == "ROTATE_RM_L") {
    M4_1();
  } else if (hold_flag == "ROTATE_RM_R") {
    M4_2();
  } else if (hold_flag == "UPPER_G") {
    M5_2();
  } else if (hold_flag == "LOWER_G") {
    M5_1();
  } else if (hold_flag == "GRIP") {
    M6_2();
  } else if (hold_flag == "UN_GRIP") {
    M6_1();
  } else if (hold_flag == "home") {
    HomePos();
  } else {
    sensor_fn();
    lcd_fn();
  }
}