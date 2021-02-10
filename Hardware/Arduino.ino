#include <SoftwareSerial.h>
SoftwareSerial ESPserial(2, 3); // RX | TX
 
void setup() 
{
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    ESPserial.begin(9600);  
    pinMode(9, INPUT);
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println(""); 
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
       
}
char str;
int a = 0;
int counterLED = 0;
void loop() 
{
    if (counterLED == 3) {
        counterLED = 0;
    }
    String val = "";
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if (ESPserial.available()) {
        while ((str = ESPserial.read()) != '\n') {
            val += str;
        }  
            a = val.toInt();
            Serial.println(a);
    }

    if (a == 1 && counterLED == 0) {
        digitalWrite(5, HIGH);
        counterLED++;
    }
    else if (a == 0 && counterLED == 0) {
        digitalWrite(5, LOW);
        counterLED++;
    }
    else if (a == 1 && counterLED == 1) {
        digitalWrite(6, HIGH);
        counterLED++;
    }
    else if (a == 0 && counterLED == 1) {
        digitalWrite(6, LOW);
        counterLED++;
    }
    else if (a == 1 && counterLED == 2) {
        digitalWrite(7, HIGH);
        counterLED++;
    }
    else if (a == 0 && counterLED == 2) {
        digitalWrite(7, LOW);
        counterLED++;
    }
    a = -1;
    delay(1000);
}
