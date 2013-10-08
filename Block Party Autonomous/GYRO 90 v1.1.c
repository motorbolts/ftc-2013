#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTGYRO,         sensorAnalogInactive)
#pragma config(Motor,  mtr_S1_C1_1,     leftwheel,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightwheel,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-gyro-test2.c 133 2013-03-10 15:15:38Z xander $
 */

/**
 * hitechnic-gyro.h provides an API for the HiTechnic Gyroscopic Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER.

 * Xander Soldaat (xander_at_botbench.com)
 * 06 April 2012
 * version 0.1
 */

#include "hitechnic-gyro.h"

task main ()
{
  float rotSpeed = 0;
  float heading = 0;
	float offset = 590;
  // Calibrate the gyro, make sure you hold the sensor still
  HTGYROstartCal(HTGYRO);

  while (heading < 90)
  {
   motor(leftwheel) = 25;
   motor(rightwheel) = -25;
   wait1Msec(20);

    // Read the current rotation speed
    rotSpeed = HTGYROreadRot(HTGYRO) - offset;

    // Calculate the new heading by adding the amount of degrees
    // we've turned in the last 20ms
    // If our current rate of rotation is 100 degrees/second,
    // then we will have turned 100 * (20/1000) = 2 degrees since
    // the last time we measured.
    heading = heading + rotSpeed * 0.02;

    // Display our current heading on the screen
    nxtDisplayCenteredBigTextLine(3, "%2.0f", heading);
  }
  motor(rightwheel) = 0;
  motor(leftwheel) = 0;
}
