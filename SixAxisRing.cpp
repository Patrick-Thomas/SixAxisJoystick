/*
 Copyright (C) 2016 P. Thomas <patrick.thomas@bath.edu>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include "SixAxisRing.h"

void SixAxis::updateAxes() {
	
	// Extract and assign analog values from integer array
	int movFH = analogRead(PIN_FRONT_H);
	int movFV = analogRead(PIN_FRONT_V);

	int movRH = analogRead(PIN_RIGHT_H);
	int movRV = analogRead(PIN_RIGHT_V);

	int movBH = analogRead(PIN_BACK_H);
	int movBV = analogRead(PIN_BACK_V);

//	int movLH = analogRead(PIN_LEFT_H);
//	int movLV = analogRead(PIN_LEFT_V);

	// Calculate output movement values from input analog readings
	movX = 512 + (movFH - movBH)/2;
	movY = 1024 - (movFV + movRV + movBV)/3;
	movZ = movRH;
	movA = 512 + (movFV - movBV)/2; //pitch
	movB = 1024 - (movFH + movRH + movBH)/3; //yaw
	movC = movRV; //roll

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
