#include "Animation_Points.h"
#include "AnimationSystem.h"
#include <FastLED.h>
#include <Arduino.h>

#define PT_AMT 20

typedef struct {
  int perc;
  int x;
  int y;
  int clr;
} Point;

void animation_points() {

    static bool requiresSetup = true;
    static Point points[PT_AMT];

    if(requiresSetup){
        requiresSetup = false;
        for(int i=0;i<PT_AMT; i++){
            Point* p = &points[i];
            p->perc = random(60,255);
            p->x = random(0,BOX_SIZE_X * BOX_AMT_X);
            p->y = random(0,4);
            p->clr = random(0,255);
        }
    }

    // Iterates over each point
    for(int i=0;i<PT_AMT;i++){

        Point* p = &points[i];

        p->perc++;

        //Serial.println("i="+String(i)+" perc="+String(p->perc));

        if(p->perc >= 255){
            leds[getPBId(p->x,p->y)] = 0;
            
            p->perc = random(60,255);
            p->x = random(0,BOX_SIZE_X * BOX_AMT_X);
            p->y = random(0,4);
            p->clr = random(0,255);
        }

        leds[getPBId(p->x,p->y)] = CHSV(
            p->clr,
            255,
            p->perc
        );
    }

    FastLED.show();
}