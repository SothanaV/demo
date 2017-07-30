////นำเข้า ชุดคำสั่ง import libary/////
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define USE_SERIAL Serial
///////define pin กำหนดขา/////
int DHTPIN = 2;          //setpin of DHT at D4
int relay = 5;        //setpin of relay at D1

//////กำหนดค่าอื่นๆ//////////////
int DHTTYPE = DHT11;                  //set Dht Type 
DHT dht(DHTPIN, DHTTYPE);             //define DHT type and pin
void SendData(float h , float t);     //Define Senddata Voide
const char* ssid     = "true_home2G_792";            //Set ssid ใส่ชื่อwifi
const char* password = "ilovestudy";                    //Set Password ใส่พาสเวิร์ดwifi
const char* Server   = "192.168.1.52";                //set Server Domain or Server ip ใส่โดเมนหรือไอพีเซิฟเวอร์
ESP8266WiFiMulti WiFiMulti;
void setup() 
{
  USE_SERIAL.begin(115200);
      for(uint8_t t = 6; t > 0; t--) 
      {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
      }
      WiFiMulti.addAP(ssid, password);    //Set SSID and Password (SSID, Password)
      WiFi.begin(ssid, password);         //Set starting for Wifi
      Serial.println(WiFi.localIP());

      dht.begin();                        //start DHT

      pinMode(relay,OUTPUT);

}

void loop() 
{
  float h = dht.readHumidity();      //Read Humidity
  float t = dht.readTemperature();   //Read Temperature
  Serial.print("TEMPERATURE");
   Serial.println(t);
   Serial.print("HUMIDITY");
   Serial.println(h);
   if (isnan(t) || isnan(h)) 
    {
    Serial.println("FaiLed to read from DHT");
    } 
   else 
    {
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
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
        if(httpCode > 0) 
        {
            if(httpCode == HTTP_CODE_OK) 
              {
                String payload = http.getString();
                USE_SERIAL.print("payload");
                USE_SERIAL.println(payload);
                  if(payload=="1")
                  {
                    digitalWrite(relay,HIGH);
                    Serial.println("Relay_ON");
                  }
                  if(payload=="0")
                  {
                    digitalWrite(relay,LOW);
                    Serial.println("Relay_OFF");
                  }
                  
              }
        }
        http.end();
    }
    delay(1000);
}

