#include "usbmidi.hpp"
#include "blemidi.hpp"

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, USBMIDI);

namespace UMIDI {

void onNoteOn(midi::Channel channel, byte note, byte velocity) {
  BLEMidiServer.noteOn(channel-1, note, velocity);
}

void onNoteOff(midi::Channel channel, byte note, byte velocity) {
  BLEMidiServer.noteOff(channel-1, note, velocity);
}

void onControlChange(midi::Channel channel, byte controller, byte value) {
  BLEMidiServer.controlChange(channel-1, controller, value);
}

void onPitchBend(midi::Channel channel, int value) {
  BLEMidiServer.pitchBend(channel-1, (uint16_t) (value + abs(MIDI_PITCHBEND_MIN)));
}

void onAfterTouch(midi::Channel channel, byte pressure) {
  BLEMidiServer.afterTouch(channel-1, pressure);
}

void onAfterTouchPoly(midi::Channel channel, byte note, byte pressure) {
  BLEMidiServer.afterTouchPoly(channel-1, note, pressure);
}

void onProgramChange(midi::Channel channel, byte program) {
  BLEMidiServer.programChange(channel-1, program);
}


UMDriver umd = UMDriver();

void UMDriver::init() {
  usb_midi.setStringDescriptor("BLE MIDI Wrench");
  // TinyUSBDevice.setProductDescriptor("BLE MIDI Wrench");
  // TinyUSBDevice.setManufacturerDescriptor("Litui");
  USBMIDI.begin(MIDI_CHANNEL_OMNI);

  USBMIDI.setHandleNoteOn(onNoteOn);
  USBMIDI.setHandleNoteOff(onNoteOff);
  USBMIDI.setHandleControlChange(onControlChange);
  USBMIDI.setHandlePitchBend(onPitchBend);
  USBMIDI.setHandleAfterTouchChannel(onAfterTouch);
  USBMIDI.setHandleAfterTouchPoly(onAfterTouchPoly);
  USBMIDI.setHandleProgramChange(onProgramChange);

  while( !TinyUSBDevice.mounted() ) delay(1);
}

void UMDriver::tick() {
  USBMIDI.read();
}

} // namespace USBMIDI