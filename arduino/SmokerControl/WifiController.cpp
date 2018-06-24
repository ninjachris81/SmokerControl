#include "WifiController.h"
#include <LogHelper.h>

#include "Credentials.h"
#include "TaskIDs.h"

#include "TempController.h"
#include "SmokerController.h"

#include "TaskIDs.h"

WifiController::WifiController() : AbstractTask() {
  server = new WiFiServer(SERVER_PORT);
}

WifiController::~WifiController() {
  server->stop();
  delete server;
}

void WifiController::init() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
}

void WifiController::update() {
  if (WiFi.status() != WL_CONNECTED) {
    wasConnected = false;
    
    if (connectTimeout>0) {
      LOG_PRINT(".");
      delay(100);
      return;
    } else {
      LOG_PRINTLN(F("Connection Failed! Rebooting..."));
      ESP.restart();
    }
  } else {
    if (!wasConnected) {
      LOG_PRINTLN(F("Wifi connected"));
      LOG_PRINTLN(WiFi.localIP());
      server->begin();
      server->setNoDelay(true);
      wasConnected = true;
    }
  }

  if (server->hasClient()){
    for(uint8_t i = 0; i < MAX_SRV_CLIENTS; i++){
      if (server->hasClient() && !serverClients[i].connected()){
        serverClients[i].stop();
        
        serverClients[i] = server->available();
        LOG_PRINT(F("new client "));
        LOG_PRINT(i);
        LOG_PRINT(" ");
        LOG_PRINT(serverClients[i].remoteIP().toString());
        LOG_PRINTLN(F(" connected"));
      }
    }

    if (server->hasClient()) {
      //no free spot
      LOG_PRINT(F("rejecting client"));
      WiFiClient serverClient = server->available();
      serverClient.stop();
    }
  }
  
  connectedClients = 0;
  for(uint8_t i = 0; i < MAX_SRV_CLIENTS; i++){
    if (serverClients[i].connected()){
      if(serverClients[i].available()) {
        LOG_PRINT(F("Incoming data "));
        LOG_PRINTLN(serverClients[i].available());

        String s = serverClients[i].readStringUntil('\n');
      }
      connectedClients++;
    }
  }

  if (lastBroadcast==0 || millis() - lastBroadcast > BROADCAST_INTERVAL_MS) {
    broadcastData(F("OHU"), taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getOutsideHumidity()); 
    broadcastData(F("OTE"), taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getOutsideTemperature()); 
    broadcastData(F("ITE"), taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature()); 
    broadcastData(F("MTT"), taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature()); 

    SmokerController::SmokerProfile profile = taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile(); 
    broadcastData(F("PNA"), profile.name); 
    broadcastData(F("PIT"), profile.insideTemp); 
    broadcastData(F("PMT"), profile.meatTargetTemp); 
    broadcastData(F("PAS"), (unsigned long) (profile.autoStop ? 1 : 0));

    broadcastData(F("RUN"), (unsigned long) (taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->isRunning() ? 1 : 0));
    broadcastData(F("DUR"), (unsigned long) (taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getDuration() / 1000));     // in sec
    
    lastBroadcast = millis();
  }
}

bool WifiController::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

uint8_t WifiController::getConnectedClients() {
  return connectedClients;
}

void WifiController::broadcastData(String dataId, unsigned long value) {
  _broadcastData(dataId + String(value));
}

void WifiController::broadcastData(String dataId, float value) {
  _broadcastData(dataId + String(value));
}

void WifiController::broadcastData(String dataId, String value) {
  _broadcastData(dataId + value);
}

void WifiController::_broadcastData(String data) {
  if (data.length()==0) return;
  
  for(uint8_t i = 0; i < MAX_SRV_CLIENTS; i++){
    if (serverClients[i] && serverClients[i].connected()){
      serverClients[i].println(data);
      delay(1);
    }
  }
}

