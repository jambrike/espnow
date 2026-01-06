#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t receiverMAC[] = {0x84,0xF3,0xEB,0x12,0x34,0x56}; // CHANGE THIS TO WHAT YOU GET IN SERIAL PORT!!!


uint8_t payload = 1;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(receiverMAC, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  esp_now_send(receiverMAC, &payload, sizeof(payload));
}

void loop() {
  // fires once. job done.
}
