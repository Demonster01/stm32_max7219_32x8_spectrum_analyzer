#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#define debug

// display settings
int pinCS = PA3; // Attach display CS to this pin (PA3), DIN to SPI1_MOSI (PA7) and CLK to SPI1_SCK (PA5)
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;
int intensity = 7; // Use a value between 0 and 15 for brightness

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

// analog
int audio_in = PB1;

// demo string
String tape = "@2019 ychurov@i.ua";
int wait = 20; // In milliseconds
int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels
int width1 = 0 - width; // need to draw escaping char

// copyright & demo
void startup_demo() {
  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
    matrix.fillScreen(LOW);
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically
    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( x > width1 && letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }
      letter--;
      x -= width;
    }
    matrix.write(); // Send bitmap to display
    delay(wait);
  }
}

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
  // demo
  startup_demo();
}

void loop() {
  // put your main code here, to run repeatedly:
}
