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
