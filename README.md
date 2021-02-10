# ESPFirebaseConfig
Our Documentation for Setup of ESP32/ESP8266 IoT Integration with Backend/Frontend

# Setting Up Firebase for Expo
## Using expo managed workflow
* Create a WEB project, store the API key, config, etc.
* Create a separate file (something like apiKeys.js, and put that in the .gitignore since that should be kept secret!

# Setting up Firebase For ESP 8266/32

## Using the Firebase Arduino Library
* Download ArduinoJson, should be on version 5 even though there are newer versions available

## Important Functions for Getting Data
* Use stream with empty string as argument in order to view the entire database as a whole and listen to any changes
* Then call readEvent() when available() returns true, retrieving the Firebase object
* Call getString("path") to get the path of the read event instance variable
* Get the json object from the Firebase object, then check for type and call appropriate method to retrieve the data


