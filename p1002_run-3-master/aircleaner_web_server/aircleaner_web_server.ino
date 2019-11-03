/*
 WiFiEsp example: WebServer

 A simple web server that shows the value of the analog input 
 pins via a web page using an ESP8266 module.
 This sketch will print the IP address of your ESP8266 module (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to display the web page.
 The web page will be automatically refreshed each 20 seconds.

 For more details see: http://yaab-arduino.blogspot.com/p/wifiesp.html
*/

#include "WiFiEsp.h"
#include <IRremote.h>
// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
#include <String.h>
#include <stdlib.h>

SoftwareSerial Serial1(6, 7); // RX, TX
#endif

char ssid[] = "netis2G";            // your network SSID (name)
char pass[] = "tnawhatnlwk1";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
int reqCount = 0;                // number of requests received

WiFiEspServer server(3000);

IRsend irsend;
unsigned long SEND_IR;


void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  print_wifi_status();
  
  // start the web server on port 80
  server.begin();
}


void loop()
{
  // listen for incoming clients
  WiFiEspClient client = server.available();
  
  if (client) {
    bool Data = false;
    String Send_ir;
    Serial.println("New client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
       // Serial.println(Data);
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          Serial.println("Sending response");
          
          // send a standard http response header
          // use \r\n instead of many println statements to speedup data send
          
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"  // the connection will be closed after completion of the response
            "Refresh: 20\r\n"        // refresh the page automatically every 20 sec
            "\r\n");
          /*
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<html>\r\n");
          client.print("<h1>Hello World!</h1>\r\n");
          client.print("Requests received: ");
          client.print(++reqCount);
          client.print("<br>\r\n");
          client.print("Analog input A0: ");
          client.print(analogRead(0));
          client.print("<br>\r\n");
          client.print("</html>\r\n");*/
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
        
        if(c == '?' && !Data){
          Data = true;
        }
        else if(c == ' ' && Data){
          Data = false;
        }
        else if(Data){
          Send_ir+=c;
        }
        
      }

      
    }
    // give the web browser time to receive the data
    delay(10);

          
    client.print("BYE BYE");
    client.stop();
    Serial.println("Client disconnected");
    
    // close the connection:
    Serial.println("Good bye");

    Serial.println(Send_ir);
    char ch[100];
    strcpy(ch, Send_ir.c_str());      // 라즈베리파이로부터 받은 String형 Send_ir을 char형 ch로 변환
    Serial.println(ch);
    char *ptr = strtok(ch, "&");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환

    while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
    {
        SEND_IR = strtoul(ptr,NULL,16);
    
       Serial.println(SEND_IR,HEX);
        irsend.sendNEC(SEND_IR,32);
        
        ptr = strtok(NULL, "&");      // 다음 문자열을 잘라서 포인터를 반환
        delay(40);
    }
    
  }
}


void print_wifi_status()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  // print where to go in the browser
  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
}
