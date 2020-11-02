
#include <ESP8266WiFi.h>
#include <WiFiManager.h> 
#include <Espalexa.h>

#define Relay1  5     //Relay pin here
#define Relay2  4
#define Relay3  2
#define Relay4  12



//Relay Function
void Relay1fn(uint8_t brightness);
void Relay2fn(uint8_t brightness);
void Relay3fn(uint8_t brightness);
void Relay4fn(uint8_t brightness);

//Device
String Device1="Light";
String Device2="Lamp";
String Device3="TV";
String Device4="Fan";

Espalexa espalexa;
WiFiManager wm;
WiFiManagerParameter custom_field;
void setup()
{   
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  digitalWrite(Relay1,LOW);
  digitalWrite(Relay2,LOW);
  digitalWrite(Relay3,LOW);
  digitalWrite(Relay4,LOW);
  
//  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);   // Wifi AP Mode to input Wifi ssid and password
  Serial.begin(115200);
  
  const char* custom="<form>Device-1 Name:<br><input type='text' name='D1' value=><br>Device-2 Name:<br><input type='text' name='D2' value=><br>Device-3 Name:<br><input type='text' name='D3' value=><br>Device-4 Name:<br><input type='text' name='D4' value=><br>";
  new (&custom_field) WiFiManagerParameter(custom); // custom html input
  
  //add all your parameters here
   wm.addParameter(&custom_field);
  wm.setSaveParamsCallback(saveParamCallback);

  bool res;
  res = wm.autoConnect("Lintod ","lintod12"); // password protected ap
    if(!res) {
        Serial.println("Failed to connect");
       // ESP.restart();
    } 
    else 
    {
        //if you get here you have connected to the WiFi    
    Serial.println("Connected :)");
    //adding devices for alexa to discover
      alexaadddevices();
    
    espalexa.begin();
    }
//read updated parameters
// strcpy(Device1, Devicename1.getValue());
 

}

void loop()
{
  espalexa.loop();
  delay(1);
}

//Relay functions defination
void Relay1fn(uint8_t brightness)
{
  //Control the device
  if (brightness == 255)
    {
      digitalWrite(Relay1, HIGH);
      Serial.println("Device1 ON");
    }
  else
  {
    digitalWrite(Relay1, LOW);
    Serial.println("Device1 OFF");
  }
}

void Relay2fn(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(Relay2, HIGH);
      Serial.println("Device2 ON");
    }
  else
  {
    digitalWrite(Relay2, LOW);
    Serial.println("Device2 OFF");
  }
}



void Relay3fn(uint8_t brightness)
{
  //Control the device  
  if (brightness == 255)
    {
      digitalWrite(Relay3, HIGH);
      Serial.println("Device3 ON");
    }
  else
  {
    digitalWrite(Relay3, LOW);
    Serial.println("Device3 OFF");
  }
}

void Relay4fn(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(Relay4, HIGH);
      Serial.println("Device4 ON");
    }
  else
  {
    digitalWrite(Relay4 , LOW);
    Serial.println("Device4 OFF");
  }
}

void alexaadddevices()  {
    espalexa.addDevice(Device1, Relay1fn); // Device 1 and calling fn is Relay1 , off by default
    espalexa.addDevice(Device2, Relay2fn);
    espalexa.addDevice(Device3, Relay3fn);
    espalexa.addDevice(Device4, Relay4fn);
    }


String getParam(String name){
  //read parameter from server, for customhmtl input
  String value;
  if(wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback(){
  Serial.println("[CALLBACK] saveParamCallback fired");
  Device1=getParam("D1");
  Device2=getParam("D2");
  Device3=getParam("D3");
  Device4=getParam("D4");
  Serial.println("PARAM D1 = " + Device1);
  Serial.println("PARAM D2 = " + Device2);
  Serial.println("PARAM D3 = " + Device3);
  Serial.println("PARAM D4 = " + Device4);
}
