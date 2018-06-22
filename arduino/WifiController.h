#ifndef WIFICONTROLLER_H
#define WIFICONTROLLER_H

#include <AbstractTask.h>
#include <ESP8266WiFi.h>

#include "Debug.h"

#define SERVER_PORT 8080
#define MAX_SRV_CLIENTS 5

#define BROADCAST_INTERVAL_MS 5000

class WifiController : public AbstractTask {
public:
  WifiController();
  ~WifiController();
  
  void init();

  void update();

  void broadcastData(String dataId, float value);
  void broadcastData(String dataId, unsigned long value);
  void broadcastData(String dataId, String value);

  bool isConnected();

  uint8_t getConnectedClients();

private:
  void _broadcastData(String data);

  bool wasConnected = false;
  uint64_t lastBroadcast = 0;
  uint8_t connectTimeout = 100;
  uint8_t connectedClients = 0;
  
  WiFiServer* server;
  WiFiClient serverClients[MAX_SRV_CLIENTS];
};


#endif
