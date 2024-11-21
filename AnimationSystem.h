#pragma once
#include <FastLED.h>

#define BOX_SIZE_X 3
#define BOX_SIZE_Y 4

#define BOX_AMT_X 25

#define LED_AMT BOX_SIZE_X * BOX_SIZE_Y*BOX_AMT_X

extern CRGB leds[LED_AMT];

// Updates the currently playing animation
void setCurrentAnimation(int animation);
int getCurrentAnimation();

// Returns the actual id from poxel-box-coordinates
int getPBId(int x, int y);

// Setups the animation system
void setupAnimationSystem();

// Loop to play the animations
void animationSystemLoop();