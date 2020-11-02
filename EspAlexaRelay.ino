/*
 * Purpose   : To turn Relay On/OFF using Alexa with Esp8266 as a controller
 * Date      : 29/10/2020
 * Author(s) : A-r-jun
 * Version   : 1.0
 * Notes     : I used espalexa basic and advance code and changed them for my use 
 *             and also added Wifimanger library for runtime input.
 */

#include <ESP8266WiFi.h> 
#include <WiFiManager.h>  // Download the library from here ------  https://github.com/tzapu/WiFiManager
#include <Espalexa.h> //   Download the library from here ------    https://github.com/Aircoookie/Espalexa

#define Relay1  5  //D1     //Relay pin here
#define Relay2  4  //D2
#define Relay3  14 //D5
#define Relay4  12 //D6
// can add more relays here if needed , i made code only for 4 relay


//Relay Function
void Relay1fn(uint8_t brightness);
void Relay2fn(uint8_t brightness);
void Relay3fn(uint8_t brightness);
void Relay4fn(uint8_t brightness);
//void RelayXfn(uint8_t brightness);
// if you add more relay trhen you will need to copy this function prototype and defination 


//Device   // this is by default name that will come when alexa search for device
          // but i have added wifiManager parameter to change them on runtime
String Device1="Light";
String Device2="Lamp";
String Device3="TV";
String Device4="Fan";
//String DeviceX="X";
Espalexa espalexa;   //Espalexa Object creation
WiFiManager wm;     ////Wifi,manager Object creation
WiFiManagerParameter custom_field;    // custom parameter to added to wifi manager ( to change device name)

void setup()
{   
    // Defining pin type and setting them on low
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);   
  digitalWrite(Relay1,LOW);
  digitalWrite(Relay2,LOW);
  digitalWrite(Relay3,LOW);
  digitalWrite(Relay4,LOW);
  
//  WiFi.disconnect(true);  //this will erase previous stored wifi data (ssid and password) 

  WiFi.mode(WIFI_STA);   // Wifi AP Mode to input Wifi ssid and password
  Serial.begin(115200);
  
  // Parameter to add device name on Runtime
  // if you add more relay means you have added more device , so to fget their name on run time you will need to add html lines here
  //html line ------    Device-X Name:<br><input type='text' name='DX' value=><br>
  const char* custom="<form>Device-1 Name:<br><input type='text' name='D1' value='Light'><br>Device-2 Name:<br><input type='text' name='D2' value='Lamp'><br>Device-3 Name:<br><input type='text' name='D3' value='TV'><br>Device-4 Name:<br><input type='text' name='D4' value='Fan'><br>";
  new (&custom_field) WiFiManagerParameter(custom);
  
 //adding parameter to wifimanager
   wm.addParameter(&custom_field);
  // when parameter are added and saved
  wm.setSaveParamsCallback(saveParamCallback);

  
  bool res;
  // Esp8266 will broadcast this wifi ssid if it is unable to connect to any network
  res = wm.autoConnect("WiFi","password"); // password protected ap // you can change it to your own
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

}

void loop()
{
  espalexa.loop();
  delay(1);
}

//Relay functions defination
void Relay1fn(uint8_t brightness)
{
  // the on and off button feature was depricated and dimming feature is use to turn on and off
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
// copy and change this function  accordingly if you add more relays and devices
/*void RelayXfn(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayX, HIGH);
      Serial.println("DeviceX ON");
    }
  else
  {
    digitalWrite(RelayX , LOW);
    Serial.println("DeviceX OFF");
  }
}*/


void alexaadddevices()  {
    espalexa.addDevice(Device1, Relay1fn); // Device 1 and calling fn is Relay1 , off by default
    espalexa.addDevice(Device2, Relay2fn);
    espalexa.addDevice(Device3, Relay3fn);
    espalexa.addDevice(Device4, Relay4fn);
  //espalexa.addDevice(DeviceX, RelayXfn);
    }

// this functions get device name on the Runtime
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
