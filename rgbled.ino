/*
 Fade
 
 A program to fade between colors with a RBG LED 
 
 */
#include <math.h>
 
#define rPin 11
#define gPin 10
#define bPin 6
 
#define speedInput A5
// 
//int r = 0;
//int g = 120;
//int b = 240;

byte r;
byte g;
byte b;

double h = 0.0;

void setup()  { 
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(A0, INPUT);
  
  analogWrite(rPin, 0);
  analogWrite(gPin, 0);
  analogWrite(bPin, 0);
  
//  Serial.begin(9600);
}

double degToRad(int degrees) {
  return 0.0174532925 * degrees;
}

double fmap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void updatePosition(double &degrees) {
  unsigned int potVal = analogRead(speedInput);
  double speed = fmap(pow(potVal/1024.0, 5.0), 0.0, pow(1024.0/1024.0, 5.0), 0.01, 100.0);
  degrees = fmod((degrees + speed), 360.0);
//  Serial.println(speed);
}

double sineRange(double input, double rangeMin, double rangeMax) {
  double halfRange = (rangeMax - rangeMin) / 2.0;
  return (sin(input) * halfRange) + halfRange + rangeMin;
}

int ledValue(int position, double scale=1.0) {
   return sineRange(degToRad(position), 10, 255 * scale);
}

void HSV_to_RGB(double h, double s, double v, byte &r, byte &g, byte &b)
{
  int i;
  double f,p,q,t;
  
  h = constrain(h, 0.0, 360.0);
  s = constrain(s, 0.0, 100.0);
  v = constrain(v, 0.0, 100.0);
  
  s /= 100;
  v /= 100;
  
  if (s == 0) {
    // Achromatic (grey)
    r = g = b = round(v*255);
    return;
  }

  h /= 60.0; 
  i = floor(h); // sector 0 to 5
  f = h - (double)i; // factorial part of h
  p = v * (1.0 - s);
  q = v * (1.0 - s * f);
  t = v * (1.0 - s * (1 - f));
  switch(i) {
    case 0:
      r = round(255*v);
      g = round(255*t);
      b = round(255*p);
      break;
    case 1:
      r = round(255*q);
      g = round(255*v);
      b = round(255*p);
      break;
    case 2:
      r = round(255*p);
      g = round(255*v);
      b = round(255*t);
      break;
    case 3:
      r = round(255*p);
      g = round(255*q);
      b = round(255*v);
      break;
    case 4:
      r = round(255*t);
      g = round(255*p);
      b = round(255*v);
      break;
    default: // case 5:
      r = round(255*v);
      g = round(255*p);
      b = round(255*q);
    }
}

// the loop routine runs over and over again forever:
void loop()  {   
  updatePosition(h);
  
  HSV_to_RGB((double)h, 100.0, 100.0, r, g, b);
  
  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);

//  Serial.print(r);
//  Serial.print(", ");
//  Serial.print(g);
//  Serial.print(", ");
//  Serial.println(b);

  delay(30);
}
