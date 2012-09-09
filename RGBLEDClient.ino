#include "SPI.h"
#include "WiFly.h"

#define SSID "PandaNet"
#define PWD "SimplerTimes399"

#define REDPIN1 6
#define GREENPIN1 5
#define BLUEPIN1 3
#define REDPIN2 11
#define GREENPIN2 10
#define BLUEPIN2 9

#define SERVER "172.16.1.8"
#define PORT 2000
WiFlyClient client("172.16.1.8", 2000);

/*#define REQUEST_BUFFER_SIZE 100
#define HEADER_BUFFER_SIZE 150 
#define BODY_BUFFER_SIZE 100

char bufRequest[REQUEST_BUFFER_SIZE];
char bufHeader[HEADER_BUFFER_SIZE];
char bufBody[BODY_BUFFER_SIZE];

WiFlySerial WiFly(2,4); 
*/

void setup() {
  
  Serial.begin(9600);
  //Serial.println("RGB LED at 9600 baud.");

  WiFly.setUart(&Serial);
  WiFly.begin();
  
  Serial.println("set comm idle 2");  // close an inactive conn in 2 seconds
  WiFly.join(SSID, PWD);
  
  pinMode(REDPIN1, OUTPUT);
  pinMode(GREENPIN1, OUTPUT);
  pinMode(BLUEPIN1, OUTPUT);
  pinMode(REDPIN2, OUTPUT);
  pinMode(GREENPIN2, OUTPUT);
  pinMode(BLUEPIN2, OUTPUT);
  
  /*Serial << "Starting WiFly." << endl;
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
    if (WiFly.setPassphrase(PWD)) {
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

  //WiFly.SendCommand("set comm remote 0",">");
  WiFly.closeConnection();
  //Serial << "After Setup mem:" << freeMemory() << endl ;

  //WiFly.exitCommandMode();*/
}

char rgb1[10] = "255255255";
char rgb2[10] = "255255255";
int r1, g1, b1;
int r2, g2, b2;
int r11, r12, r13;
int g11, g12, g13;
int b11, b12, b13;
int r21, r22, r23;
int g21, g22, g23;
int b21, b22, b23;

void loop() {
  Serial.println("in loop");
  
  if (!client.connected()) {
    client.connect();
    delay(100);
  }
  
  if (client.available()) {
    client.println("g");
    for (int i = 0; i < 9; i++) {
      rgb1[i] = client.read();
    }
    for (int i = 0; i < 9; i++) {
      rgb2[i] = client.read();
    }
  }
  
  /*if (WiFly.openConnection( SERVER, PORT ) ) {
    Serial << "opened connection" << endl;
    
    WiFly.uart <<  (const char*) "xxx" << endl; 
    
    // Show server response
    unsigned long TimeOut = millis() + 100;

    while ( millis()  < TimeOut) {
      for (int i = 0; i < 9; i++) {
        //rgb1[i] = WiFly.uart.read();
      }
      for (int i = 0; i < 9; i++) {
        //rgb2[i] = WiFly.uart.read();
      }
      if (  WiFly.uart.available() > 0 ) {
        Serial << "reading" << endl;
        Serial.println( WiFly.uart.read(), BYTE);
        Serial << "done" << endl;
      }
      //while ( WiFly.uart.available() > 0 ) {
      // Serial.print(WiFly.uart.read(), BYTE);
      //}
      WiFly.uart.flush();
    }
    Serial << "rgb1: " << rgb1 << endl;
    Serial << "rgb2: " << rgb2 << endl;
    
    // Force-close connection
    WiFly.closeConnection();
  }*/
  
  r11 = int(rgb1[0]) - 48;
  r12 = int(rgb1[1]) - 48;
  r13 = int(rgb1[2]) - 48;
  g11 = int(rgb1[3]) - 48;
  g12 = int(rgb1[4]) - 48;
  g13 = int(rgb1[5]) - 48;
  b11 = int(rgb1[6]) - 48;
  b12 = int(rgb1[7]) - 48;
  b13 = int(rgb1[8]) - 48;
  
  r21 = int(rgb2[0]) - 48;
  r22 = int(rgb2[1]) - 48;
  r23 = int(rgb2[2]) - 48;
  g21 = int(rgb2[3]) - 48;
  g22 = int(rgb2[4]) - 48;
  g23 = int(rgb2[5]) - 48;
  b21 = int(rgb2[6]) - 48;
  b22 = int(rgb2[7]) - 48;
  b23 = int(rgb2[8]) - 48;
  
  r1 = r11 * 100 + r12 * 10 + r13;
  g1 = g11 * 100 + g12 * 10 + g13;
  b1 = b11 * 100 + b12 * 10 + b13;
  
  r2 = r21 * 100 + r22 * 10 + r23;
  g2 = g21 * 100 + g22 * 10 + g23;
  b2 = b21 * 100 + b22 * 10 + b23;
    
  analogWrite(REDPIN1, r1);
  analogWrite(GREENPIN1, g1);
  analogWrite(BLUEPIN1, b1);
  analogWrite(REDPIN2, r2);
  analogWrite(GREENPIN2, g2);
  analogWrite(BLUEPIN2, b2);
    
  delay(1000);
}


