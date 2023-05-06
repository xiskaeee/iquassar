/* -----------------------------------------------------------------------------
  - Project : IT-PLN Quadruped Robot SAR
  - info :  This library contains gyromotions an accelerations function
  - modified by i-Quassar Team
  
  - scl = 21
  - sda = 20 
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "quassar_movement.h"

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

float headingDegrees;
float heading;

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void compass_setup(void) 
{
  Serial.begin(57600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
}

void compass_signal()
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  // Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  // Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  // Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = -0.45;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  headingDegrees = heading * 180/M_PI;
  
  return round(headingDegrees);
}

void compass_show(void) 
{
  
  Serial.print("Heading (degrees): "); Serial.println(round(headingDegrees));
  
  // int min_heading = 40;
  // int max_heading = 70;
  // int head = headingDegrees;
  
  
  // // directional set position
  //   while(headingDegrees <= min_heading || headingDegrees >= max_heading)
  //   {
  //     if(headingDegrees <= min_heading)
  //     {
  //       turn_right(1, 0.5, 10);
  //       if(headingDegrees <= min_heading || headingDegrees >= max_heading)
  //       {
  //         stand();
  //         break;
  //       }
  //       else
  //         continue;
  //     }
  //     else if(headingDegrees >= max_heading)
  //     {
  //       turn_left(1, 0.5, 10);
  //       if(headingDegrees <= min_heading || headingDegrees >= max_heading)
  //       {
  //         stand();
  //         break;
  //       }
  //       else
  //         continue;
  //     }
  //     else
  //       stand();
  //   }
    
  //   Serial.print("Heading (degrees): "); Serial.println(round(headingDegrees));
  
  delay(500);
}