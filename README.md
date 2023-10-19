# FirebaseRealtime

A simple library to make Firebase Realtime Database CRUD operations.

## Features
- save (create and update)
- read
- delete

## Dependencies

- FirebaseRealtime uses [ArduinoJson](https://github.com/bblanchon/ArduinoJson) for json parsing.

## Example

```c++
#include <FirebaseRealtime.h>

#define FIREBASE_REALTIME_URL ""
#define FIREBASE_REALTIME_SECRET ""

char ssid[] = "";
char pass[] = "";

FirebaseRealtime firebaseRealtime;

void setup() {
  Serial.begin(9600);
  firebaseRealtime.begin(FIREBASE_REALTIME_URL, FIREBASE_REALTIME_SECRET, ssid, pass);
}

void loop() {
  // save
  DynamicJsonDocument saveDoc(1024);
  saveDoc["name"] = "Device 1";
  saveDoc["temperature"] = 30.00;
  saveDoc["location"][0] = 48.756080;
  saveDoc["location"][1] = 2.302038;
  String saveJSONData;
  serializeJson(saveDoc, saveJSONData);
  int saveResponseCode = firebaseRealtime.save("devices", "1", saveJSONData);
  Serial.println("\nSave - response code: " + String(saveResponseCode));
  saveDoc.clear();

  // update
  DynamicJsonDocument updateDoc(1024);
  updateDoc["temperature"] = 35.00;
  String updateJSONData;
  serializeJson(updateDoc, updateJSONData);
  int updateResponseCode = firebaseRealtime.save("devices", "1", updateJSONData, true);
  Serial.println("\nUpdate - response code: " + String(updateResponseCode));
  updateDoc.clear();

  // fetch
  DynamicJsonDocument fetchDoc(1024);
  int fetchResponseCode = firebaseRealtime.fetch("devices", "1", fetchDoc);
  float temp = fetchDoc["temperature"];
  String name = fetchDoc["name"];
  float lat = fetchDoc["location"][0];
  float lon = fetchDoc["location"][1];
  Serial.println("\nFetch - response code: " + String(fetchResponseCode));
  Serial.println("Name: " + name + ", Temp: " + String(temp) + ", Lat: " + String(lat) + ", Lon: " + String(lon));
  fetchDoc.clear();

  // delete
  // int deleteResponseCode = remove("devices", "1");
  // Serial.println("\nDelete response code: " + String(deleteResponseCode));

  delay(5000);
}
```

## License

[MIT](https://github.com/sachinmunasinghe/FirebaseRealtime/blob/main/LICENSE)
