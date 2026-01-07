#include <WiFi.h>
#include <esp_now.h>

// 🔧 CHANGE THIS TO RECEIVER ESP32 MAC
uint8_t receiverMAC[] = { 0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC };

typedef struct {
  char command[8];
} Message;

Message msg;

// --- CALLBACK (OPTIONAL DEBUG) ---
void onSend(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("ESP-NOW send: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "FAIL");
}

void setup() {
  Serial.begin(115200);

  // ESP-NOW requires station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_send_cb(onSend);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("ESP32 bridge ready. Waiting for HIT...");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "HIT") {
      strcpy(msg.command, "On");

      esp_err_t result = esp_now_send(
        receiverMAC,
        (uint8_t *)&msg,
        sizeof(msg)
      );

      Serial.println("HIT sent via ESP-NOW");
    }
  }
}
