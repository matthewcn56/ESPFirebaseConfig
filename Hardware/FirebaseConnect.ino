#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "espfirebaseconfig-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH ""
#define WIFI_SSID "BlueLaser"
#define WIFI_PASSWORD ""

void setup() {
    Serial.begin(9600);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.stream("");
    if (Firebase.success()) {
        Serial.println("Success!");
    }
    else {
        Serial.println("Sad arduino sounds");
    }
}
char ch = '0';
boolean led1On;
boolean led2On;
boolean led3On;
String led1Color;
String led2Color;
String led3Color;
boolean newOn = false;
void loop() {
    Serial.println("Hello");
    if (Firebase.available()) {
        FirebaseObject a = Firebase.readEvent();
        String path = a.getString("path");
        JsonVariant js = a.getJsonVariant(path);
        Serial.println(js.is<bool>());
        js.prettyPrintTo(Serial);
        if (js.is<int>()) {
            Serial.println(path + " " + Firebase.getInt(path)); //ESP32 :))
        }
        if (js.is<bool>()) {
            Serial.println(path + " " + Firebase.getBool(path)); //ESP32 :))
        }
        if (js.is<const char*>()) {
            Serial.println(path + " " + Firebase.getString(path)); //ESP32 :))
        }
        if (js.is<double>()) {
            Serial.println(path + " " + Firebase.getFloat(path)); //ESP32 :))
        }
    }
    if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
    }
    delay(1000);
    
}
