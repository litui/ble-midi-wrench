#include "graphics.hpp"

SPIClass SPI1 = SPIClass(2);

namespace Graphics {

GFXDriver gfx = GFXDriver();

void GFXDriver::init() {
  SPI1.begin(TFT_SCLK, TFT_MISO, TFT_MOSI, TFT_CS);
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("BLE MIDI Wrench", MARGIN, MARGIN, 4);

  int16_t headerHeight = tft.fontHeight(4) + 2;
  int16_t textHeight = tft.fontHeight(2) + 1;

  tft.setViewport(MARGIN, MARGIN + headerHeight, TFT_WIDTH - MARGIN*2, TFT_HEIGHT - MARGIN*2 - headerHeight);
  tft.frameViewport(TFT_BROWN, -1);
  tft.setTextFont(2);

  bufferLines = tft.getViewportHeight() / textHeight;
  initBuffer();

  // for (uint8_t i = 1; i < bufferLines; i++) {
  //   shiftBuffer("Test...");
  // }

  // Enable backlight
  digitalWrite(GPIO_NUM_9, HIGH);
}

void GFXDriver::initBuffer() {
  buffer = (char**) malloc(bufferLines * sizeof(char *));

  for (uint8_t col = 0; col < bufferLines; col++) {
    buffer[col] = (char*) malloc(1 * sizeof(char));
    buffer[col][0] = '\0';
  }
}

void GFXDriver::shiftBuffer(const char *msg) {
  free(buffer[0]);

  for (uint8_t i = 0; i < bufferLines-1; i++) {
    buffer[i] = buffer[i+1];
  }

  buffer[bufferLines-1] = (char*) malloc((strlen(msg) + 1) * sizeof(char));
  memcpy(buffer[bufferLines-1], msg, strlen(msg)+1);

  // tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  
  for (uint8_t i = 0; i < bufferLines; i++) {
    if (buffer[i][0] != '\0') {
      tft.printf("%s\n", buffer[i]);
    }
  }
}

void GFXDriver::writeString(String msg) {
  shiftBuffer(msg.c_str());
}

void GFXDriver::writeString(const char* msg) {
  shiftBuffer(msg);
}

} // namespace Graphics