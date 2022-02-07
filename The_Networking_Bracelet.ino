///////////////////////////////////////////////////////////////////////////////
/*
Advanced Wearable Technolgy - OCAD U - Winter 2022
The Networking Bracelet : By Patricia Mwenda
This project uses a circuit playground express to light up different animation sequences 
Created Feb, 06th, 2022

///////////////////////////////////////////////////////////////////////////////

Based on:
Code for (Gaming Wearables) Glowing LED Team Badge for Pokemon Go by Richard Albritton - Adafruit
July 19, 2016 - (updated) Feb 18, 2021.

And

Circuit Playground Bike Light - The All Of Them
Author: Carter Nelson
 MIT License (https://opensource.org/licenses/MIT)
*/
///////////////////////////////////////////////////////////////////////////////
#include <Adafruit_CircuitPlayground.h>
// Variables will change:
int ledState = 0;            // the current state of the output pin
int buttonState ;            // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int ColorState;              // the previous Color set
int R = 0;
int G = 0;
int B = 0;

int pixel1 = 0;
int pixel2 = 9;

bool slideSwitch;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 0;    // the debounce time; increase if the output flickers

// Change these to be whatever color you want
// Use color picker to come up with hex values
#define FLASH_COLOR        0x0000FF //BLUE - PROFESSIONALS/EMPLOYERS
#define ANIMATION_COLOR    0x00FF00 //GREEN - RECRUITERS
#define CYLON_COLOR        0x808000 //YELLOW - STUDENTS

// Change these to set speed (lower is faster)
#define FLASH_RATE      500
#define ANIMATION_RATE  100
#define CYLON_RATE      200


void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(50);
}

void loop() {
  //Turns everything off to preserve the energy
  if (!CircuitPlayground.slideSwitch()) {
    CircuitPlayground.clearPixels();
    return;
  }

  // reads the state of the button into a local variable:
  int reading = CircuitPlayground.leftButton();


  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;


      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ++ledState;

      }
    }
  }

  // set the Animations:
  // do something different depending on the range value:

  switch (ledState) {
    case 0:
      R = 0;
      G = 0;
      B = 0;
      ColorState = 0;
    case 1:  //PROFESSINALS/EMPLOYERS - BLUE(PROFESSIONALISM)
      // Turn on all the pixels to FLASH_COLOR
      for (int pixel = 0; pixel < 10; pixel++) {
        CircuitPlayground.setPixelColor(pixel, FLASH_COLOR);
      }
      // Leave them on for a little bit
      delay(FLASH_RATE);
      // Turn off all the NeoPixels
      CircuitPlayground.clearPixels();
      // Leave them off for a little bit
      delay(FLASH_RATE);
      break;

    case 2:    //RECUITERS - GREEN(SERACHING, TRACKING)
      // Turn on all the pixels to ANIMATION_COLOR
      for (int pixel = 0; pixel < 10; pixel++) {
        // Turn OFF all pixels
        CircuitPlayground.clearPixels();
        // Turn ON the current pixel to COLOR
        CircuitPlayground.setPixelColor(pixel, ANIMATION_COLOR);
        // Don't spin too fast
        delay(ANIMATION_RATE);
      }
      break;

    case 3:    //STUDENTS - YELLOW(CURIOSITY, YOUTH, OPTIMISM)
      // Turn on all the pixels to CYLON_COLOR
      for (int step = 0; step < 4; step++) {
        CircuitPlayground.clearPixels();

        CircuitPlayground.setPixelColor(pixel1, CYLON_COLOR);
        CircuitPlayground.setPixelColor(pixel2, CYLON_COLOR);

        pixel1 = pixel1 + 1;
        pixel2 = pixel2 - 1;

        delay(CYLON_RATE);
      }

      // Scan back the other direction
      for (int step = 0; step < 4; step++) {
        CircuitPlayground.clearPixels();

        CircuitPlayground.setPixelColor(pixel1, CYLON_COLOR);
        CircuitPlayground.setPixelColor(pixel2, CYLON_COLOR);

        pixel1 = pixel1 - 1;
        pixel2 = pixel2 + 1;

        delay(CYLON_RATE);
      }
      break;
      
    case 4:    // Return to oringinal state
      ledState = 0;
      break;
  }
  delay(1);        // delay in between reads for stability

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;

}
