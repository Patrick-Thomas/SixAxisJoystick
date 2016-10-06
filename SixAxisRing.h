/*
 Copyright (C) 2016 P. Thomas <patrick.thomas@bath.edu>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * @file SixAxis.h
 *
 * Class declaration for Six Axis
 */

#ifndef __SIXAXIS_H__
#define __SIXAXIS_H__

#include <Arduino.h>

#define DEADBAND 25
#define RANGE_MULTIPLIER 1.1

#define OLD_SHIELD 1

#if defined(OLD_SHIELD)

#define PIN_FRONT_H A0
#define PIN_FRONT_V A1
#define PIN_RIGHT_H A2
#define PIN_RIGHT_V A3
#define PIN_BACK_H A4
#define PIN_BACK_V A5
#define PIN_LEFT_H A7
#define PIN_LEFT_V A6

#else

#define PIN_FRONT_H A0
#define PIN_FRONT_V A1
#define PIN_LEFT_H A2
#define PIN_LEFT_V A3
#define PIN_BACK_V A4
#define PIN_RIGHT_V A5

#if defined(ARDUINO_AVR_MICRO)

#define PIN_BACK_H A6
#define PIN_RIGHT_H A7

#endif

#endif

class SixAxis {

private:

	int axisValues[6];
	void updateAxes();

	int movX, movY, movZ, movA, movB, movC;

public:

	SixAxis() {

	}

	int readX();
	int readY();
	int readZ();
	int readPitch();
	int readYaw();
	int readRoll();
};

#endif // __SIXAXIS_H__


