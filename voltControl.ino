///////////////////////////////////////////////////////////////////////////////////////////////
// -FILENAME: ELBCode.ino                                               -LAST EDITED: 7/30/2018
// -HEADERS:  nunchuk.h           
//
// -DESCRIPTION: The following code is written for controlling an electric longboard via a wii 
//               nunchuck.
//
//
// -CREATOR: Hebron Taylor                                             -DATE CREATED: 7/28/2018
///////////////////////////////////////////////////////////////////////////////////////////////

#include <Servo.h>
#include <Wire.h>
#include "nunchuk.h"

//GLOBAL VARIABLES
  
  Servo esc;
  int motorSpeed;

//END GLOBAL VARIABLES

void setup() {
  // put your setup code here, to run once:
  
  //Serial.begin(19200);                                 //initalize serial port for debugging
  
  nunchuck_setpowerpins();                             //Set power and ground pins for the nunchuck
  nunchuck_init();                                     //Initialize I2C communication for the nunchuk

  pinMode(9,OUTPUT);                                   //setup pin 9 as an output
  esc.attach(9);                                       //attach esc to I/O 9
  
  //Serial.println("**Initialization Complete**");    //DEUBUG LINE
}

void loop() {
  // put your main code here, to run repeatedly:

  nunchuck_get_data();                                  //request data from the nunchuck

  int yJoystick = nunchuck_joyy();                      //y axis data
  int zButton = nunchuck_zbutton();                     //z button data
  int cButton = nunchuck_cbutton();                     //c button data 

  motorSpeed = map(yJoystick, 122, 213, 1000, 2000);    //map the y joystick value to something that the esc can understand
  
  //Serial.println(motorSpeed);                         //DEUBUG LINE

  //only activate the motor if the Z button is pressed (safety feature)
  if(zButton){ esc.writeMicroseconds(motorSpeed);}
  else{ esc.writeMicroseconds(1000);}
 

  

}
