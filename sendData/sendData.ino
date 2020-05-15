#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ezTime.h>
#include <NTPClient.h>
#include <WiFiUdp.h> 

//Only 2.4 GHz
#define WIFI_SSID "Noam - 2.4G"
#define WIFI_PASSWORD "noam33pnt"

const char* serverName = "http://192.168.1.77:5000/hearrate";

int data = 80;
int k = 0;
int startRun=0;
String string="time=";
String timeStart ="";
String dateStart ="";
char buf[]={};
char buf1[]={};
int syear,smonth,sday,shour,smin,ssec;
bool tt=true;

Timezone myLocalTime; 
WiFiUDP ntpUDP;

void calcTime(String str){ 
  
  }

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  k = millis();
  myLocalTime.setLocation(F("Asia/Ho_Chi_Minh")); // set your time zone

  // Sync NTP time for ezTime library
  waitForSync(); 
}
 
void loop() {

  if(tt==true) {
    timeStart = String(myLocalTime.dateTime("H:i:s"));
    dateStart = String(myLocalTime.dateTime("d:m:Y"));
    string += timeStart +"&date="+ dateStart + "&data=";
    tt = false;
  }
  
  string += String(data)+ +",";
  startRun = (millis()-k)%60000;
  if(startRun>59950){
    string += String(data);
    HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = string;           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
      Serial.println(string);
      string="time=";
      tt = true;
  }
  delay(30);
}
