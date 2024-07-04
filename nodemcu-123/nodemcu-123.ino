#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial nodemcu(D5, D6);


int data1, data2,data3 ,data4;
String apiKey = "VOTEYUSZ5QVPAHVI";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "Gravity Gimbals";     // replace with your wifi ssid and wpa2 key
const char *pass =  "8778222387";
const char* server = "api.thingspeak.com";
 
WiFiClient client;
   String str;
void setup() 
{
  
  nodemcu.begin(115200);
       Serial.begin(115200);
    //  gpsSerial.begin(9600);
      
       delay(10);
      
       Serial.println("Connecting to ");
       Serial.println(ssid);
       
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(nodemcu);
  if (root == JsonObject::invalid())
  {
    return;
    Serial.println("invalid");
  }

 data1 = root["a1"];
  //data2 = root["a2"];
  //data3 = root["a3"];
 // data4 = root["a4"];
 
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(data1);
                             //postStr +="&field2=";
                             //postStr += String(data2);
                             //postStr +="&field3=";
                             //postStr += String(data3);
                             //postStr +="&field4=";
                             //postStr += String(data4);
                             //postStr +="&field5=";
                             //postStr += String(latitude);
                            // postStr +="&field6=";
                            // postStr += String(longitude);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             //Serial.print("t: ");
                              
                             Serial.print(data1);
                             //Serial.print(" h: ");
                            // Serial.print(data2);
                             //Serial.print("gas");
                             //Serial.print(data3);
                             //Serial.print("dis");
                             // Serial.print(data4);
                             //Serial.print("lat");
                            // Serial.print(latitude);
                            // Serial.print("lon");
                            // Serial.print(longitude);
                             //Serial.print("lat");
                             
                             Serial.println(" Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
  
  
                 
}
