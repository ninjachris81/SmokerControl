#ifndef WIFICONTROLLER_H
#define WIFICONTROLLER_H

#include <AbstractTask.h>
#include <ESP8266WiFi.h>

#include "Debug.h"

#define SERVER_PORT 8080
#define MAX_SRV_CLIENTS 5

class WifiController : public AbstractTask {
public:
  WifiController();
  ~WifiController();
  
  void init();

  void update();

  void broadcastData(String data);

  bool isConnected();

  uint8_t getConnectedClients();

private:
  bool wasConnected = false;
  uint8_t connectTimeout = 100;
  uint8_t connectedClients = 0;
  
  WiFiServer* server;
  WiFiClient serverClients[MAX_SRV_CLIENTS];
};


#endif
