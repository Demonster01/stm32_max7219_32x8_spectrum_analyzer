#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#define debug

// display settings
int pinCS = PA3; // Attach display CS to this pin (PA3), DIN to SPI1_MOSI (PA7) and CLK to SPI1_SCK (PA5)
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;
intensity = 7; // Use a value between 0 and 15 for brightness

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

// analog
const int audio_in = PB1;

void setup() {
  // put your setup code here, to run once:
  #ifdef debug
    Serial.begin(115200);
    Serial.println();
  #endif

  // init displays
  for (int i = 0; i < numberOfHorizontalDisplays; i++) {
    matrix.setPosition(i, i, 0); // all displays stays in one row
    matrix.setRotation(i, 1);    // all displays position is 90 degrees clockwise
  }
  matrix.setIntensity(intensity); // Use a value between 0 and 15 for brightness
  // clear screen
  matrix.fillScreen(LOW);
  matrix.write();
}

void loop() {
  // put your main code here, to run repeatedly:
}
