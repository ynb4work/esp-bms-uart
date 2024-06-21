#include "esphome.h"
using namespace esphome;

class MyCustomSensor : public PollingComponent, public UARTDevice {
 public:
  Sensor *voltage_sensor = new Sensor();
  Sensor *current_sensor = new Sensor();

  MyCustomSensor(UARTComponent *parent) : PollingComponent(10000), UARTDevice(parent) {}

  void setup() override {
    // nothing to do here
  }

  void update() override {
    // Read data from UART
    String data = read_line();
    if (data.length() == 0) {
      return;
    }

    // Parse data (example logic, needs to be adapted to your data format)
    float voltage = id(parse_voltage)(std::string(data.c_str()));
    float current = id(parse_current)(std::string(data.c_str()));

    // Publish sensor values
    voltage_sensor->publish_state(voltage);
    current_sensor->publish_state(current);
  }

  String read_line() {
    String line = "";
    while (available()) {
      char c = read();
      if (c == '\n') {
        break;
      }
      line += c;
    }
    return line;
  }
};
