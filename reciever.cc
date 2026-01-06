#include <ESP8266WiFi.h>
#include <espnow.h>

#define LIGHT_PIN D4

uint8_t senderMAC[] = {0x00,0x00,0x00,0x00,0x00,0x00}; // fill later

void onReceive(uint8_t *mac, uint8_t *data, uint8_t len) {
  if (len > 0 && data[0] == 1) {
    digitalWrite(LIGHT_PIN, HIGH);
  }
}

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);
  digitalWrite(LIGHT_PIN, LOW);

  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  Serial.print("Receiver MAC: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onReceive);
}

void loop() {
  // nothing. silence is power.
}
