#undef USB_MANUFACTURER
#define USB_MANUFACTURER "Litui"
#undef USB_PRODUCT
#define USB_PRODUCT "BLE MIDI Wrench"

#include <Arduino.h>
#include <SPI.h>
#include <FS.h>
#include <SPIFFS.h>

#include "graphics.hpp"
#include "blemidi.hpp"
#include "usbmidi.hpp"

void setup() {
  UMIDI::umd.init();
  Graphics::gfx.init();
  BLEMIDI::bmd.init();
}

void loop() {
  UMIDI::umd.tick();
  BLEMIDI::bmd.tick();
}