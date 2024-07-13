#pragma once
#include <BLEMidi.h>
#include "graphics.hpp"

namespace BLEMIDI {

class BMDriver {
public:
  BMDriver() {};

  void init();
  void tick();

  bool connected();
};

extern BMDriver bmd;

} // namespace BLEMIDI