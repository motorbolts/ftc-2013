#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     SMUX,           sensorI2CCustom)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S2_C1_1,     leftwheel,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     rightwheel,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const tMUXSensor LEGOLS = msensor_S1_4;

task main()
{
int nrm = 0;

bool active = true;

LSsetActive(LEGOLS);

while(LSvalNorm(LEGOLS) < 26)
{
	motor(leftwheel) = 20;
	motor(rightwheel) = 20;
}

motor(rightwheel) = 0;
motor(leftwheel) = 0;
wait1Msec(3000);

}