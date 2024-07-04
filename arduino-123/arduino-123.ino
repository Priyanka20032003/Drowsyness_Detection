#include <LiquidCrystal.h>

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial nodemcu(5, 6);

LiquidCrystal lcd(13,12,11,10,9,8);
int eyeblink=2;
int motor=7;
int buzzer=3;

void setup() 
{
       Serial.begin(9600);
        nodemcu.begin(115200);
       lcd.begin(16, 2);
       lcd.print("    WELCOME");
       delay(1000);
       lcd.clear();
       
       pinMode(eyeblink,INPUT);
       pinMode(motor,OUTPUT);
       pinMode(buzzer,OUTPUT);
       }
 
void loop() 
{
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
    
  int eyestatus= digitalRead(eyeblink);
  Serial.println(eyestatus);
  if(eyestatus==1)
  {
    digitalWrite(motor,LOW);
    digitalWrite(buzzer,HIGH);
    lcd.clear();
    lcd.print("   DANGER !!!");
    lcd.setCursor(0,1);
    lcd.print("Driver in sleep");
  }
  else
  {
    digitalWrite(motor,HIGH);
    digitalWrite(buzzer,LOW);
    lcd.clear();
    lcd.print(" DRIVER ACTIVE");
    lcd.setCursor(0,1);
    lcd.print("   SAFE DRIVE");
  }
   root["a1"] = eyestatus;
   //root["a2"] = h;
   //root["a3"] = darkness;
   //root["a4"] = moisture;
  root.printTo(nodemcu);
  jsonBuffer.clear();
  delay(100);  
}
