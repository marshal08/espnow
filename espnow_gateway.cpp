#include "espnow_gateway.h"

void ESPNOWGateway::setup() {
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(on_data_receive);
}

void ESPNOWGateway::loop() {}

void ESPNOWGateway::on_data_receive(const uint8_t *mac, const uint8_t *incomingData, int len) {
  Message msg;
  memcpy(&msg, incomingData, sizeof(msg));
  ESP_LOGD("espnow", "📥 Received → Topic: %s | Payload: %s", msg.topic, msg.payload);
  esphome::mqtt::global_mqtt_client->publish(msg.topic, msg.payload);
}
esp_now_peer_info_t peerInfo = {
  .peer_addr = {0xF4, 0x12, 0xFA, 0xCA, 0x5E, 0xC4},
  .channel = 6,
  .encrypt = false
};
esp_now_add_peer(&peerInfo);
