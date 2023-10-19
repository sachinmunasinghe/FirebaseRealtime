// FirebaseRealtime.cpp

#include "FirebaseRealtime.h"

void FirebaseRealtime::begin(const String url, const String secret, const char *ssid, const char *pass) {
  delay(500);
  connectWiFi(ssid, pass);
  client.setInsecure();
  FirebaseRealtime::URL = url;
  FirebaseRealtime::secret = secret;
}

void FirebaseRealtime::connectWiFi(const char *ssid, const char *pass) {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  if (WiFi.status() != WL_CONNECTED) {
    if (pass && strlen(pass)) {
      WiFi.begin(ssid, pass);
    } else {
      WiFi.begin(ssid);
    }
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

String FirebaseRealtime::getSecretParam() {
  if (secret != "")
    return "?auth=" + secret;
  return "";
}

int FirebaseRealtime::save(const String &parentNode, const String &childNode, const String &jsonData, bool isUpdate) {
  int httpResponseCode;
  http.begin(client, URL + "/" + parentNode + "/" + childNode + ".json" + getSecretParam());
  http.addHeader("Content-Type", "application/json");
  if (isUpdate)
    httpResponseCode = http.PATCH(jsonData);
  else
    httpResponseCode = http.PUT(jsonData);
  return httpResponseCode;
}

int FirebaseRealtime::fetch(const String &parentNode, const String &childNode, DynamicJsonDocument &doc) {
  http.begin(client, URL + "/" + parentNode + "/" + childNode + ".json" + getSecretParam());
  int httpResponseCode = http.GET();
  deserializeJson(doc, http.getString());
  return httpResponseCode;
}

int FirebaseRealtime::remove(const String &parentNode, const String &childNode) {
  http.begin(client, URL + "/" + parentNode + "/" + childNode + ".json" + getSecretParam());
  int httpResponseCode = http.DELETE();
  return httpResponseCode;
}
