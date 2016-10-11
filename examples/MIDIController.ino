#include <frequencyToNote.h>
#include <MIDIUSB.h>
#include <pitchToNote.h>

#include <SixAxisRing.h>

SixAxis myaxis;

void controlChange(byte channel, byte control, byte value) {
  
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}


void setup() {

}

void loop() {

  // Update axis values (X and Z always return 0 on Uno)
  int movXnew = map(myaxis.readX(), 0, 1023, 0, 127);
  int movYnew = map(myaxis.readY(), 0, 1023, 0, 127);
  int movZnew = map(myaxis.readZ(), 0, 1023, 0, 127);
  int movAnew = map(myaxis.readPitch(), 0, 1023, 0, 127);
  int movBnew = map(myaxis.readYaw(), 0, 1023, 0, 127);
  int movCnew = map(myaxis.readRoll(), 0, 1023, 0, 127);

  // Send CC values
  controlChange(0, 1, movXnew);
  MidiUSB.flush();
  controlChange(0, 2, movYnew);
  MidiUSB.flush();
  controlChange(0, 3, movZnew);
  MidiUSB.flush();
  controlChange(0, 4, movAnew);
  MidiUSB.flush();
  controlChange(0, 5, movBnew);
  MidiUSB.flush();
  controlChange(0, 6, movCnew);
  MidiUSB.flush();

}
