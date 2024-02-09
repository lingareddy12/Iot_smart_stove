#include<ESP8266WiFi.h> 
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>

WiFiClient client;
HTTPClient http;



const char *ssid="IQ";
const char *pass="linga444";  

String url;
char val; 
int k;

void connect_wifi()
{
   WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  } 
  Serial.println("Wifi connected");
  Serial.println("IP Address :");
  Serial.print(WiFi.localIP());
} 

void send_gas_data(int data)
{
  url="http://api.thingspeak.com/update?api_key=HKYM0HOG2HA2MSPJ&field1=";
  url=url+data;
  http.begin(client,url);
  int httpcode=http.GET();
  if(httpcode>0)
  {
    Serial.println("DATA SENT SUCCESSFULLY");
  } 
  else
  {
    Serial.println("Error");
  }  
  http.end();
}

void send_whistle_data(int data)
{
  url="https://api.thingspeak.com/update?api_key=HKYM0HOG2HA2MSPJ&field2=";
  url=url+data;
  http.begin(client,url);
  int httpcode=http.GET();
  if(httpcode>0)
  {
    Serial.println("DATA SENT SUCCESSFULLY");
  } 
  else
  {
    Serial.println("Error");
  }  
  http.end();
}

void send_timer_data(int data)
{
  url="http://api.thingspeak.com/update?api_key=HKYM0HOG2HA2MSPJ&field3=";
  url=url+data;
  http.begin(client,url);
  int httpcode=http.GET();
  if(httpcode>0)
  {
    Serial.println("DATA SENT SUCCESSFULLY");
  } 
  else
  {
    Serial.println("Error");
  }  
  http.end();
}

void setup()
{ 
  Serial.begin(9600);
  connect_wifi(); 
}  

void loop()
{    
  while(Serial.available()>0)
 {
  val=Serial.read();  
  Serial.println(k);
  if (val=='1')
  {  
    k=1;
    Serial.println(k);
    send_whistle_data(k);   
  }
  if (val=='2')
  { 
    k=2;
  Serial.println(k);
    send_timer_data(k);   
  } 
   if (val=='3')
  { 
    k=300;
  Serial.println(k);
    send_gas_data(k);   
  } 
  
      
}
}
