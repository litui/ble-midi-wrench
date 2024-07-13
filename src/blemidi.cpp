#include "blemidi.hpp"
#include "usbmidi.hpp"

namespace BLEMIDI {

BMDriver bmd = BMDriver();
bool connStatus = false;

void onConnected() {
  if (!connStatus) {
    connStatus = true;
    Graphics::gfx.writeString("BLE Connected");
  }
}

void onDisconnected() {
  if (connStatus) {
    connStatus = false;
    Graphics::gfx.writeString("BLE Disconnected");
  }
}

void onNoteOff(uint8_t channel, uint8_t note, uint8_t velocity, uint16_t timestamp) {
  USBMIDI.sendNoteOff(note, velocity, channel+1);
}

void onNoteOn(uint8_t channel, uint8_t note, uint8_t velocity, uint16_t timestamp) {
  USBMIDI.sendNoteOn(note, velocity, channel+1);
}

void onControlChange(uint8_t channel, uint8_t controller, uint8_t value, uint16_t timestamp) {
  USBMIDI.sendControlChange(controller, value, channel+1);
}

void onPitchBend(uint8_t channel, uint16_t value, uint16_t timestamp) {
  USBMIDI.sendPitchBend(value + MIDI_PITCHBEND_MIN, channel+1);
}

void onAfterTouch(uint8_t channel, uint8_t pressure, uint16_t timestamp) {
  USBMIDI.sendAfterTouch(pressure, channel+1);
}

void onAfterTouchPoly(uint8_t channel, uint8_t note, uint8_t pressure, uint16_t timestamp) {
  USBMIDI.sendPolyPressure(note, pressure, channel+1);
}

void onProgramChange(uint8_t channel, uint8_t program, uint16_t timestamp) {
  USBMIDI.sendProgramChange(program, channel+1);
}

void BMDriver::init() {
  using namespace Graphics;

  BLEMidiServer.begin("BLE MIDI Wrench");
  BLEMidiServer.setOnConnectCallback(onConnected);
  BLEMidiServer.setOnDisconnectCallback(onDisconnected);
  BLEMidiServer.setNoteOffCallback(onNoteOff);
  BLEMidiServer.setNoteOnCallback(onNoteOn);
  BLEMidiServer.setControlChangeCallback(onControlChange);
  BLEMidiServer.setPitchBendCallback(onPitchBend);
  BLEMidiServer.setAfterTouchCallback(onAfterTouch);
  BLEMidiServer.setAfterTouchPolyCallback(onAfterTouchPoly);
  BLEMidiServer.setProgramChangeCallback(onProgramChange);

  gfx.writeString("BLE Awaiting Connection");
}

void BMDriver::tick() {
  // Nothing needed here
}

bool BMDriver::connected() {
  return connStatus;
}

} // namespace BLEMIDI