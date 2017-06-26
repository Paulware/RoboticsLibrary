/*
 * ArduinoNunchuk.h - Improved Wii Nunchuk library for Arduino
 *
 * Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *
 * Based on the following resources:
 *   http://www.windmeadow.com/node/42
 *   http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
 *   http://wiibrew.org/wiki/Wiimote/Extension_Controllers
 *
 */

#ifndef ArduinoNunchuk_H
#define ArduinoNunchuk_H

#include <Arduino.h>

typedef struct  {
    int analogX;
    int analogY;
    int accelX;
    int accelY;
    int accelZ;
    int zButton;
    int cButton;
} NunchukData;

class ArduinoNunchuk
{
  public:
    int analogX = 0;
    int analogY = 0;
    int accelX = 0;
    int accelY = 0;
    int accelZ = 0;
    int zButton = 0;
    int cButton = 0;

    void init();
    void update();
    
    bool xChanged (int & value ) {
       bool changed = false;
       if (abs(analogX - lastAnalogX) > 10) {
          lastAnalogX = analogX;     
          changed = true;
          value = analogX;
       }
       return changed;
    }   
    
    bool yChanged (int & value ) {
       bool changed = false;
       if (abs(analogY - lastAnalogY) > 10) {
          lastAnalogY = analogY;     
          changed = true;
          value = analogY;
       }
       return changed;
    }   
    
    bool cButtonChanged ( int & value ) {
       bool changed = false;
       if (cButton != lastCButton) {
          lastCButton = cButton;
          changed = true;
          value = cButton;
       }        
       return changed;
    }
    
    bool zButtonChanged ( int & value ) {
       bool changed = false;
       if (zButton != lastZButton) {
          lastZButton = zButton;
          changed = true;
          value = zButton;
       }        
       return changed;
    }    
    int read (bool & changeOccured, bool & fullSpeed); 
  private:
    void _sendByte(byte data, byte location);
    int lastCButton = 0;
    int lastZButton = 0;
    int lastAnalogX = 0;
    int lastAnalogY = 0;
};

#endif
