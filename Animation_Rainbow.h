#pragma once
#include <Arduino.h>


extern byte rainbow_Speed;
extern byte rainbow_offset_x;
extern byte rainbow_offset_y;


// TODO: Comments

void animation_rainbow();

void rainbow_setting(byte type, byte value);

void animation_rainbow_setup();