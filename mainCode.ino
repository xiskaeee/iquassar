// // #include "quassar_config.h"
// #include "quassar_movement.h"
// #include "quassar_gyro.h"
#include "quassar_compass.h"
#include "quassar_control.h"
// #include "quassar_communication.h"

/*
  - setup function
   ---------------------------------------------------------------------------*/
void setup()
{
  
  TIMSK0 = 0;
  // robot initialization
  robot_initialization();
  
  // initializing acceleration
  // gyro_setup();
  
  // initializing compass
  compass_setup();
  
  // initializing controller
  // controller_setup();
  
}

/*
  - loop function
   ---------------------------------------------------------------------------*/
void loop()
{
  
  compass_signal();
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
  
  int min_heading = 60;
  int max_heading = 100;
  int head = headingDegrees;
  
   
  // directional set position
    while(headingDegrees <= min_heading || headingDegrees >= max_heading)
    {
      
      if(headingDegrees <= min_heading)
      {
        turn_right(1, 1, 10);
        Serial.println("putar kanan");
        if(headingDegrees <= min_heading || headingDegrees >= max_heading)
        {
          Serial.println("berdiri");
          stand();
          break;
        }
        else
          continue;
      }
      else if(headingDegrees >= max_heading)
      {
        turn_left(1, 1, 10);
        if(headingDegrees <= min_heading || headingDegrees >= max_heading)
        {
          stand();
          break;
        }
        else
          continue;
      }
      else
        stand();
        break;
    }
    
    Serial.print("Heading (degrees): "); Serial.println(round(headingDegrees));
  
  delay(500);
  
  // ble_setup();
  delay(2000);
  stand();
  
  // trot_gait_forward(1, 0.25, 10);
  
  // acceleration_show();
  
  // gyro_signal();
  
  
  // // compass_show();
  
  
   // ble_connect();
}
