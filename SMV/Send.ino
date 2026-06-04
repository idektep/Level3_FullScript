void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void sendCmdViaESPNow(String cmd) {
  cmd.toCharArray(myData.command, 15);
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  if (result == ESP_OK) {
    Serial.println("Sent Command to Arm: " + cmd);
  } else {
    Serial.println("Error sending command");
  }
}
//------------------------------------------------------------------------------------------------------------//