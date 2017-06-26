/*
 * ArduinoNunchuk.cpp - Improved Wii Nunchuk library for Arduino
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

#define ADDRESS 0x52

#include "ArduinoNunchuk.h"
#if (ARDUINO < 1000)
  #include "../Wire/Wire.h"
#else
  #include <Wire.h>
#endif
void ArduinoNunchuk::init()
{
  Wire.begin();

  ArduinoNunchuk::_sendByte(0x55, 0xF0);
  ArduinoNunchuk::_sendByte(0x00, 0xFB);

  ArduinoNunchuk::update();
}

void ArduinoNunchuk::update()
{
  int count = 0;
  int values[6];

  Wire.requestFrom(ADDRESS, 6);

  while(Wire.available())
  {
    values[count] = Wire.read();
    count++;
  }

  ArduinoNunchuk::analogX = values[0];
  ArduinoNunchuk::analogY = values[1];
  ArduinoNunchuk::accelX = (values[2] << 2) | ((values[5] >> 2) & 3);
  ArduinoNunchuk::accelY = (values[3] << 2) | ((values[5] >> 4) & 3);
  ArduinoNunchuk::accelZ = (values[4] << 2) | ((values[5] >> 6) & 3);
  ArduinoNunchuk::zButton = !((values[5] >> 0) & 1);
  ArduinoNunchuk::cButton = !((values[5] >> 1) & 1);

  ArduinoNunchuk::_sendByte(0x00, 0x00);
}

void ArduinoNunchuk::_sendByte(byte data, byte location)
{
  Wire.beginTransmission(ADDRESS);

  Wire.write(location);
  Wire.write(data);

  Wire.endTransmission();

  delay(10);
}

int ArduinoNunchuk::read (bool & changeOccured, bool & fullSpeed) {
  int done = 1;
  int left = 0;
  int right = 0;
  int forward = 0;
  int backwards = 0;
  int cButton = 0;
  int zButton = 0;
  static int lastState = 0;
  int state = lastState;
  int value = 0;
  static unsigned long timeout = 0;
  int static lastLeft = 0;
  int static lastRight = 0;
  int static lastForward = 0;
  int static lastBackwards = 0;
  bool debugIt = false;
  changeOccured = false;
  bool static lastFullSpeed = false;
  fullSpeed = lastFullSpeed;
  if (millis() > timeout) { // Don't call too often
    timeout = millis() + 50;

    update();
    if (cButtonChanged (value)) {
       if (value == 1) { 
          state = 5;
          changeOccured = true;
       }
    } else if (zButtonChanged (value)) {
       if (value == 1) { 
          state = 5;
          changeOccured = true;
       }
    } else {
      if (xChanged(value)) { 
         if (value > 128) {
           right = value - 128;
         } else if (value < 128) {
           left = 128 - value;
         }
         changeOccured = true;
      } else {
         left = lastLeft;
         right = lastRight;
      }
  
      if (yChanged(value)) {
         if (value > 128) {
           forward = value - 128;
         } else if (value < 128) {
           backwards = 128 - value;
         }
         changeOccured = true;
      } else {
         forward = lastForward;
         backwards = lastBackwards;
      }

      
      if ((right > 10) || (left >10) || (forward > 10) || (backwards > 10) ||(lastState != 0) ) {
        if (changeOccured && debugIt) {
          Serial.print ( "right: " );
          Serial.print (right );
          Serial.print ( " left: " );
          Serial.print (left);
          Serial.print ( " forward: " );
          Serial.print (forward);
          Serial.print ( " backwards: " );
          Serial.println ( backwards);
        }  

        if ((right < 10) && (left < 10) && (forward < 10) && (backwards < 10) ) {
          state = 0;
          changeOccured = true;
        } else { 

          if (right > left) { 
            if ((right > forward) && (right > backwards)) { // right wins
               if (changeOccured && debugIt) { 
                 Serial.println ( "Right wins" );     
               }   
               state = 4;
            }
          } else {
            if ((left > forward) && (left > backwards)) { // left wins
               if (changeOccured && debugIt) {
                 Serial.println ( "Left wins" );           
               }  
               state = 3;
            }
          }

          if (forward > backwards) { 
            if ((forward > right) && (forward > left)) { // forward wins
               if (changeOccured && debugIt) {
                 Serial.println ( "Forward wins" );
               }  
               if (forward > 110) { 
                 fullSpeed = true;
               } else {
                 fullSpeed = false;
               }
               state = 1;
            }
          } else { 
            if ((backwards > right) && (backwards > left)) { // forward wins
               if (changeOccured && debugIt) {
                 Serial.println ( "Backwards wins" );
               }  
               if (backwards > 110) { 
                 fullSpeed = true;
               } else {
                 fullSpeed = false;
               }
               state = 2;
            }        
          } 
        } 
      }   
      lastLeft = left;
      lastRight = right;
      lastForward = forward;
      lastBackwards = backwards;
    }
    if (lastState != state) {
      if (debugIt) {
        Serial.print ( "newState: " );
        Serial.println ( state );
      }
    } else if (lastFullSpeed != fullSpeed) {  
      changeOccured = true;  
    } else {
      changeOccured = false;  
    }
    lastState = state;
    lastFullSpeed = fullSpeed;
  }  
  return state;
}