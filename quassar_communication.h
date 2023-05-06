/* -----------------------------------------------------------------------------
  - Project : IT-PLN Quadruped Robot SAR
  - info :  This library contains all configurations for bluetooth communication
  - modified by i-Quassar Team
/*

/* Includes ------------------------------------------------------------------*/
#include "quassar_movement.h"
#include <SerialCommand.h>

SerialCommand SCmd;

#define STAND_SIT         0
#define STEP_FORWARD      1
#define STEP_BACK         2
#define STEP_RIGHT        3
#define STEP_LEFT         4
#define TURN_RIGHT        5
#define TURN_LEFT         6
#define BODY_RIGHT        7
#define BODY_LEFT         8

void action_cmd(void)
{
  char *arg;
  int action_mode, n_step;
  Serial.println("Action :");
  arg = SCmd.next();
  action_mode = atoi(arg);
  arg = SCmd.next();
  n_step = atoi(arg);

  switch (action_mode)
  {
    case STAND_SIT:
      Serial.println("1 : UP, 0 : DOWN");
      if (n_step)
        stand();
      else
        sit();
      break;
    case STEP_FORWARD:
      Serial.print("Step Forward -> ");
      Serial.print(n_step);
      Serial.println("x");
      if (!is_stand())
        stand();
      trot_gait_forward(n_step, 0.5, 10);
      break;
    case STEP_BACK:
      Serial.print("Step Back -> ");
      Serial.print(n_step);
      Serial.println("x");
      if (!is_stand())
        stand();
      trot_gait_back(n_step, 0.5, 10);
      break;
    case STEP_RIGHT:
      Serial.print("Step Right -> ");
      Serial.print(n_step);
      Serial.println("x");
      if (!is_stand())
        stand();
      trot_gait_right(n_step, 0.5, 10);
      break;
    // case STEP_LEFT:
    //   Serial.print("Step Left -> ");
    //   Serial.print(n_step);
    //   Serial.println("x");
    //   if (!is_stand())
    //     stand();
    //   trot_gait_left(n_step, 0.5);
    //   break;
    case TURN_RIGHT:
      Serial.print("Turn Right -> ");
      Serial.print(n_step);
      Serial.println("x");
      turn_right(n_step, 0.5, 10);
      break;
    case TURN_LEFT:
      Serial.print("Turn Left -> ");
      Serial.print(n_step);
      Serial.println("x");
      turn_left(n_step, 0.5, 10);
      break;
    case BODY_RIGHT:
      Serial.println("Body Right");
      body_right(n_step);
      break;  
    case BODY_LEFT:
      Serial.println("Body Left");
      body_left(n_step);
      break;
    default:
      Serial.println("Error");
      break;
  }
}

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("What?");
}

/*
  - setup the bluethooth connection
   ---------------------------------------------------------------------------*/
void ble_setup()
{ 
 
  SCmd.addCommand("quassar", action_cmd);
  SCmd.setDefaultHandler(unrecognized);
  
}

/*
  - bluethoot connection function
   ---------------------------------------------------------------------------*/
void ble_connect()
{
  SCmd.readSerial();
}


