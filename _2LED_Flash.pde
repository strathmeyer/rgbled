// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN1 6
#define GREENPIN1 5
#define BLUEPIN1 3
#define REDPIN2 11
#define GREENPIN2 10
#define BLUEPIN2 9
 
#define FLASHSPEED 1000
#define FADESPEED 100     // make this higher to slow down
 
void setup() {
  pinMode(REDPIN1, OUTPUT);
  pinMode(GREENPIN1, OUTPUT);
  pinMode(BLUEPIN1, OUTPUT);
  pinMode(REDPIN2, OUTPUT);
  pinMode(GREENPIN2, OUTPUT);
  pinMode(BLUEPIN2, OUTPUT);
}
 
 
void loop() {
  int r, g, b;
  
  r = 255;
  b = 255;
  g = 255;
  
  int r2, g2, b2;
  r2 = 0;
  g2 = 0;
  b2 = 0;
  
  /*
  analogWrite(REDPIN1, r);
  analogWrite(GREENPIN1, g);
  analogWrite(BLUEPIN1, b);
  analogWrite(REDPIN2, 0);
  analogWrite(GREENPIN2, 0);
  analogWrite(BLUEPIN2, 0);
  
  delay(FLASHSPEED);
  
  analogWrite(REDPIN2, r);
  analogWrite(GREENPIN2, g);
  analogWrite(BLUEPIN2, b);
  analogWrite(REDPIN1, 0);
  analogWrite(GREENPIN1, 0);
  analogWrite(BLUEPIN1, 0);
  
  delay(FLASHSPEED);
  */
  
  analogWrite(REDPIN1, 0);
  analogWrite(GREENPIN1, 0);
  analogWrite(BLUEPIN1, b);
  analogWrite(REDPIN2, 0);
  analogWrite(GREENPIN2, g);
  analogWrite(BLUEPIN2, 0);
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    r2 = 255 - r;
    analogWrite(REDPIN1, r);
    analogWrite(REDPIN2, r2);
    delay(FADESPEED);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    b2 = 255 - b;
    analogWrite(BLUEPIN1, b);
    analogWrite(BLUEPIN2, b2);
    delay(FADESPEED);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    g2 = 255 - g;
    analogWrite(GREENPIN1, g);
    analogWrite(GREENPIN2, g2);
    delay(FADESPEED);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    r2 = 255 - r;
    analogWrite(REDPIN1, r);
    analogWrite(REDPIN2, r2);
    delay(FADESPEED);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    b2 = 255 - b;
    analogWrite(BLUEPIN1, b);
    analogWrite(BLUEPIN2, b2);
    delay(FADESPEED);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    g2 = 255 - g;
    analogWrite(GREENPIN1, g);
    analogWrite(GREENPIN2, g2);
    delay(FADESPEED);
  } 
}

