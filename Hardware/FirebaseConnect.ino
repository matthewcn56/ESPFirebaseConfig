#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  pinMode(2, OUTPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

boolean currentOn = false;
boolean newOn = false; 
void loop() {
  // set bool value
  newOn = Firebase.getBool("led");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  if (newOn && !currentOn) {
    digitalWrite(2, HIGH);
    currentOn = true;
  }
  else if (!newOn && currentOn) {
    digitalWrite(2, LOW);
    currentOn = false;
  }
  delay(10000);
}
