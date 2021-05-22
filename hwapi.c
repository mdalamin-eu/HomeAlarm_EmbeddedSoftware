#include "hwapi.h"
#include <REG52.H>
void configureTimerInterrupt();

//INPUTS
sbit WINDOW1 = P0^0;
sbit WINDOW2 = P0^1;
sbit LEAK = P0^2;
sbit FIRE = P0^3;
sbit DOOR1 = P0^4;
sbit DOOR2 = P0^5;
sbit PRESENCE = P0^6;
sbit KEY = P3^0;
sbit RFID = P3^1;

//OUTPUTS
sbit POWER = P1^0;
sbit ACTIVE = P1^1;
sbit SIREN = P1^2;

int seconds = 0;
void initialize() {
  P0 = 0xFF;
  P1 = 0xFF;
  POWER = 1;
  setActiveOff();
  setAlarmOff();
  configureTimerInterrupt();
}

int isKey() {return KEY;}
int isRfid() {return RFID;}
int indoorSensors() {return WINDOW1 || WINDOW2 || LEAK || FIRE;}
int outdoorSensors() {return indoorSensors() || PRESENCE || DOOR1 || DOOR2 ;}
int getSeconds(){return seconds;}

void setAlarmOn() { SIREN = 1;}
void setAlarmOff() { SIREN = 0;}
void setActiveOn() {ACTIVE = 1;}
void setActiveOff() {ACTIVE = 0;}
void showState(state) {P2 = state;}
void resetSeconds() {seconds = 0;}

  
  void configureTimerInterrupt() {
    ET0= 1; TMOD= 0x01; TL0= 0xB7; TH0= 0x3C; TR0= 1; EA = 1;}
  
 
  void incrementSeconds() interrupt 1 {
    static int ticks = 0;
    TL0= 0xB7; TH0= 0x3C; ticks++;
 
    if (ticks == 20) {
      seconds++;
      ticks = 0;
    }
  }
    

