#include "Animation_Rainbow.h"
#include "AnimationSystem.h"
#include <FastLED.h>
#include <Arduino.h>
#include <EEPROM.h>

#define CFG_OFFSET_SPEED 1
#define CFG_OFFSET_OFFSET_X 2
#define CFG_OFFSET_OFFSET_Y 3

byte rainbow_Speed = 100; // v:(0-255) * 100 = Millis-speed
byte rainbow_offset_x = 20; // v:(0-255)*10 = Millis
byte rainbow_offset_y = 40; // v:(0-255)*10 = Millis

void rainbow_setting(byte type, byte value) {
    if(type < 0 || type > 2) return;

    switch(type){
        case 0:
            if(value <= 0) value = 1;
            EEPROM.write(CFG_OFFSET_SPEED, rainbow_Speed = value);
            break;
        case 1: EEPROM.write(CFG_OFFSET_OFFSET_X, rainbow_offset_x = value); break;
        case 2: EEPROM.write(CFG_OFFSET_OFFSET_Y, rainbow_offset_y = value); break;
    }
    EEPROM.commit();

    Serial.println("Updated [Rainbow] "+String(type)+"="+String(value));
}

void animation_rainbow_setup(){
    rainbow_Speed = EEPROM.read(CFG_OFFSET_SPEED);
    rainbow_offset_x = EEPROM.read(CFG_OFFSET_OFFSET_X);
    rainbow_offset_y = EEPROM.read(CFG_OFFSET_OFFSET_Y);
}

void animation_rainbow() {

    for(int y = 0;y<BOX_SIZE_Y;y++){
        for(int x=0;x<BOX_SIZE_X*BOX_AMT_X;x++){

            float perc = (float)((millis() + (rainbow_offset_x*10) * x + (rainbow_offset_y * 10) * y) % (rainbow_Speed * 100)) / (float)(rainbow_Speed * 100);

            if(x==0 && y == 0);
                //Serial.println(perc);

            leds[getPBId(x,y)] = CHSV(
                255*perc,
                255,
                255
            );

        }
    }
    FastLED.show();

}