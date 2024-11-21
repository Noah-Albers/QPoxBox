#include "Server.h"
#include "AnimationSystem.h"
#include <EEPROM.h>

// Amount of Config-values to use
#define EEPROM_SIZE 6

void setup(){
  Serial.begin(9600);

  // Setups the EEPROM
  EEPROM.begin(EEPROM_SIZE);

  setupServer();

  setupAnimationSystem();
}

void loop(){
  handleClient();

  animationSystemLoop();

  delay(30);
}