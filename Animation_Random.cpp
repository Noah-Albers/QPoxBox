#include "Animation_Random.h"
#include "AnimationSystem.h"
#include <FastLED.h>
#include <Arduino.h>
#include <EEPROM.h>

#define CFG_OFFSET_CHANCE 5

extern byte anm_random_chanceOn = 10;


void random_setting(byte value) {
    EEPROM.write(CFG_OFFSET_CHANCE, anm_random_chanceOn = value);
    EEPROM.commit();

    Serial.println("Updated [Random] Chance="+String(value));
}

void setup_animation_random() {
    anm_random_chanceOn = EEPROM.read(CFG_OFFSET_CHANCE);
}

void animation_random() {

    EVERY_N_MILLIS(100) {
        for(int i=0;i<30;i++){

            leds[random(0,LED_AMT)] = random(0,anm_random_chanceOn) == 0 ? CHSV(0,0,0) : CHSV(
                random(0,255),
                255,
                255
            );
        }
        FastLED.show();
    }

}