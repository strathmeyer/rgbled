/*
 * WiFly_Device Test Platform
 * A simple tester for communicating with the WiFly GSx RN-131b/g series.
 * LGPL 2.0
 * Tom Waldock, 2011 
 */

#include <WProgram.h>
#include <Streaming.h>
#include <NewSoftSerial.h>
#include "WiFlySerial.h"
#include "MemoryFree.h"

#define ConsoleSerial Serial

#define REDPIN 11
#define GREENPIN 10
#define BLUEPIN 6

#define SSID "PandaNet"
#define WPAKEY "SimplerTimes399"

// Pins are 3 for INCOMING TO Arduino, 4 for OUTGOING TO Wifly
// Arduino       WiFly
//  2 - receive  TX   (Send from Wifly, Receive to Arduino)
//  3 - send     RX   (Send from Arduino, Receive to WiFly) 
WiFlySerial WiFly(2,4); 

#define REQUEST_BUFFER_SIZE 100
#define HEADER_BUFFER_SIZE 150 
#define BODY_BUFFER_SIZE 100

char bufRequest[REQUEST_BUFFER_SIZE];
char bufHeader[HEADER_BUFFER_SIZE];
char bufBody[BODY_BUFFER_SIZE];

//Server server(80);

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Starting RGB LED server." );
  //Serial << "Free memory:" << freeMemory() << endl;  

  //WiFly.setDebugChannel( (Print*) &Serial);
  WiFly.begin();
  Serial << "Starting WiFly." << endl;
  //Serial << "Free memory:" << freeMemory() << endl;

  //Serial << "WiFly begin mem:" <<  freeMemory() << endl;
  
  // get MAC
  Serial << "MAC: " << WiFly.GetMAC(bufRequest, REQUEST_BUFFER_SIZE) << endl;
  // is connected ?

  // if not connected restart link
  if (! WiFly.isConnected() ) {
    Serial << "Leave:" <<  SSID << WiFly.leave() << endl;
    // join
    if (WiFly.setSSID(SSID) ) {    
      Serial << "SSID Set :" << SSID << endl;
    }
    if (WiFly.setPassphrase(WPAKEY)) {
      Serial << "Passphrase Set :" << endl;
    }
    Serial << "Joining... :" << SSID << endl;

    if ( WiFly.join() ) {
      Serial << "Joined " << SSID << " successfully." << endl;
      //WiFly.setNTP( ntp_server ); // use your favorite NTP server
    } else {
      Serial << "Join to " << SSID << " failed." << endl;
    }
  } // if not connected

  Serial << "IP: " << WiFly.GetIP(bufRequest, REQUEST_BUFFER_SIZE) << endl <<
    "Netmask: " << WiFly.GetNetMask(bufRequest, REQUEST_BUFFER_SIZE) << endl <<
    "Gateway: " << WiFly.GetGateway(bufRequest, REQUEST_BUFFER_SIZE) << endl <<
    "DNS: " << WiFly.GetDNS(bufRequest, REQUEST_BUFFER_SIZE) << endl ;

  memset (bufBody,'\0',BODY_BUFFER_SIZE);

  WiFly.SendCommand("set comm remote 0",">");
  WiFly.closeConnection();
  //Serial << "After Setup mem:" << freeMemory() << endl ;

  WiFly.exitCommandMode();
  
}

void strobe(int red, int green, int blue, int period) {
  
}

char chOut;
char chMisc;
int req;
int r, g, b;
int r1, r2, r3;
int g1, g2, g3;
int b1, b2, b3;
void loop() {
  // Terminal routine

  // Always display a response uninterrupted by typing
  // but note that this makes the terminal unresponsive
  // while a response is being received.
  while ((chMisc = WiFly.uart.read()) > -1) {
    Serial << chMisc;
  }
  
  Serial << "Ready!";
  
  req = WiFly.ScanForPattern( bufRequest, REQUEST_BUFFER_SIZE, "*OPEN*", false,2000 );
  if ( ( req &  PROMPT_EXPECTED_TOKEN_FOUND) == PROMPT_EXPECTED_TOKEN_FOUND ) {
    memset (bufRequest,'\0',REQUEST_BUFFER_SIZE);
    WiFly.bWiFlyInCommandMode = false;
    WiFly.ScanForPattern(bufRequest, REQUEST_BUFFER_SIZE, "RGB", 1000);
    Serial << "request,  bytes: " << strlen(bufRequest) << endl << bufRequest << endl;
  
    if (strlen(bufRequest) != 12) {
      return;
    }
    
    while ((chMisc = WiFly.uart.read()) > -1) {
      Serial << chMisc;
    }
  
    r1 = int(bufRequest[0]) - 48;
    r2 = int(bufRequest[1]) - 48;
    r3 = int(bufRequest[2]) - 48;
    g1 = int(bufRequest[3]) - 48;
    g2 = int(bufRequest[4]) - 48;
    g3 = int(bufRequest[5]) - 48;
    b1 = int(bufRequest[6]) - 48;
    b2 = int(bufRequest[7]) - 48;
    b3 = int(bufRequest[8]) - 48;
  
    r = r1 * 100 + r2 * 10 + r3;
    g = g1 * 100 + g2 * 10 + g3;
    b = b1 * 100 + b2 * 10 + b3;
  
    Serial << "r: " << r << endl << "g: " << g << endl << "b: " << b << endl;
    
    /* if (strlen(bufRequest) > 12) {
      switch(bufRequest[9]) {
        case "s":  
      } 
    }*/
    analogWrite(REDPIN, r);
    analogWrite(GREENPIN, g);
    analogWrite(BLUEPIN, b);
  
    WiFly.uart << "OK";
  
    WiFly.closeConnection();
    WiFly.exitCommandMode();
  } // if open connection
} //loop

