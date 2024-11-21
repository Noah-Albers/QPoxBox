#include "AnimationSystem.h"
#include <FastLED.h>
#include <EEPROM.h>
#include <Arduino.h>
#include "Animation_Rainbow.h"
#include "Animation_Points.h"
#include "Animation_Off.h"
#include "Animation_Random.h"

#define CFG_OFFSET 0

#define LED_PIN 19

// Lookup table for the on-box pixel
int lookUpTable[BOX_SIZE_Y][BOX_SIZE_X] = {
  { 4, 3, 2},
  { 5, 0, 1},
  { 6,11,10},
  { 7, 8, 9}
};



int getPBId(int x, int y){
    // Pre current box
    int boxX = x/BOX_SIZE_X;
    int onBoxX = x % BOX_SIZE_X;
    int lookupId = lookUpTable[y][onBoxX];

    int id = boxX * BOX_SIZE_X * BOX_SIZE_Y + lookupId;

    //Serial.println("X:"+String(x)+" / "+String(y)+" = "+String(id)+" (LookupId="+String(lookupId)+") (BoxX = "+String(boxX)+") (onBoxX = "+onBoxX+")");

    return id;
}


// Which animation is playing
int currentAnimation = 1;

// LED-Api
CRGB leds[LED_AMT];

void setCurrentAnimation(int animation) {
  currentAnimation = animation;
  EEPROM.write(CFG_OFFSET, currentAnimation);
  EEPROM.commit();

  Serial.println("Changed to animation "+String(animation));
}

int getCurrentAnimation() {
  return currentAnimation;
}

void setupAnimationSystem() {

  // Setups fastled-library
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_AMT);

  // Sets the current animation from eeprom
  setCurrentAnimation(EEPROM.read(CFG_OFFSET));

  // Setups the animations
  animation_rainbow_setup();
  setup_animation_random();
}

void animationSystemLoop() {
  switch(currentAnimation){
    case 1: animation_rainbow(); break;
    case 2: animation_points(); break;
    case 3: animation_off(); break;
    case 4: animation_random(); break;
  }
}