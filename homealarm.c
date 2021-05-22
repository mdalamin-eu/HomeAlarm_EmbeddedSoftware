#pragma NOEXTEND
#include "hwapi.h"

void main() {
  enum {INACTIVE,INDOORS,OUTDOORS,DELAY,ALARM} device_state = INACTIVE;
  initialize();
  while (1) {
    showState(device_state);
    switch (device_state) {
      case INACTIVE:
        if (isKey()) {
            device_state = INDOORS;
            setActiveOn();
             
        }
        break;
      case  INDOORS:
        if (indoorSensors()) {
          device_state = ALARM;
        }
        else if (isRfid()) {
          device_state = OUTDOORS;
        }
        else if (isKey()==0) {
          device_state = INACTIVE;
          setActiveOff();
        }
        break;
      
      case OUTDOORS:
        if (indoorSensors() || outdoorSensors()) {
          resetSeconds();
          device_state = DELAY;
        }
        else if (isRfid()==0) {
          device_state = INDOORS;
        }
        break;
      
      case DELAY:
        if (isRfid() == 0) {
           device_state = INDOORS;
        }
        else if (indoorSensors() == 0 && outdoorSensors() == 0) {
           device_state = OUTDOORS;
        }
        else if (getSeconds() >= 5) {
          device_state = ALARM;
        }
        break;
      
      case ALARM:
         setAlarmOn();
         if (isKey()== 0) {
           setAlarmOff();
           setActiveOff();
           device_state = INACTIVE;
         }
         break;
       }
     }
 }

 