#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <IR.h>
#include <IRPipboy.h>
#include <TimerOne.h>

#define IRRECEIVEPIN 17
#define IRTRANSMITPIN 3

IRPipboy ir (IRRECEIVEPIN, IRTRANSMITPIN, &Timer1, false);
ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{
  Serial.begin(9600);
  nunchuk.init();
  Serial.println ( "Ready" ); 
  pinMode (2,OUTPUT);
  digitalWrite (2,0); 
}

// IR cmds: use 8 bits
// e q w d for direction
// k = fire
// 0 1 2 for speed 
void loop()
{
  int value;
  int speed;
  char ch;
  nunchuk.update();
  if (nunchuk.cButtonChanged (value)) {
     Serial.print ( "cButton changed to : " );
     Serial.println ( value );
     ir.createFireSequence ('k');
     ir.fireData();     
  }
  if (nunchuk.zButtonChanged (value)) {
     Serial.print ( "zButton changed to : " );
     Serial.println ( value );
     ir.createFireSequence ('k');
     ir.fireData();     
  }
  if (nunchuk.xChanged(value)) { 
     Serial.print ( "x changed to : " );
     Serial.println ( value );
     // left = x == 1
     if (value < 100) { // moving to the left
        speed = (128 - value) / 10;              
        ch = 'O' + speed;
     } else if (value > 100) { // moving to the right
        speed = (value - 128) / 10;
        ch = ' ' + speed;
     } else { 
        ch = ' ';   
     }    
     Serial.print ( "Fire: [" );
     Serial.print ( ch ); 
     Serial.println ( "]" );
     ir.createFireSequence(ch);
     ir.fireData();     
  }
  
  if (nunchuk.yChanged(value)) {
     Serial.print ( "y changed to : " );
     Serial.println ( value );
     if (value > 128) { // moving forward
        speed = (value - 128) / 10;              
        ch = '1' + speed;
     } else if (value < 128) { // moving backward
        speed = (128 - value) / 10;
        ch = 'A' + speed;
     } else { 
        ch = ' ';   
     }    
     Serial.print ( "Fire: [" );
     Serial.print ( ch ); 
     Serial.println ( "]" );
     ir.createFireSequence(ch);
     ir.fireData();      
     ir.createFireSequence(ch);
     ir.fireData();     
  }
}
