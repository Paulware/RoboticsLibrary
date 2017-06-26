#include <Wire.h>
#include <ArduinoNunchuk.h>
ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{
  Serial.begin(9600);
  nunchuk.init();
  Serial.println ( "Ready" );  
}

void loop()
{
  int value;
  nunchuk.update();
  if (nunchuk.cButtonChanged (value)) {
     Serial.print ( "cButton changed to : " );
     Serial.println ( value );
  }
  if (nunchuk.zButtonChanged (value)) {
     Serial.print ( "zButton changed to : " );
     Serial.println ( value );
  }
  if (nunchuk.xChanged(value)) { 
     Serial.print ( "x changed to : " );
     Serial.println ( value );
  }
  if (nunchuk.yChanged(value)) {
     Serial.print ( "y changed to : " );
     Serial.println ( value );
  }
}
