#include <WiFiUdp.h>
#include <WiFi.h>



const char* sta_ssid     = "your wifi name ";
const char* sta_password = "pass code ";

unsigned int localUdpPort = 14555;
char incomingPacket[255];
#define BUFFER_SIZE 1024
#define packTimeout 1
//unsigned char buff[BUFFER_SIZE];
WiFiUDP udp;
byte buff[BUFFER_SIZE];



void setup() {
  Serial.begin(57600);
  Serial2.begin(57600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(sta_ssid, sta_password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  Serial2.println("UDP Print");
  udp.begin(localUdpPort);
Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort); 
}
 




void loop() {
  int size = 0;
  int packetSize = udp.parsePacket();
  char udpBuffer[packetSize];
  
  
   
    udp.read(udpBuffer,packetSize);
    
    Serial.write(udpBuffer,packetSize);
    Serial2.write(udpBuffer,packetSize);
   Serial2.flush();

  
    while( size = Serial2.available()){
      size = (size >= BUFFER_SIZE ? BUFFER_SIZE : size);
      Serial2.readBytes(buff, size);
       udp.beginPacket(udp.remoteIP(), udp.remotePort());
      udp.write(buff,size);
       udp.endPacket();
       
    }
    
   }
