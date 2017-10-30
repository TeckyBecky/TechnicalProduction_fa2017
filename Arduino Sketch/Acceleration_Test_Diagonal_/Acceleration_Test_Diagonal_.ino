#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_NeoPixel.h>

#define PIN 12
#define PIN 9
#define PIN 6
#define PIN 10      
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_NeoPixel frontR = Adafruit_NeoPixel(2, 12, NEO_GRB + NEO_KHZ800); // front right (left from wearer's pov)
Adafruit_NeoPixel frontL = Adafruit_NeoPixel(2, 6, NEO_GRB + NEO_KHZ800);  // front left (right from wearer's pov)
Adafruit_NeoPixel backR = Adafruit_NeoPixel(1, 9, NEO_GRB + NEO_KHZ800);  // back right (left from wearer's pov)
Adafruit_NeoPixel backL = Adafruit_NeoPixel(1, 10, NEO_GRB + NEO_KHZ800);  // back left (right from wearer's pov)

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  delay(500);
}

unsigned long previousMillis = 0;
const long interval = 700;
float int_x = 0.0;
float sec_x = 0.0;
float x_diff = 0.0;

float int_z = 0.0;
float sec_z = 0.0;
float z_diff = 0.0;

float int_y = 0.0;
float sec_y = 0.0;
float y_diff = 0.0;

void setup(void)
{
    /* Display some basic information on this sensor */
    displaySensorDetails();
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
    unsigned long currentMillis = millis();
    /* Get a new sensor event */
    sensors_event_t event;
    accel.getEvent(&event);
  
     //SPEED TEST - ADDED CODE
     int_x = event.acceleration.x;
    // Serial.print("Initial X: ");
     //Serial.println(int_x);
  
      int_y = event.acceleration.y;
  //    Serial.print("Initial Y: ");
    //  Serial.println(int_y);
  
     int_z = event.acceleration.z;
     Serial.print("Initial Z: ");
     Serial.println(int_z);
     if(currentMillis - previousMillis >= interval)
     {
        previousMillis = currentMillis;
        sec_x = event.acceleration.x;
        sec_y = event.acceleration.y;
        sec_z = event.acceleration.z;
     }
     Serial.println("=========================================");
     Serial.print("Secondary X: ");
     Serial.println(sec_x);
     Serial.print("Secondary Y: ");
     Serial.println(sec_y);
     Serial.print("Secondary Z: ");
     Serial.println(sec_z);
     
     Serial.println("=========================================");
     x_diff = sec_x - int_x;
     Serial.print("Difference in X: "); 
     Serial.println(x_diff);
  
     z_diff = sec_z - int_z;
     Serial.print("Difference in Z: "); 
     Serial.println(z_diff);
  
     y_diff = sec_y - int_y;
     Serial.print("Difference in Y: ");
     Serial.println(y_diff);
     Serial.println("=========================================");
    /*
     * Note: Difference in X 
     * Direction:
     *      If x_diff is equal to negative value and less than negative 1, the subject is turning left
     * Speed:
     *      If(x_diff <= -1 && x_diff >= -4)
     *        Slow Movement
     *      else if(x_diff < -4)
     *        Fast Movement
     *      else(-1 to 1: 0 to -1 for left)
     *        No or too little movement.
     *        
     * Direction:
     *      If x_diff is equal to positive value and greater than 1, the subject is turning right
     * Speed:
     *      If(x_diff >= 1 && x_diff <= 4)
     *        Slow Movement
     *      else if(x_diff > 4)
     *        Fast Movement
     *      else(-1 to 1: 0 to 1 for right)
     *        No or too little movement.
     * 
     * 
     * Inconsistency Below due to none-leveled area for accelerometer
     * Speed cannot be determined due to inconsistency however up returns positive values and down returns negative.
     * Possible Problems: Interval of initial and secondary values cost switch but generally movement towards the front or nod forward will return positive value while the latter returns negative
     */
    //-------------------------------------------------LEFT AND RIGHT-------------------------------------------------
    if(x_diff >= 5.5 && x_diff <= 6.5)
    {
      //Left, Slow
    }
    else if(x_diff <= -5.5 && x_diff >= -6.5)
    {
      //Right, Slow
    }
    else if(x_diff > 6.5)
    {
      //Left, Fast
    }
    else if(x_diff < -6.5)
    {
      //Right, Fast
    }
    //-------------------------------------------------FORWARD AND BACKWARD-------------------------------------------------
    else if(y_diff >= 5.5 && y_diff <= 6.5)
    {
      //Forward, Slow
    }
    else if(y_diff <= -5.5 && y_diff >= -6.5)
    {
      //Backward, Slow
    }
    else if(y_diff > 6.5)
    {
      //Forward, Fast
    }
    else if(y_diff < -6.5)
    {
      //Backward, Fast
    }
    //-------------------------------------------------UP AND DOWN-------------------------------------------------
    else if(z_diff >= 5.5 && z_diff <= 6.5)
    {
      //Up, Slow
    }
    else if(z_diff <= -5.5 && z_diff >= -6.5)
    {
      //Down, Slow
    }
    else if(z_diff > 6.5)
    {
      //Up, Fast
    }
    else if(z_diff < -6.5)
    {
      //Down, Fast
    }
    //-------------------------------------------------DIAGONAL, FORWARD, DOWN, RIGHT-------------------------------------------------
    else if(x_diff >= 5.5 && x_diff <= 6.5 && z_diff <= -5.5 && z_diff >= -6.5 && y_diff >= 5.5 && y_diff <= 6.5)
    {
      //Diagonal, Slow
    }
    else if(x_diff > 6.5 && z_diff < -6.5 && y_diff > 6.5)
    {
      //Diagonal, Fast
    }
    //-------------------------------------------------DIAGONAL, FORWARD, DOWN, LEFT-------------------------------------------------
    else if(x_diff <= -5.5 && x_diff >= -6.5 && z_diff <= -5.5 && z_diff >= -6.5 && y_diff >= 5.5 && y_diff <= 6.5)
    {
      //Diagonal, Slow
    }
    else if(x_diff < -6.5 && z_diff < -6.5 && y_diff > 6.5)
    {
      //Diagonal, Fast
    }
    //------------------------------------------------DIAGONAL, FORWARD, UP, RIGHT----------------------------------------------------
    else if(x_diff >= 5.5 && x_diff <= 6.5 && z_diff <= 5.5 && z_diff >= 6.5 && y_diff >= 5.5 && y_diff <= 6.5)
    {
        //Diagonal, Slow
    }
    else if(x_diff > 6.5 && z_diff > 6.5 && y_diff > 6.5)
    {
        //Diagonal, Fast
    }
    //------------------------------------------------DIAGONAL, FORWARD, UP, LEFT-----------------------------------------------------
    else if(x_diff >= -5.5 && x_diff <= -6.5 && z_diff >= 5.5 && z_diff <= 6.5 && y_diff >= 5.5 && y_diff <= 6.5)
    {
        //Diagonal, Slow
    }
    else if(x_diff < -6.5 && z_diff > 6.5 && y_diff > 6.5)
    {
        //Diagonal, Fast
    }
    //------------------------------------------------DIAGONAL, BACKWARD, UP, LEFT-----------------------------------------------------
    else if(x_diff <= -5.5 && x_diff >= -6.5 && z_diff >= 5.5 && z_diff <= 6.5 && y_diff <= -5.5 && y_diff >= -6.5)
    {
        //Diagonal, Slow
    }
    else if(x_diff < -6.5 && z_diff > 6.5 && y_diff < -6.5)
    {
        //Diagonal, Fast
    }
    //------------------------------------------------DIAGONAL, BACKWARD, UP, RIGHT-----------------------------------------------------
    else if(x_diff >= 5.5 && x_diff <= 6.5 && z_diff >= 5.5 && z_diff <= 6.5 && y_diff >= -5.5 && y_diff <= -6.5)
    {
        //Diagonal, Slow
    }
    else if(x_diff > 6.5 && z_diff > 6.5 && y_diff < -6.5)
    {
        //Diagonal, Fast 
    }
    //-------------------------------------------------DIAGONAL, BACKWARD, DOWN, RIGHT-------------------------------------------------
    else if(x_diff >= 5.5 && x_diff <= 6.5 && z_diff <= -5.5 && z_diff >= -6.5 && y_diff >= -5.5 && y_diff <= -6.5)
    {
      //Diagonal, Slow
    }
    else if(x_diff > 6.5 && z_diff < -6.5 && y_diff < -6.5)
    {
      //Diagonal, Fast
    }
    //-------------------------------------------------DIAGONAL, BACKWARD, DOWN, LEFT-------------------------------------------------
    else if(x_diff <= -5.5 && x_diff >= -6.5 && z_diff <= -5.5 && z_diff >= -6.5 && y_diff >= -5.5 && y_diff <= -6.5)
    {
      //Diagonal, Slow
    }
    else if(x_diff < -6.5 && z_diff < -6.5 && y_diff < -6.5)
    {
      //Diagonal, Fast
    }
    //-------------------------------------------------ALL OFF-------------------------------------------------
    else
    {
      frontR.setPixelColor(0, 0, 0, 0);
      frontL.setPixelColor(0, 0, 0, 0);
      frontR.setPixelColor(1, 0, 0, 0);
      frontL.setPixelColor(1,0,0,0);
      backR.setPixelColor(0, 0, 0, 0);
      backL.setPixelColor(0, 0, 0, 0);
      frontR.show();
      backR.show();
      //Off
    }
  
    /* Display the results (acceleration is measured in m/s^2) */
  //  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  //  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  //  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  
    /* Note: You can also get the raw (non unified values) for */
    /* the last data sample as follows. The .getEvent call populates */
    /* the raw values used below. */
    //Serial.print("X Raw: "); Serial.print(accel.raw.x); Serial.print("  ");
    //Serial.print("Y Raw: "); Serial.print(accel.raw.y); Serial.print("  ");
    //Serial.print("Z Raw: "); Serial.print(accel.raw.z); Serial.println("");
}
