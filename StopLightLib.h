/**
*
*	STOPLIGHTLIB - Code Library
*
*	Author: Joe Sandoval
	Orginal Creation Date: 3/4/16
	Last Revision:	3/4/16
*	Copyright 2016(c) Joe Sandoval - Creative Commons Atribution 4.0 International License
*	
*	For All Technical Support Questions, please visit http://cpieeerobotics.wordpress.com/help-support/
*
**/

#ifndef H_STOPLIGHTLIB
#define H_STOPLIGHTLIB

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

class StopLightLib{
public:
	// Variable Definitions
	int motorPins[6]; // Motor Pins [0-3] , PWM Control Pins [4-5]
	int lineSensorPins[3]; // Line Sensor Pins

	StopLightLib();
	// Config & Single Instance Functions
	void motorPinConfig(int motorA1, int motorA2, int motorB1, int motorB2, int pwmA, int pwmB);
	void lineSensorPinConfig(int lineSensor1, int lineSensor2, int lineSensor3);
	void logDrive(double leftSpeed, double rightSpeed);
	void tankDrive(double leftSpeed, double rightSpeed);
	int lineTrack();
	// Utility Functions
	int analog2Digital(int anaPinNo);
	double ultrasonic(int pinTrig, int pinPing); //hcsr04

private:
	int instanceIdentifier;

};

#endif