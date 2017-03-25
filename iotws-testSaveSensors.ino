// project: IoT Weather Station, EAFIT University, Systems Engineering, 20171
// Adaptation done by: Edwin Montoya Munera - emontoya@eafit.edu.co and David Velasquez - dvelas25@eafit.edu.co
// github: https://github.com/iotweatherstation/iotws-testSaveSensors.git

// Description: This program test the connection to the server "iotweatherstation" in order to SAVE: idhome, temp, humid and timestamp (yyyy:mm:dd:hh:mm:ss)
// the connection is done throught Wifi network and HTTP Connection. It uses GET Method.

//Libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

//Constants
const unsigned long SEND_Timer = 5000;  //Delay between SEND updates, 5000 milliseconds
const unsigned int SENTVARS = 4;  //Number of sensor vars sent to REST Web App, (idHome, Temp & Humid, TimeStamp)
const char* SSIDR = "nombre-wifi"; //WiFi SSID, change nombre-wifi por la red propia
const char* PASSWORD = "password-wifi"; //WiFi Pass, coloque el password real
const char* HOST = "http://iotserver1.dis.eafit.edu.co";  //REST Web Host

String appName = "/weather";
String serviceSaveSensors = "/saveSensors";  //Name of the service SAVESENSORS
String serviceGetTime = "/getTime";  //Name of the service GETTIME
char* propertyNames[] = {"idhome", "temp", "humid", "timestamp"}; //Vector Var names 
float propertyValues[SENTVARS]; //Vector for Var values
unsigned long lastConnectionTime = 0; //Last time you connected to the server, in milliseconds


String webGetTime() {
  // variables:
  HTTPClient http;
  String url;
  int httpCode;
  String payload;

  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    url = appName;
    url += serviceGetTime;
    http.begin(HOST + url);
    Serial.print(HOST + url);
    httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        payload = http.getString();
        Serial.println(payload);
      }
    }
    http.end();
    return payload;
  }
}



void SEND(int SENTVARS, char* sensorNames[], float values[]) {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    HTTPClient http;
    String url = appName;
    url += serviceSaveSensors;
    url += "?";
    for (int idx = 0; idx < SENTVARS; idx++)
    {
      url += propertyNames[idx];
      url += "=";
      url += values[idx];
      url += "&";
    }

    http.begin(HOST + url);
    Serial.print(HOST + url);

    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }


}

void setup() {

  Serial.begin(115200);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFiMulti.addAP(SSID, PASSWORD);

}

void loop() {

  if (millis() - lastConnectionTime > SEND_Timer) {
    t = 23.1; // example, replace by real var sensor
    h = 55.0; // example, replace by real var sensor
    Serial.print(" Temperature: ");
    Serial.println(t);
    Serial.print("Humidity: ");
    Serial.print(h);

    propertyValues[0] = 1; // replace by real idHome (string type)
    propertyValues[1] = t;
    propertyValues[2] = h;
    propertyValues[3] = 2017; // replace by webGetTime() (string type)
    
    SEND(SENTVARS, propertyNames, propertyValues);
    lastConnectionTime = millis();
  }
}


