#pragma once
#include <TFT_eSPI.h>

#define MARGIN 10

extern SPIClass SPI1;

namespace Graphics {

enum class Subsystem {
  BLE = 0,
  USB,
};

enum class MidiType {
  NOTE_OFF = 0,
  NOTE_ON,
  POLY_AFT,
  CTRL_CHG,
  PRGM_CHG,
  CHAN_AFT,
  PITCH,
};

class GFXDriver {
public:
  GFXDriver() {};

  void init();

  void writeString(String msg);
  void writeString(const char* msg);
  void writeMidiLog(Subsystem subsystem, uint8_t channel, MidiType type, uint32_t value);

private:
  TFT_eSPI tft = TFT_eSPI();
  uint8_t bufferLines = 12;

  void initBuffer();
  void shiftBuffer(const char *);

  char **buffer;
};

extern GFXDriver gfx;

} // namespace Graphics