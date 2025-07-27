#include "esphome.h"
#include <esp_now.h>
#include <WiFi.h>

typedef struct {
  char topic[32];
  char payload[32];
} Message;

class ESPNOWGateway : public esphome::Component {
 public:
  void setup() override;
  void loop() override;
  static void on_data_receive(const uint8_t *mac, const uint8_t *incomingData, int len);
};
