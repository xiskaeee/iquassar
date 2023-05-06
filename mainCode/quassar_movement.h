/* -----------------------------------------------------------------------------
  - Project : IT-PLN Quadruped Robot SAR
  - info :  This library contains all gesture functions
  - modified by i-Quassar Team

/* Includes ------------------------------------------------------------------*/
#include "quassar_config.h"

/*
  - leg position function
   ---------------------------------------------------------------------------*/
void leg_pos()
{ 
  set_site(0, x_default - x_offset, y_start + y_step, z_boot);
  set_site(1, x_default - x_offset, y_start + y_step, z_boot);
  set_site(2, x_default + x_offset, y_start, z_boot);
  set_site(3, x_default + x_offset, y_start, z_boot);
  
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      site_now[i][j] = site_expect[i][j];
    }
  }
}

/*
  - robot initialitazion function
   ---------------------------------------------------------------------------*/
void robot_initialization()
{
  //start serial for debug
  Serial.begin(57600);
  Serial.println("Robot starts initialization");
  
  leg_pos();

  //start servo service
  FlexiTimer2::set(20, servo_service);
  FlexiTimer2::start();  
  Serial.println("Servo service started");
  
  //initialize servos
  servo_attach();
  Serial.println("Servos initialized");
  Serial.println("Robot initialization Complete");
}

void stance()
{
  move_speed = stand_seat_speed;
  
  set_site(0, x_default + x_offset, y_start, z_up);
  set_site(1, x_default + x_offset, y_start, z_up);
  set_site(2, x_default + x_offset, y_start, z_up);
  set_site(3, x_default + x_offset, y_start, z_up);
}

void push_up(int step)
{
  for(int i = 0; i < step; i++)
  {
    if(i % 2 == 0)
    {
      move_speed = stand_seat_speed;
      for (int leg = 0; leg < 4; leg++)
      {
        set_site(leg, KEEP, KEEP, z_default);
      }
      wait_all_reach();
    }
    else
    {
      move_speed = stand_seat_speed;
      for (int leg = 0; leg < 4; leg++)
      {
        set_site(leg, KEEP, KEEP, z_default + 15);
      }
      wait_all_reach();
    }
    delay(200);
  }
}



/*
  - stand function
   ---------------------------------------------------------------------------*/
void stand()
{  
  move_speed = stand_seat_speed;
  for (int leg = 0; leg < 4; leg++)
  {
    set_site(leg, KEEP, KEEP, z_default);
  }
  wait_all_reach();
}

/*
  - is stand function
   ---------------------------------------------------------------------------*/
bool is_stand(void)
{
  if (site_now[0][2] == z_default)
    return true;
  else
    return false;
}

/*
  - is stand function
   ---------------------------------------------------------------------------*/
void sit(void)
{
  move_speed = stand_seat_speed;
  for (int leg = 0; leg < 4; leg++)
  {
    set_site(leg, KEEP, KEEP, z_boot);
  }
  wait_all_reach();
}

/*
  - body right function
   ---------------------------------------------------------------------------*/
void body_right(int ax)
{
  for(int i = 0; i < ax; i++)
  {
    move_speed = stand_seat_speed;
    
    set_site(0, x_default + x_offset - i, KEEP, KEEP);
    set_site(1, x_default + x_offset - i, KEEP, KEEP);
    set_site(2, x_default + x_offset + i, KEEP, KEEP);
    set_site(3, x_default + x_offset + i, KEEP, KEEP);
    
    delay(10);
  }
  wait_all_reach();
}

/*
  - body left function
   ---------------------------------------------------------------------------*/
void body_left(int ax)
{
  for(int i = 0; i < ax; i++)
  {
    move_speed = stand_seat_speed;
    
    set_site(0, x_default + x_offset + i, KEEP, KEEP);
    set_site(1, x_default + x_offset + i, KEEP, KEEP);
    set_site(2, x_default + x_offset - i, KEEP, KEEP);
    set_site(3, x_default + x_offset - i, KEEP, KEEP);
    
    delay(10);
  }
  wait_all_reach();
}

/*
  - warming up function
   ---------------------------------------------------------------------------*/
void warming_up(int step)
{
    
  move_speed = 0.5 * leg_move_speed;
    
  while(step-- > 0)
  {
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default + 10);
    set_site(2, x_default, y_start, z_default + 10);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default + 10);
    set_site(2, x_default, y_start, z_default + 10);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
      
    set_site(0, x_default, y_start, z_default + 10);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default + 10);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default + 10);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default + 10);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
  }
}

/*
  - breath function
   ---------------------------------------------------------------------------*/
void breath(int step)
{
    
  move_speed = 0.025 * leg_move_speed;
    
  while(step-- > 0)
  {
    set_site(0, x_default, y_start, z_default + 10);
    set_site(1, x_default, y_start, z_default + 10);
    set_site(2, x_default, y_start, z_default + 10);
    set_site(3, x_default, y_start, z_default + 10);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default + 10);
    set_site(1, x_default, y_start, z_default + 10);
    set_site(2, x_default, y_start, z_default + 10);
    set_site(3, x_default, y_start, z_default + 10);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
      
    set_site(0, x_default, y_start, z_default + 10);
    set_site(1, x_default, y_start, z_default + 10);
    set_site(2, x_default, y_start, z_default + 10);
    set_site(3, x_default, y_start, z_default + 10);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default + 10);
    set_site(1, x_default, y_start, z_default + 10);
    set_site(2, x_default, y_start, z_default + 10);
    set_site(3, x_default, y_start, z_default + 10);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
  }
}

/*
  - step forward with trot gait
   ---------------------------------------------------------------------------*/
void trot_gait_forward(int step, float speed, float up)
{
  float offset_x = 0;
  float offset_y = 0;
  float offset_z = 0;
  
  move_speed = speed * leg_move_speed;
    
  while(step-- > 0)
  {
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default + up);
    set_site(2, x_default, y_start, z_default + up);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default);
    set_site(1, x_default, y_start + 10, z_default + up);
    set_site(2, x_default, y_start + 10, z_default + up);
    set_site(3, x_default, y_start - 10, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default);
    set_site(1, x_default, y_start + 10, z_default);
    set_site(2, x_default, y_start + 10, z_default);
    set_site(3, x_default, y_start - 10, z_default);
    wait_all_reach();
      
    set_site(0, x_default, y_start, z_default + up);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default + up);
    set_site(1, x_default, y_start - 10, z_default);
    set_site(2, x_default, y_start - 10, z_default);
    set_site(3, x_default, y_start + 10, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default);
    set_site(1, x_default, y_start - 10, z_default);
    set_site(2, x_default, y_start - 10, z_default);
    set_site(3, x_default, y_start + 10, z_default);
    wait_all_reach();
  }
}


/*
  - step back with trot gait
   ---------------------------------------------------------------------------*/
void trot_gait_back(int step, float speed, float up)
{
    
  move_speed = speed * leg_move_speed;
    
  while(step-- > 0)
  {
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default + up);
    set_site(2, x_default, y_start, z_default + up);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default);
    set_site(1, x_default, y_start - 10, z_default + up);
    set_site(2, x_default, y_start - 10, z_default + up);
    set_site(3, x_default, y_start + 10, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default);
    set_site(1, x_default, y_start - 10, z_default);
    set_site(2, x_default, y_start - 10, z_default);
    set_site(3, x_default, y_start + 10, z_default);
    wait_all_reach();
      
    set_site(0, x_default, y_start, z_default + up);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default + up);
    set_site(1, x_default, y_start + 10, z_default);
    set_site(2, x_default, y_start + 10, z_default);
    set_site(3, x_default, y_start - 10, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default);
    set_site(1, x_default, y_start + 10, z_default);
    set_site(2, x_default, y_start + 10, z_default);
    set_site(3, x_default, y_start - 10, z_default);
    wait_all_reach();
  }
}


/*
  - step right with trot gait
   ---------------------------------------------------------------------------*/
void trot_gait_right(int step, float speed, float up)
{
    
  move_speed = speed * leg_move_speed;
    
  while(step-- > 0)
  {
    set_site(0, x_default - 5, y_start, z_default + up);
    set_site(1, x_default - 5, y_start, z_default);
    set_site(2, x_default - 5, y_start, z_default);
    set_site(3, x_default - 5, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default - 5, y_start + 10, z_default + up);
    set_site(1, x_default - 5, y_start + 10, z_default);
    set_site(2, x_default - 5, y_start + 10, z_default);
    set_site(3, x_default - 5, y_start + 10, z_default + up);
    wait_all_reach();
    set_site(0, x_default - 5, y_start + 10, z_default);
    set_site(1, x_default - 5, y_start + 10, z_default);
    set_site(2, x_default - 5, y_start + 10, z_default);
    set_site(3, x_default - 5, y_start + 10, z_default);
    wait_all_reach();
      
    set_site(0, x_default - 5, y_start, z_default);
    set_site(1, x_default - 5, y_start, z_default + up);
    set_site(2, x_default - 5, y_start, z_default + up);
    set_site(3, x_default - 5, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default - 5, y_start - 10, z_default);
    set_site(1, x_default - 5, y_start - 10, z_default + up);
    set_site(2, x_default - 5, y_start - 10, z_default + up);
    set_site(3, x_default - 5, y_start - 10, z_default);
    wait_all_reach();
    set_site(0, x_default - 5, y_start - 10, z_default);
    set_site(1, x_default - 5, y_start - 10, z_default);
    set_site(2, x_default - 5, y_start - 10, z_default);
    set_site(3, x_default - 5, y_start - 10, z_default);
    wait_all_reach();
  }
}


/*
  - step left with trot gait
   ---------------------------------------------------------------------------*/
void trot_gait_left(int step, float speed, float up)
{
    
  move_speed = speed * leg_move_speed;
    
  while(step-- > 0)
  {
    set_site(0, x_default - 5, y_start, z_default + up);
    set_site(1, x_default - 5, y_start, z_default);
    set_site(2, x_default - 5, y_start, z_default);
    set_site(3, x_default - 5, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default - 5, y_start - 10, z_default + up);
    set_site(1, x_default - 5, y_start - 10, z_default);
    set_site(2, x_default - 5, y_start - 10, z_default);
    set_site(3, x_default - 5, y_start - 10, z_default + up);
    wait_all_reach();
    set_site(0, x_default - 5, y_start - 10, z_default);
    set_site(1, x_default - 5, y_start - 10, z_default);
    set_site(2, x_default - 5, y_start - 10, z_default);
    set_site(3, x_default - 5, y_start - 10, z_default);
    wait_all_reach();
      
    set_site(0, x_default - 5, y_start, z_default);
    set_site(1, x_default - 5, y_start, z_default + up);
    set_site(2, x_default - 5, y_start, z_default + up);
    set_site(3, x_default - 5, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default - 5, y_start + 10, z_default);
    set_site(1, x_default - 5, y_start + 10, z_default + up);
    set_site(2, x_default - 5, y_start + 10, z_default + up);
    set_site(3, x_default - 5, y_start + 10, z_default);
    wait_all_reach();
    set_site(0, x_default - 5, y_start + 10, z_default);
    set_site(1, x_default - 5, y_start + 10, z_default);
    set_site(2, x_default - 5, y_start + 10, z_default);
    set_site(3, x_default - 5, y_start + 10, z_default);
    wait_all_reach();
  }
}


/*
  - step swift forward right with trot gait
   ---------------------------------------------------------------------------*/
void swift_forward_right(int step, float speed, float up)
{
    
  move_speed = speed * leg_move_speed;
    
  while(step-- > 0)
  {
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default + up);
    set_site(2, x_default, y_start, z_default + up);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default);
    set_site(1, x_default, y_start, z_default + up);
    set_site(2, x_default, y_start, z_default + up);
    set_site(3, x_default, y_start - 10, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start - 10, z_default);
    wait_all_reach();
      
    set_site(0, x_default, y_start, z_default + up);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default + up);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start + 10, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start + 10, z_default);
    wait_all_reach();
  }
}

/*
  - step swift forward left with trot gait
   ---------------------------------------------------------------------------*/
void swift_forward_left(int step, float speed, float up)
{
    
  move_speed = speed * leg_move_speed;
    
  while(step-- > 0)
  {
    set_site(0, x_default, y_start, z_default + up);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default + up);
    set_site(1, x_default, y_start - 10, z_default);
    set_site(2, x_default, y_start - 10, z_default);
    set_site(3, x_default, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start - 10, z_default);
    set_site(2, x_default, y_start - 10, z_default);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default + up);
    set_site(2, x_default, y_start, z_default + up);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start + 10, z_default + up);
    set_site(2, x_default, y_start + 10, z_default + up);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start + 10, z_default);
    set_site(2, x_default, y_start + 10, z_default);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
  }
}

/*
  - step swift back right with trot gait
   ---------------------------------------------------------------------------*/
void swift_back_right(int step, float speed, float up)
{
    
  move_speed = speed * leg_move_speed;
    
  while(step-- > 0)
  {
    set_site(0, x_default, y_start, z_default + up);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default + up);
    set_site(1, x_default, y_start + 10, z_default);
    set_site(2, x_default, y_start + 10, z_default);
    set_site(3, x_default, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start + 10, z_default);
    set_site(2, x_default, y_start + 10, z_default);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default + up);
    set_site(2, x_default, y_start, z_default + up);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start - 10, z_default + up);
    set_site(2, x_default, y_start - 10, z_default + up);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start - 10, z_default);
    set_site(2, x_default, y_start - 10, z_default);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
  }
}

/*
  - step swift back left with trot gait
   ---------------------------------------------------------------------------*/
void swift_back_left(int step, float speed, float up)
{
    
  move_speed = speed * leg_move_speed;
    
  while(step-- > 0)
  {
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default + up);
    set_site(2, x_default, y_start, z_default + up);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default);
    set_site(1, x_default, y_start, z_default + up);
    set_site(2, x_default, y_start, z_default + up);
    set_site(3, x_default, y_start + 10, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start + 10, z_default);
    wait_all_reach();
      
    set_site(0, x_default, y_start, z_default + up);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default + up);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start - 10, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start - 10, z_default);
    wait_all_reach();
  }
}

/*
  - turn right function
   ---------------------------------------------------------------------------*/
void turn_right(int step, float speed, float up)
{
  move_speed = speed * leg_move_speed;
  
  while(step-- > 0)
  {
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default + up);
    set_site(2, x_default, y_start, z_default + up);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default);
    set_site(1, x_default, y_start + 10, z_default + up);
    set_site(2, x_default, y_start - 10, z_default + up);
    set_site(3, x_default, y_start + 10, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default);
    set_site(1, x_default, y_start + 10, z_default);
    set_site(2, x_default, y_start - 10, z_default);
    set_site(3, x_default, y_start + 10, z_default);
    wait_all_reach();
      
    set_site(0, x_default, y_start, z_default + up);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default + up);
    set_site(1, x_default, y_start - 10, z_default);
    set_site(2, x_default, y_start + 10, z_default);
    set_site(3, x_default, y_start - 10, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default);
    set_site(1, x_default, y_start - 10, z_default);
    set_site(2, x_default, y_start + 10, z_default);
    set_site(3, x_default, y_start - 10, z_default);
    wait_all_reach();
  }
}

/*
  - turn left function
   ---------------------------------------------------------------------------*/
void turn_left(int step, float speed, float up)
{
  move_speed = speed * leg_move_speed;
  
  while(step-- > 0)
  {
    set_site(0, x_default, y_start, z_default);
    set_site(1, x_default, y_start, z_default + up);
    set_site(2, x_default, y_start, z_default + up);
    set_site(3, x_default, y_start, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default);
    set_site(1, x_default, y_start - 10, z_default + up);
    set_site(2, x_default, y_start + 10, z_default + up);
    set_site(3, x_default, y_start - 10, z_default);
    wait_all_reach();
    set_site(0, x_default, y_start + 10, z_default);
    set_site(1, x_default, y_start - 10, z_default);
    set_site(2, x_default, y_start + 10, z_default);
    set_site(3, x_default, y_start - 10, z_default);
    wait_all_reach();
      
    set_site(0, x_default, y_start, z_default + up);
    set_site(1, x_default, y_start, z_default);
    set_site(2, x_default, y_start, z_default);
    set_site(3, x_default, y_start, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default + up);
    set_site(1, x_default, y_start + 10, z_default);
    set_site(2, x_default, y_start - 10, z_default);
    set_site(3, x_default, y_start + 10, z_default + up);
    wait_all_reach();
    set_site(0, x_default, y_start - 10, z_default);
    set_site(1, x_default, y_start + 10, z_default);
    set_site(2, x_default, y_start - 10, z_default);
    set_site(3, x_default, y_start + 10, z_default);
    wait_all_reach();
  }
}

/*
  - step forward function
   ---------------------------------------------------------------------------*/
void step_forward(int step)
{
  // z_axis *= -1;
  
  // z_up += z_axis;
  // z_default += z_axis;  

  move_speed = leg_move_speed;
  while (step-- > 0)
  {
    if (site_now[3][1] == y_start)
    {
      //leg 3&0 move
      set_site(3, x_default + x_offset, y_start, z_up);
      wait_all_reach();
      set_site(3, x_default + x_offset, y_start + 2 * y_step, z_up);
      wait_all_reach();
      set_site(3, x_default + x_offset, y_start + 2 * y_step, z_default);
      wait_all_reach();

      move_speed = body_move_speed;

      set_site(0, x_default + x_offset, y_start + 2 * y_step, z_default);
      set_site(1, x_default + x_offset, y_start, z_default);
      set_site(2, x_default - x_offset, y_start + y_step, z_default);
      set_site(3, x_default - x_offset, y_start + y_step, z_default);
      wait_all_reach();

      move_speed = leg_move_speed;

      set_site(0, x_default + x_offset, y_start + 2 * y_step, z_up);
      wait_all_reach();
      set_site(0, x_default + x_offset, y_start, z_up);
      wait_all_reach();
      set_site(0, x_default + x_offset, y_start, z_default);
      wait_all_reach();
    }
    else
    {
      //leg 1&2 move
      set_site(1, x_default + x_offset, y_start, z_up);
      wait_all_reach();
      set_site(1, x_default + x_offset, y_start + 2 * y_step, z_up);
      wait_all_reach();
      set_site(1, x_default + x_offset, y_start + 2 * y_step, z_default);
      wait_all_reach();

      move_speed = body_move_speed;

      set_site(0, x_default - x_offset, y_start + y_step, z_default);
      set_site(1, x_default - x_offset, y_start + y_step, z_default);
      set_site(2, x_default + x_offset, y_start + 2 * y_step, z_default);
      set_site(3, x_default + x_offset, y_start, z_default);
      wait_all_reach();

      move_speed = leg_move_speed;

      set_site(2, x_default + x_offset, y_start + 2 * y_step, z_up);
      wait_all_reach();
      set_site(2, x_default + x_offset, y_start, z_up);
      wait_all_reach();
      set_site(2, x_default + x_offset, y_start, z_default);
      wait_all_reach();
    }
  }
}

/*
  - step back
  - blocking function
  - parameter step steps wanted to go
   ---------------------------------------------------------------------------*/
void step_back(unsigned int step)
{
  move_speed = leg_move_speed;
  while (step-- > 0)
  {
    if (site_now[3][1] == y_start)
    {
      //leg 2&1 move
      set_site(2, x_default + x_offset, y_start, z_up);
      wait_all_reach();
      set_site(2, x_default + x_offset, y_start + 2 * y_step, z_up);
      wait_all_reach();
      set_site(2, x_default + x_offset, y_start + 2 * y_step, z_default);
      wait_all_reach();

      move_speed = body_move_speed;

      set_site(0, x_default + x_offset, y_start, z_default);
      set_site(1, x_default + x_offset, y_start + 2 * y_step, z_default);
      set_site(2, x_default - x_offset, y_start + y_step, z_default);
      set_site(3, x_default - x_offset, y_start + y_step, z_default);
      wait_all_reach();

      move_speed = leg_move_speed;

      set_site(1, x_default + x_offset, y_start + 2 * y_step, z_up);
      wait_all_reach();
      set_site(1, x_default + x_offset, y_start, z_up);
      wait_all_reach();
      set_site(1, x_default + x_offset, y_start, z_default);
      wait_all_reach();
    }
    else
    {
      //leg 3&0 move
      set_site(0, x_default + x_offset, y_start, z_up);
      wait_all_reach();
      set_site(0, x_default + x_offset, y_start + 2 * y_step, z_up);
      wait_all_reach();
      set_site(0, x_default + x_offset, y_start + 2 * y_step, z_default);
      wait_all_reach();

      move_speed = body_move_speed;

      set_site(0, x_default - x_offset, y_start + y_step, z_default);
      set_site(1, x_default - x_offset, y_start + y_step, z_default);
      set_site(2, x_default + x_offset, y_start, z_default);
      set_site(3, x_default + x_offset, y_start + 2 * y_step, z_default);
      wait_all_reach();

      move_speed = leg_move_speed;

      set_site(3, x_default + x_offset, y_start + 2 * y_step, z_up);
      wait_all_reach();
      set_site(3, x_default + x_offset, y_start, z_up);
      wait_all_reach();
      set_site(3, x_default + x_offset, y_start, z_default);
      wait_all_reach();
    }
  }
}

