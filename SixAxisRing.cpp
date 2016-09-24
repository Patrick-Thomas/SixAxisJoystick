/*
 Copyright (C) 2016 P. Thomas <patrick.thomas@bath.edu>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include "SixAxisRing.h"

void SixAxis::updateAxes() {
	
	/*
	 * Y,A,B,C calculation
	 */

	// Extract and assign analog values from integer array
	int movFH = analogRead(PIN_FRONT_H);
	int movFV = analogRead(PIN_FRONT_V);

	int movRH = analogRead(PIN_RIGHT_H);
	int movRV = analogRead(PIN_RIGHT_V);

	int movBV = analogRead(PIN_BACK_V);

	int movLV = analogRead(PIN_LEFT_V);

	// Calculate output movement values from input analog readings
	movY = (movFV + movRV + movBV + movLV)/4;
	movA = 512 + (movFV - movBV)/2; // pitch
	movB = 1024 - (movFH + movRH)/2; // yaw
	movC = 512 + (movRV - movLV)/2; // roll

	/*
	 * X,Y calculation (only applicable to boards with 8 analog inputs)
	 */

	#if defined(ARDUINO_AVR_MICRO)

	int movBH = analogRead(PIN_BACK_H);
	int movLH = analogRead(PIN_LEFT_H);

	movX = 512 + (movBH - movFH)/2;
	movZ = 512 + (movRH - movLH)/2;
	movB = 1024 - (movFH + movRH + movBH + movLH)/4; // yaw

	#endif

	// Apply small centre-point deadband to outputs
	if (movX < 512 + DEADBAND && movX > 512 - DEADBAND)
		movX = 512;
	if (movY < 512 + DEADBAND && movY > 512 - DEADBAND)
		movY = 512;
	if (movZ < 512 + DEADBAND && movZ > 512 - DEADBAND)
		movZ = 512;
	if (movA < 512 + DEADBAND && movA > 512 - DEADBAND)
		movA = 512;
	if (movB < 512 + DEADBAND && movB > 512 - DEADBAND)
		movB = 512;
	if (movC < 512 + DEADBAND && movC > 512 - DEADBAND)
		movC = 512;

	// Increase sensitivity
	movX = movX + (movX - 512)*RANGE_MULTIPLIER;
	movY = movY + (movY - 512)*RANGE_MULTIPLIER;
	movZ = movZ + (movZ - 512)*RANGE_MULTIPLIER;
	movA = movA + (movA - 512)*RANGE_MULTIPLIER;
	movB = movB + (movB - 512)*RANGE_MULTIPLIER;
	movC = movC + (movC - 512)*RANGE_MULTIPLIER;

	movX = constrain(movX, 0, 1023);
	movY = constrain(movY, 0, 1023);
	movZ = constrain(movZ, 0, 1023);
	movA = constrain(movA, 0, 1023);
	movB = constrain(movB, 0, 1023);
	movC = constrain(movC, 0, 1023);
}

int SixAxis::readX() {
	
	updateAxes();
	return movX;
}

int SixAxis::readY() {

	updateAxes();
	return movY;
}

int SixAxis::readZ() {

	updateAxes();
	return movZ;
}

int SixAxis::readPitch() {

	updateAxes();
	return movA;
}

int SixAxis::readYaw() {

	updateAxes();
	return movB;
}

int SixAxis::readRoll() {

	updateAxes();
	return movC;
}
