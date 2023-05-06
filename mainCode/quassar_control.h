/* -----------------------------------------------------------------------------
  - Project : IT-PLN Quadruped Robot SAR
  - info :  This library contains controller configuration
  - modified by i-Quassar Team
*/
#include <PS2X_lib.h>   

PS2X controller; 

/* -----------------------------------------------------------------------------
  - right now, the library does NOT support hot-pluggable controllers, meaning 
  - you must always either restart your Arduino after you connect the controller, 
  - or call config_gamepad(pins) again after connecting the controller.
*/

int error = 0; 
byte type = 0;
byte vibrate = 0;

void controller_setup()
{
  Serial.begin(57600);

  // GamePad(clock, command, attention, data, Pressures?, Rumble?)
  error = controller.config_gamepad(2, 3, 4, 5, true, true);  
  
  if(error == 0)
  {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
    
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
    
  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
        
  type = controller.readType(); 
    switch(type)
    {
      case 0:
        Serial.println("Unknown Controller type");
        break;
      case 1:
        Serial.println("DualShock Controller Found");
        break;
    }
}


void controller_read(){
  
  /*  You must Read Gamepad to get new values
      Read GamePad and set vibration values
      controller.read_gamepad(small motor on/off, larger motor strenght from 0-255)
      if you don't enable the rumble, use controller.read_gamepad(); with no values
      you should call this at least once a second
  */
   
  if(error == 1) 
    return; 

 if(type == 1) //DualShock Controller
 { 
  controller.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
  if(controller.Button(PSB_START))                   //will be TRUE as long as button is pressed
    Serial.println("Start is being held");
  
  if(controller.Button(PSB_SELECT))
     Serial.println("Select is being held");
            
  if(controller.Button(PSB_PAD_UP))         //will be TRUE as long as button is pressed
  {  
    Serial.print("Up held this hard: ");
    Serial.println(controller.Analog(PSAB_PAD_UP), DEC);
  }
      
  if(controller.Button(PSB_PAD_RIGHT))
  {
    Serial.print("Right held this hard: ");
    Serial.println(controller.Analog(PSAB_PAD_RIGHT), DEC);
  }
  
  if(controller.Button(PSB_PAD_LEFT))
  {
    Serial.print("LEFT held this hard: ");
    Serial.println(controller.Analog(PSAB_PAD_LEFT), DEC);
  }
  
  if(controller.Button(PSB_PAD_DOWN))
  {
    Serial.print("DOWN held this hard: ");
    Serial.println(controller.Analog(PSAB_PAD_DOWN), DEC);
  }   
    
  vibrate = controller.Analog(PSAB_BLUE);     //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
  if (controller.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
  {   
    if(controller.Button(PSB_L3))
      Serial.println("L3 pressed");
    
    if(controller.Button(PSB_R3))
      Serial.println("R3 pressed");
    
    if(controller.Button(PSB_L2))
      Serial.println("L2 pressed");
    
    if(controller.Button(PSB_R2))
      Serial.println("R2 pressed");
    
    if(controller.Button(PSB_GREEN))
      Serial.println("Triangle pressed");  
  }   
  
  if(controller.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
    Serial.println("Circle just pressed");
         
  if(controller.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
    Serial.println("Square just released");     
    
  if(controller.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
    Serial.println("X just changed");    
    
  if(controller.Button(PSB_L1) || controller.Button(PSB_R1)) // print stick values if either is TRUE
  {
    Serial.print("Stick Values:");
    Serial.print(controller.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
    Serial.print(",");
    Serial.print(controller.Analog(PSS_LX), DEC); 
    Serial.print(",");
    Serial.print(controller.Analog(PSS_RY), DEC); 
    Serial.print(",");
    Serial.println(controller.Analog(PSS_RX), DEC); 
  }
 }
 delay(50);   
}