#include <HID-Project.h>
#include <HID-Settings.h>

#include <SixAxisRing.h>

SixAxis myaxis;

void setup() {
  
  // Initialise the HID interface
  Gamepad.begin();
}

void loop() {
  
  // Update axis values (X and Z always return 0 on Uno)
  int movXnew = map(myaxis.readX(), 0, 1023, -32768, 32767);
  int movYnew = map(myaxis.readY(), 0, 1023, -32768, 32767);
  int movZnew = map(myaxis.readZ(), 0, 1023, -128, 127);
  int movAnew = map(myaxis.readPitch(), 0, 1023, -32768, 32767);
  int movBnew = map(myaxis.readYaw(), 0, 1023, -32768, 32767);
  int movCnew = map(myaxis.readRoll(), 0, 1023, -128, 127);

  // Update HID parameters
  Gamepad.xAxis(movXnew);
  Gamepad.yAxis(movYnew);
  Gamepad.zAxis(movZnew);
  Gamepad.rxAxis(movAnew);
  Gamepad.ryAxis(movBnew);
  Gamepad.rzAxis(movCnew);

  // Send the HID report
  Gamepad.write();
}
