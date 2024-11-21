#include "Animation_Off.h"
#include <FastLED.h>
#include <Arduino.h>
#include "AnimationSystem.h"

long anm_off_lastTrigger = 0;

void animation_off(){
    if(((long)millis()) - anm_off_lastTrigger >=  0){
        anm_off_lastTrigger = millis()+1000;

        for(int i=0;i<LED_AMT;i++)
            leds[i] = 0;

        FastLED.show();
    }
}