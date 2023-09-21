// FirebaseRealtime.h

#ifndef FirebaseRealtime_h
#define FirebaseRealtime_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

class FirebaseRealtime {
private:
  String URL;
  String secret;
  WiFiClientSecure client;
  HTTPClient http;
  void connectWiFi(const char *ssid, const char *pass);
  String getSecretParam();

public:
  void begin(const String url, const String secret, const char *ssid, const char *pass);
  int save(const String &parentNode, const String &childNode, const String &jsonData, bool isUpdate = false);
  int fetch(const String &parentNode, const String &childNode, DynamicJsonDocument &doc);
  int remove(const String &parentNode, const String &childNode);
};

#endif