#include <ESP8266WiFi.h>

class PrometheusClient {
 public:
  // Create a new prometheus client connecting to server:port.
  PrometheusClient(const String& server,
                   const uint16_t port,
                   const String& job,
                   const String& instance);
  ~PrometheusClient() { 
    Clear();
    Stop();
  }
  // Init the client - this actually connects to the prometheus server.
  bool Init();
  // AddGauge adds a gauge metric to be updated to the prometheus server.
  //     "extra_keys" are just copied as-is into the args.
  void AddGauge(const String& name,
                const float value,
                const String& extra_keys = "");
  // TODO(z2amiller): Implement rates, etc.

  // Clear will erase any pending unsent messages.
  void Clear() {
    messages_ = "";
  }
  // Send will post any unsent messages to the prometheus server and clear
  //     the list of pending messages.
  bool Send();
  // Stop will stop the wifi client.
  void Stop() {
    client_.stop();
  }
 private:
  const String server_;
  const uint16_t port;
  const String url_;
  String messages_;
  WifiClient client_;
}
