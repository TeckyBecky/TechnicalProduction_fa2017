#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_NeoPixel.h>

#define PIN 12
#define PIN 9
#define PIN 6
#define PIN 10                                                                                                                                                                                                                                                                                                                                                          
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
Adafruit_NeoPixel frontR = Adafruit_NeoPixel(2, 12, NEO_GRB + NEO_KHZ800); // front right (left from wearer's pov)
Adafruit_NeoPixel frontL = Adafruit_NeoPixel(2, 6, NEO_GRB + NEO_KHZ800);  // front left (right from wearer's pov)
Adafruit_NeoPixel backR = Adafruit_NeoPixel(1, 9, NEO_GRB + NEO_KHZ800);  // back right (left from wearer's pov)
Adafruit_NeoPixel backL = Adafruit_NeoPixel(1, 10, NEO_GRB + NEO_KHZ800);  // back left (right from wearer's pov)
void setup(void)
{
  Serial.begin(9600);

  frontR.begin();
  frontL.begin();
  backR.begin();
  backL.begin();
  frontR.show();
  frontL.show();
  backR.show();
  backL.show();
}



void loop(void)
{
  Serial.println("TEST");
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);
  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
  if(heading < 0)
  {
    heading = 360 + heading;
  }
  if (heading <= 150)
  {
    frontR.setPixelColor(0, 255, 255, 255);
    frontL.setPixelColor(0,255,255,0);
    frontR.setPixelColor(1, 0, 255, 155);
    frontL.setPixelColor(1,255,155,0);
    backR.setPixelColor(0,255,0,255);
    backL.setPixelColor(0,0,255,0);
    frontR.show();
    frontL.show();
    backR.show();
    backL.show();
  }
  else if(heading <= 200)
  {
    frontR.setPixelColor(0, 0, 0, 255);
    frontL.setPixelColor(0, 100, 120, 0);
    frontR.setPixelColor(1, 140, 30, 230);
    frontL.setPixelColor(1,105,65,35);
    backR.setPixelColor(0, 255, 100, 0);
    backL.setPixelColor(0, 0, 255, 100);
    frontR.show();
    frontL.show();
    backR.show();
    backL.show();
  }
  else if(heading <= 250)
  {
    frontR.setPixelColor(0, 255, 0, 255);
    frontL.setPixelColor(0, 255, 120, 0);
    frontR.setPixelColor(1, 140, 30, 255);
    frontL.setPixelColor(1,105,255,35);
    backR.setPixelColor(0, 255, 100, 30);
    backL.setPixelColor(0, 50, 255, 100);
    frontR.show();
    frontL.show();
    backR.show();
    backL.show();
  }
  else if(heading <= 300)
  {
    frontR.setPixelColor(0, 20, 50, 255);
    frontL.setPixelColor(0, 200, 220, 10);
    frontR.setPixelColor(1, 240, 40, 230);
    frontL.setPixelColor(1,205,65,55);
    backR.setPixelColor(0, 25, 225, 10);
    backL.setPixelColor(0, 90, 245, 150);
    frontR.show();
    frontL.show();
    backR.show();
    backL.show();
  }
  else
  {
    frontR.setPixelColor(0, 0, 255, 0);
    frontL.setPixelColor(0,0,0,255);
    backR.setPixelColor(0,123,127,100);
    backL.setPixelColor(0,255,0,0);
    frontR.show();
    frontL.show();
    backR.show();
    backL.show();
  }
  delay(500);
}
