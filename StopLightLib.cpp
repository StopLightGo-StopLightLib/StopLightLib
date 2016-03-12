#include "StopLightLib.h"
	StopLightLib::StopLightLib(){
		// Nothing Here!
	}

	void StopLightLib::motorPinConfig(int motorA1, int motorA2, int motorB1, int motorB2, int pwmA, int pwmB){
		motorPins[0] = motorA1;
		motorPins[1] = motorA2;
		motorPins[2] = motorB1;
		motorPins[3] = motorB2;
		motorPins[4] = pwmA;
		motorPins[5] = pwmB;
	}

	void StopLightLib::lineSensorPinConfig(int lineSensor1, int lineSensor2, int lineSensor3){
		lineSensorPins[0] = lineSensor1;
		lineSensorPins[1] = lineSensor2;
		lineSensorPins[2] = lineSensor3;
	}

	int StopLightLib::analog2Digital(int anaPinNo){
		int analogProcessing = analogRead(anaPinNo);
		if (analogProcessing >= 600) {
		return 1;
		}
		else {
		return 0;
		}
	}

	void StopLightLib::logDrive(double leftSpeed, double rightSpeed){
	/*
	   *  Logarithmic Drive Function:
	   *    - This function uses a logarithmic curve to provide variable speeds within a usable range.
	   *    - Log Equation used: (60*ln(x))+255
	   *
	   */

	  // Set both motor directions to forward by default, changing only if the user types in a negative decimal
	  bool lDirection = true; // true == forwards
	  bool rDirection = true;

	  // Create 2 speed variables we can use while tinkering with the speed commands.
	  double leftSpeedWorking = 0.00;
	  double rightSpeedWorking = 0.00;

	  // Compute the final output into these variables.
	  double leftOutput = 0.00;
	  double rightOutput = 0.00;

	  if (leftSpeed < 0.00) {
	    // If the percentage is negative, use absolute value of input and chage direction the false (backwards)
	    lDirection = false;
	    leftSpeedWorking = leftSpeed * (-1.0);
	  }
	  else {
	    leftSpeedWorking = leftSpeed;
	  }
	  if (rightSpeed < 0.00) {
	    // If the percentage is negative, use absolute value of input and chage direction the false (backwards)
	    rDirection = false;
	    rightSpeedWorking = rightSpeed * (-1.0);
	  }
	  else {
	    rightSpeedWorking = rightSpeed;
	  }

	  // Use the Logarithim to scale the requested speed into the usable range. (125 - 255 arduino PWM units)
	  leftOutput = (60 * (log(leftSpeedWorking)) + 255);
	  rightOutput = (60 * (log(rightSpeedWorking)) + 255);

	  if (lDirection == true && leftSpeed != 0.00) {
	    \
	    // If direction is forward AND speed is NOT 0.00, Drive Motors Forward.
	    analogWrite(motorPins[4], leftOutput);
	    digitalWrite(motorPins[1], HIGH); // Send PWM
	    digitalWrite(motorPins[0], LOW); // GND
	  }
	  else if (lDirection == false && leftSpeed != 0.00) {
	    // If direction is backwards AND speed is NOT 0.00, Drive Motors Backward.
	    analogWrite(motorPins[4], leftOutput);
	    digitalWrite(motorPins[0], HIGH); // Send PWM
	    digitalWrite(motorPins[1], LOW); // GND
	  }
	  else {
	    digitalWrite(motorPins[4], LOW);
	  }

	  if (rDirection == true && rightSpeed != 0.00) {
	    \
	    // If direction is forward AND speed is NOT 0.00, Drive Motors Forward.
	    analogWrite(motorPins[5], rightOutput);
	    digitalWrite(motorPins[2], HIGH); // Send PWM
	    digitalWrite(motorPins[3], LOW); // GND
	  }
	  else if (rDirection == false && rightSpeed != 0.00) {
	    // If direction is backwards AND speed is NOT 0.00, Drive Motors Backward.
	    analogWrite(motorPins[5], rightOutput);
	    digitalWrite(motorPins[3], HIGH); // Send PWM
	    digitalWrite(motorPins[2], LOW); // GND
	  }
	  else {
	    digitalWrite(motorPins[5], LOW);
	  }
	}

	void StopLightLib::tankDrive(double leftSpeed, double rightSpeed){
	/*
	   *  Tank Drive Function:
	   *    - This function converts decimal values to motor PWM signals
	   *	- Note that depending on you device, your motors could stall at lower input values
	   *
	   */

	  // Set both motor directions to forward by default, changing only if the user types in a negative decimal
	  bool lDirection = true; // true == forwards
	  bool rDirection = true;

	  // Create 2 speed variables we can use while tinkering with the speed commands.
	  double leftSpeedWorking = 0.00;
	  double rightSpeedWorking = 0.00;

	  // Compute the final output into these variables.
	  double leftOutput = 0.00;
	  double rightOutput = 0.00;

	  if (leftSpeed < 0.00) {
	    // If the percentage is negative, use absolute value of input and chage direction the false (backwards)
	    lDirection = false;
	    leftSpeedWorking = leftSpeed * (-1.0);
	  }
	  else {
	    leftSpeedWorking = leftSpeed;
	  }
	  if (rightSpeed < 0.00) {
	    // If the percentage is negative, use absolute value of input and chage direction the false (backwards)
	    rDirection = false;
	    rightSpeedWorking = rightSpeed * (-1.0);
	  }
	  else {
	    rightSpeedWorking = rightSpeed;
	  }

	  // Uses a liniar scale to convert the requested speed into the usable range. (0 - 255 arduino PWM units)
	  leftOutput = ((leftSpeedWorking)*255);
	  rightOutput = ((rightSpeedWorking)*255);

	  if (lDirection == true && leftSpeed != 0.00) {
	    // If direction is forward AND speed is NOT 0.00, Drive Motors Forward.
	    analogWrite(motorPins[4], leftOutput);
	    digitalWrite(motorPins[1], HIGH); // Send PWM
	    digitalWrite(motorPins[0], LOW); // GND
	  }
	  else if (lDirection == false && leftSpeed != 0.00) {
	    // If direction is backwards AND speed is NOT 0.00, Drive Motors Backward.
	    analogWrite(motorPins[4], leftOutput);
	    digitalWrite(motorPins[0], HIGH); // Send PWM
	    digitalWrite(motorPins[1], LOW); // GND
	  }
	  else {
	    digitalWrite(motorPins[4], LOW);
	  }

	  if (rDirection == true && rightSpeed != 0.00) {
	    \
	    // If direction is forward AND speed is NOT 0.00, Drive Motors Forward.
	    analogWrite(motorPins[5], rightOutput);
	    digitalWrite(motorPins[2], HIGH); // Send PWM
	    digitalWrite(motorPins[3], LOW); // GND
	  }
	  else if (rDirection == false && rightSpeed != 0.00) {
	    // If direction is backwards AND speed is NOT 0.00, Drive Motors Backward.
	    analogWrite(motorPins[5], rightOutput);
	    digitalWrite(motorPins[3], HIGH); // Send PWM
	    digitalWrite(motorPins[2], LOW); // GND
	  }
	  else {
	    digitalWrite(motorPins[5], LOW);
	  }
	}

	double StopLightLib::ultrasonic(int pinTrig, int pinPing){
	// Bring Trigger Pin LOW to avoid interference
	digitalWrite(pinTrig, LOW);
	delayMicroseconds(2);
	// Signal to the Ultrasonic to enable ultrasonic pulse
	digitalWrite(pinTrig, HIGH);
	delayMicroseconds(10);
	// Bring Trigger Low again; Begin Ping.
	digitalWrite(pinTrig, LOW);

	// Determine and return time to signal return.
	int v = pulseIn(pinPing, HIGH);
	return v;
	}

	int StopLightLib::lineTrack(){
	if(analog2Digital(lineSensorPins[0]) == LOW && analog2Digital(lineSensorPins[1])== LOW && analog2Digital(lineSensorPins[2]) == LOW){
	    // Completely off, not sure which direction
	    return 3;
	  }
	  else if(analog2Digital(lineSensorPins[2]) == HIGH && analog2Digital(lineSensorPins[1])== LOW){
	    // Right
	    return 1;
	  }
	  else if(analog2Digital(lineSensorPins[0]) == HIGH && analog2Digital(lineSensorPins[1]) == LOW){
	    // Left
	    return 2;
	  }
	  else{
	    // Nope, your good!
	    return 0;
	  }
	}