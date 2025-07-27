#include "esphome.h"
#include <esp_now.h>
#include <WiFi.h>

typedef struct {
  char topic[32];
  char payload[32];
} Message;

class ESPNOWGateway : public Component {
 public:
  void setup() override {
    WiFi.mode(WIFI_STA);
    esp_now_init();
    esp_now_register_recv_cb(on_data_receive);
  }

  static void on_data_receive(const uint8_t *mac, const uint8_t *incomingData, int len) {
    Message msg;
    memcpy(&msg, incomingData, sizeof(msg));

    ESP_LOGD("espnow", "📥 Received → Topic: %s | Payload: %s", msg.topic, msg.payload);

    // Publish to MQTT
    global_mqtt_client->publish(msg.topic, msg.payload);
  }

  void loop() override {}
};
