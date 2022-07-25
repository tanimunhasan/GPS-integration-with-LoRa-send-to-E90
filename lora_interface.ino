#include "Lora.h"
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(GPSBaud);
  loraInit();
  delay(500);
  Serial.println("Hi, I'm going to send message");
  delay(500);
  setConf(11, 22, 1, 0);
  delay(500);
  loraMode(0); // Normal Mode

}

void loop() {
  // put your main code here, to run repeatedly:
   //char* data = "Successful \n\r";
   // char* data = "LED";
 while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
     
//      Serial.print("Latitude= "); 
double data=     Serial.print(gps.location.lat(), 6);      
//     
//      Serial.print(" Longitude= "); 
double data2 =      Serial.println(gps.location.lng(), 6); 
// 
 //double data = double(gps.location.lat(), 6); 
 //   Serial.println(data);
  //double data2 = double(gps.location.lng(), 6);
 
  // Serial.println(data2);
//   
  String stringOne ="    Latitude =  "  ;
  stringOne+= String(data);
  Serial.println(data);
  stringOne+= " Longtitude = "+String(data2);
   
  

  char Buf[300];
    stringOne.toCharArray(Buf, 300);

// char* data = "hello";
//  Serial.println(data);
  sendData(11, 22, 01,stringOne.c_str());

  delay(10);
  multiSerial();
  
    }
  }
}
