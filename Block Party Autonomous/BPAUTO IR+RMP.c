#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     SMUX,           sensorI2CCustom)
#pragma config(Sensor, S3,     HTGYRO,         sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     leftwheel,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightwheel,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     shoulder,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     elbow,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     spinner,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    claw,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "hitechnic-sensormux.h"
#include "lego-light.h"
#include "lego-touch.h"
#include "hitechnic-gyro.h"


const tMUXSensor dumptouch = msensor_S2_1;
//const tMUXSensor walltouch = msensor_S2_2;
const tMUXSensor LEGOLS = msensor_S2_3;

int backuptime;
int backupdump;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
 LSsetActive(LEGOLS);//set the Light sensor
servo(wrist) = 243;
servo(claw) = 0;
servo(dump) = 16;
HTGYROstartCal(HTGYRO);
wait1Msec(1000);
  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


task main()
{
  initializeRobot();

  time1[T1] = 0;

   while(SensorValue(IR) != 5 )

	{
		motor(leftwheel)= -25; // Go backwards
		motor(rightwheel)= -25;

	}

backuptime = time1[T1];


 float rotSpeed = 0;
  float heading = 0;
	float offset = 605;
  // Calibrate the gyro, make sure you hold the sensor still
  HTGYROstartCal(HTGYRO);

  if(backuptime > 1250 && backuptime < 2500)
	{
		motor(rightwheel) = 20;
		motor(leftwheel) = 20;
		wait1Msec(500);
	}

  if(backuptime > 2500)
	{
		motor(rightwheel) = 20;
		motor(leftwheel) = 20;
		wait1Msec(750);
	}
while (heading > -90)
  	{
   		motor(leftwheel) = -25;
  	  motor(rightwheel) = 25;
  	  wait1Msec(10);

    // Read the current rotation speed
    rotSpeed = SensorValue(HTGYRO)- offset;

    // Calculate the new heading by adding the amount of degrees
    // we've turned in the last 20ms
    // If our current rate of rotation is 100 degrees/second,
    // then we will have turned 100 * (20/1000) = 2 degrees since
    // the last time we measured.
    heading = heading + rotSpeed * 0.01;
  }

	motor(leftwheel) = 0; // Stop
	motor(rightwheel) = 0;

	wait1Msec(250);

	time1[T2] = 0;

	while(TSreadState(dumptouch) != 1)
	{
		motor(leftwheel) = -25; // Go backwards
		motor(rightwheel)= -25;
	}
	 backupdump = time1[T2];

	motor(leftwheel) = 0;
	motor(rightwheel)= 0;
	wait1Msec(250);

	servo[dump] = 149;
	  // dump out
	  wait1Msec(500);
	servo[dump] = 16;
	  // dump in
	  wait1Msec(100);

	motor(leftwheel) = 25;
	motor(rightwheel) = 25;
	wait1Msec(backupdump);

	heading =0;
	rotSpeed = 0;

	while (heading < 80)
  {
   motor(leftwheel) = 0;
   motor(rightwheel) = -30;
   wait1Msec(10);

    // Read the current rotation speed
    rotSpeed = SensorValue(HTGYRO)- offset;

    // Calculate the new heading by adding the amount of degrees
    // we've turned in the last 20ms
    // If our current rate of rotation is 100 degrees/second,
    // then we will have turned 100 * (20/1000) = 2 degrees since
    // the last time we measured.
    heading = heading + rotSpeed * 0.01;
  }


		motor(rightwheel) = 25;
		motor(leftwheel) = 25;
		wait1Msec(backuptime + 900);

  heading =0;
	rotSpeed=0;

	while (heading < 75)
  {
   motor(leftwheel) = 20;
   motor(rightwheel) = -20;
   wait1Msec(10);

    // Read the current rotation speed
    rotSpeed = SensorValue(HTGYRO)- offset;

    // Calculate the new heading by adding the amount of degrees
    // we've turned in the last 20ms
    // If our current rate of rotation is 100 degrees/second,
    // then we will have turned 100 * (20/1000) = 2 degrees since
    // the last time we measured.
    heading = heading + rotSpeed * 0.01;
  }

  while(LSvalNorm(LEGOLS) < 40)
	{
		motor(leftwheel) = 25; // Go foreward)
		motor(rightwheel)= 25;
	}
//	motor(leftwheel) = 0;
	//motor(rightwheel) = 0;
//	wait1Msec(10);//change wait time for compitition

	heading = 0;
	rotSpeed=0;
	while (heading > -100)
  {
   motor(leftwheel) = 0;
   motor(rightwheel) = 25;
   wait1Msec(10);

    // Read the current rotation speed
    rotSpeed = SensorValue(HTGYRO)- offset;

    // Calculate the new heading by adding the amount of degrees
    // we've turned in the last 20ms
    // If our current rate of rotation is 100 degrees/second,
    // then we will have turned 100 * (20/1000) = 2 degrees since
    // the last time we measured.
    heading = heading + rotSpeed * 0.01;
  }

 motor(leftwheel) = 0;
 motor(rightwheel) = 0;
 wait1Msec(100); //change value

 motor(leftwheel) = -50;
 motor(rightwheel) = -50;
 wait1Msec(2250); //change to how long it takes to climb ramp

 motor(leftwheel) = 0;
 motor(rightwheel) = 0;
 wait1Msec(200);

 servo(dump) = 149;//prepare robot for tele-op
 wait1Msec(500);
 motor(elbow) = -100;
 wait1Msec(1750);
 servo(wrist) = 105;
 wait1Msec(500);
 servo(dump) = 16;
 wait1Msec(500);

}
