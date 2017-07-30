////นำเข้า ชุดคำสั่ง import libary/////
#include <Arduino.h>
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
void SendData(float h , float t);     //Define Senddata Voide
///////define pin กำหนดขา/////
int DHTPIN = D2;          //setpin of DHT at D4
//////กำหนดค่าอื่นๆ//////////////
int DHTTYPE = DHT11;                  //set Dht Type 
DHT dht(DHTPIN, DHTTYPE);             //define DHT type and pin
const char* ssid     = "true_home2G_792";            //Set ssid
const char* password = "ilovestudy";                    //Set Password
const char* Server   = "192.168.1.54";           //set Server Domain or Server ip
ESP8266WiFiMulti WiFiMulti;
void setup() 
{
  Serial.begin(115200);
      for(uint8_t t = 6; t > 0; t--) 
      {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
      }
  Serial.begin(115200);
  dht.begin();                        //start DHT
  WiFiMulti.addAP(ssid, password);    //Set SSID and Password (SSID, Password)
    WiFi.begin(ssid, password);         //Set starting for Wifi
    Serial.println(WiFi.localIP());
    dht.begin();
}

void loop() 
{
  float h = dht.readHumidity();      //Read Humidity
  float t = dht.readTemperature();   //Read Temperature
   if (isnan(t) || isnan(h)) 
    {
    Serial.println("FaiLed to read from DHT");
    } 
   else 
    {
   Serial.print("TEMPERATURE");
   Serial.println(t);
   Serial.print("HUMIDITY");
   Serial.println(h);
    SendData(h,t);
    }

}
void SendData(float h,float t) 
{
  
  // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) 
    {
        HTTPClient http;
        String str = "http://" +String(Server)+":5002" +"/data/" + String(t)+"/"+String(h);
        Serial.println(str);
        http.begin(str);
        int httpCode = http.GET();
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        if(httpCode > 0) 
        {
            if(httpCode == HTTP_CODE_OK) 
              {
                String payload = http.getString();
              }
        }
    }
}
