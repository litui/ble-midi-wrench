#pragma once

#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

extern midi::MidiInterface<midi::SerialMIDI<Adafruit_USBD_MIDI>> USBMIDI;

namespace UMIDI {

class UMDriver {
public:
  UMDriver() {};

  void init();
  void tick();
};

extern UMDriver umd;

} // namespace USBMIDI