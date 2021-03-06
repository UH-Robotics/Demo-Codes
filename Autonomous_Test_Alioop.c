#pragma config(Sensor, dgtl1,  encoderBacLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encoderBacRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  encoderForRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  encoderForLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, Unicorn,        sensorTouch)
#pragma config(Motor,  port1,           holo2,         tmotorVex269, openLoop)
#pragma config(Motor,  port2,           holo1,         tmotorVex269, openLoop)
#pragma config(Motor,  port3,           feed1,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           feed2,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           holo4,         tmotorVex269, openLoop)
#pragma config(Motor,  port6,           shootr1,       tmotorVex393, openLoop)
#pragma config(Motor,  port7,           shootr2,       tmotorVex393, openLoop)
#pragma config(Motor,  port8,           shootl1,       tmotorVex393, openLoop)
#pragma config(Motor,  port9,           shootl2,       tmotorVex393, openLoop)
#pragma config(Motor,  port10,          holo3,         tmotorVex269, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(45)
#pragma userControlDuration(75)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!


/*Functions defined at bottom*/
void alioop(void);
void intake(int meow);
void shooter(int meow);
void load(void);
void maybe(void);

void EncodedForward(int speed,int ticks);
void EncodedSide(int speed,int ticks);
void EncodedTurn(int speed,int ticks);

bool cupcake = false;
int speed = 125;

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

task autonomous() {
	EncodedSide(-50,145);
	wait10Msec(30);
	shooter(65);
	wait10Msec(300);
	maybe();
	load();
	maybe();
	load();
	maybe();
	shooter(0);
	wait10Msec(300);
	EncodedTurn(70,550);
	wait10Msec(70);
	intake(120);
	wait10Msec(50);
	EncodedForward(-55,200);
	wait10Msec(70);
	intake(0);
	wait10Msec(50);
	EncodedTurn(70,490);
	wait10Msec(50);
	shooter(65);
	wait10Msec(300);
	load();
	maybe();
	shooter(0);
	wait10Msec(300);
	//EncodedForward(-85,400);
}

task usercontrol()	{
	while(true)	{
	 /*Driving Mechanisms : Holonomic Drive eventually*/
		motor[port1]= ((vexRT[Ch3]) + (vexRT[Ch4]) + (vexRT[Ch1]));//Fl
		motor[port2]= ((vexRT[Ch3]) - (vexRT[Ch4]) - (vexRT[Ch1]));//FR
		motor[port5]= (-(vexRT[Ch3]) - (vexRT[Ch4]) + (vexRT[Ch1]));//BR
		motor[port10]= (-(vexRT[Ch3]) + (vexRT[Ch4]) - (vexRT[Ch1]));//BL

		/*Shooting Mechanisms*/
		if(vexRT[Btn8D]==1)	{alioop();}

		if(vexRT[Btn6U]==1 && speed<=120)	{
			speed=speed+5;
			wait10Msec(50);
		}
		else if(vexRT[Btn6D]==1 && speed>=45)	{
			speed=speed-5;
			wait10Msec(50);
	  }
	  else{speed=speed;}
		if(cupcake==true)	{
			motor[port6]=speed;
			motor[port7]=-speed;
			motor[port8]=speed;
			motor[port9]=-speed;
		}
		else	{
			motor[port6]=0;
			motor[port7]=0;
			motor[port8]=0;
			motor[port9]=0;
		}
		/*Intake Mechanism*/
		if((vexRT[Btn5D]==1) && (SensorValue(Unicorn)==0))	{
			motor[port3]=127;
			motor[port4]=127;
		}
		else if(vexRT[Btn5U]==1)	{
			motor[port3]=-127;
			motor[port4]=-127;
		}
		else	{
			motor[port3]=0;
			motor[port4]=0;
		}
	}
}

void alioop(void)	{					// Switches variable to opposite value
	if(cupcake==false)	cupcake=true;
	else cupcake=false;
	wait10Msec(50);
}

void EncodedForward(int speed,int ticks){
	SensorValue[encoderBacRight]=0;
	SensorValue[encoderBacLeft]=0;
	SensorValue[encoderForRight]=0;
	SensorValue[encoderForLeft]=0;

	motor[port1]= speed; //FL
	motor[port2]= speed; //FR
	motor[port5]= -speed; //BR w/ encoder Left
	motor[port10]= -speed; //BL w/ encoder Right

	while((((abs(SensorValue[encoderBacRight])+ abs(SensorValue[encoderForRight]))/2) < ticks) || (((abs(SensorValue[encoderBacLeft])+ abs(SensorValue[encoderForLeft]))/2) < ticks))	{
		if(((abs(SensorValue[encoderBacRight])+ abs(SensorValue[encoderForRight]))/2) > ((abs(SensorValue[encoderBacLeft])+ abs(SensorValue[encoderForLeft]))/2)){
			motor[port1]= speed-25; //FL
			motor[port2]= speed; //FR
			motor[port5]= -speed; //BR w/ encoder Right
			motor[port10]= -speed+25; //BL w/ encoder Left
		}
		if(((abs(SensorValue[encoderBacRight])+ abs(SensorValue[encoderForRight]))/2) < ((abs(SensorValue[encoderBacLeft])+ abs(SensorValue[encoderForLeft]))/2))	{
			motor[port1]= speed; //FL
			motor[port2]= speed-25; //FR
			motor[port5]= -speed+25; //BR w/ encoder Right
			motor[port10]= -speed; //BL w/ encoder Left
		}
		if(((abs(SensorValue[encoderBacRight])+ abs(SensorValue[encoderForRight]))/2) == ((abs(SensorValue[encoderBacLeft])+ abs(SensorValue[encoderForLeft]))/2))	{
			motor[port1]= speed; //FL
			motor[port2]= speed; //FR
			motor[port5]= -speed; //BR w/ encoder Left
			motor[port10]= -speed; //BL w/ encoder Right
		}
	}

	motor[port1]= 0;
	motor[port2]= 0;
	motor[port5]= 0;
	motor[port10]= 0;
}
void EncodedSide(int speed,int ticks){
	SensorValue[encoderBacRight]=0;
	SensorValue[encoderBacLeft]=0;
	SensorValue[encoderForRight]=0;
	SensorValue[encoderForLeft]=0;

	motor[port1]= speed;
	motor[port2]= -speed;
	motor[port5]= -speed;
	motor[port10]= speed;

	while((((abs(SensorValue[encoderBacRight])+ abs(SensorValue[encoderBacLeft]))/2) < ticks) || (((abs(SensorValue[encoderForRight])+ abs(SensorValue[encoderForLeft]))/2) < ticks)){
		if(((abs(SensorValue[encoderBacRight])+ abs(SensorValue[encoderBacLeft]))/2) > ((abs(SensorValue[encoderForRight])+ abs(SensorValue[encoderForLeft]))/2) ){
			motor[port1]= speed-25; //FL
			motor[port2]= -speed+25; //FR
			motor[port5]= -speed; //BR w/ encoder Right
			motor[port10]= speed; //BL w/ encoder Left
		}
		if(((abs(SensorValue[encoderBacRight])+ abs(SensorValue[encoderBacLeft]))/2) < ((abs(SensorValue[encoderForRight])+ abs(SensorValue[encoderForLeft]))/2) ){
			motor[port1]= speed; //FL
			motor[port2]= -speed; //FR
			motor[port5]= -speed+25; //BR w/ encoder Right
			motor[port10]= speed-25; //BL w/ encoder LEFT
		}
		if(((abs(SensorValue[encoderBacRight])+ abs(SensorValue[encoderBacLeft]))/2) == ((abs(SensorValue[encoderForRight])+ abs(SensorValue[encoderForLeft]))/2) ){
			motor[port1]= speed; //FL
			motor[port2]= -speed; //FR
			motor[port5]= -speed; //BR w/ encoder Left
			motor[port10]= speed; //BL w/ encoder Right
		}
	}

	motor[port1]= 0;
	motor[port2]= 0;
	motor[port5]= 0;
	motor[port10]= 0;
}

void EncodedTurn(int speed,int ticks){
	SensorValue[encoderBacRight]=0;
	SensorValue[encoderBacLeft]=0;
	SensorValue[encoderForRight]=0;
	SensorValue[encoderForLeft]=0;

	motor[port1]= speed;
	motor[port2]= -speed;
	motor[port5]= speed;
	motor[port10]= -speed;

	while((abs(SensorValue[encoderBacRight]) < ticks) || (abs(SensorValue[encoderBacLeft]) < ticks)){}

	motor[port1]= 0;
	motor[port2]= 0;
	motor[port5]= 0;
	motor[port10]= 0;
}

// Moving Functions for Autonomous
void intake (int meow){
	motor[port3]= -meow;
	motor[port4]= -meow;
}

void shooter (int meow){
	motor[port6]=meow;
	motor[port7]=-meow;
	motor[port8]=meow;
	motor[port9]=-meow;
}

void load(void){
	while(SensorValue(Unicorn)==0){intake(120);}
	wait10Msec(50);
	intake(0);
	wait10Msec(70);
}

void maybe(void){
	while(SensorValue(Unicorn)==1){intake(120);}
	intake(0);
	wait10Msec(70);
}
