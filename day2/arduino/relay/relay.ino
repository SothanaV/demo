////นำเข้า ชุดคำสั่ง import libary/////
#include <Arduino.h>
#define USE_SERIAL Serial
///////define pin กำหนดขา/////
int relay = 5;        //setpin of relay at D1
//////กำหนดค่าอื่นๆ//////////////
void setup() 
{
  USE_SERIAL.begin(115200);
      pinMode(relay,OUTPUT);
}

void loop() 
{ 
  digitalWrite(relay,HIGH);
  delay(1000);
  digitalWrite(relay,LOW);
  delay(1000);
  digitalWrite(relay,HIGH);
  delay(500);
  digitalWrite(relay,LOW);
  delay(500);
}
