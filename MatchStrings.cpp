#include "MatchStrings.h"

   MatchStrings::MatchStrings (CommandStringType * _strings){
     numStrings = 0;
     strings = _strings;
   };
    
  void MatchStrings::showStrings() {
    CommandStringType * string;
    Serial.println ("");
    for (int i=0; i<numStrings; i++) {
      Serial.print ( i);
      Serial.print ( ")");
      string = &strings[i];
      Serial.println ( string->str );
    }
  }  
    
  void  MatchStrings::clearIndexes () {
    CommandStringType * string;
    for (int i=0; i<numStrings; i++) {
      string = &strings[i];
      string->index = 0;
    }
  }  
  void  MatchStrings::addString (String str) {
     //Serial.print ("addString ");
     //Serial.print (str);
     //Serial.print (" numStrings: ");
     //Serial.println (numStrings);
     strings[numStrings].str = str;
     numStrings = numStrings + 1;   
     //showStrings();
  }
  
  int  MatchStrings::matchString ( char ch) {
    char c;
    int matched = -1;
    CommandStringType * string;
 
    for (int i=0; i<numStrings; i++) {
      string = &strings[i];
      c = string->str.charAt ( string->index );
      if (ch == c) {
         string->index = string->index + 1;
         /*
         Serial.print (ch);
         Serial.print ( "==");
         Serial.print (c);
         Serial.print ( " ");
         Serial.println ( string->index);
         */
      }
      else {
         string->index = 0;
         /*
         Serial.print (ch);
         Serial.print ( "!=");
         Serial.print (c);
         Serial.print ( " ");
         Serial.println ( string->index );
         */
      }
      //Serial.print (ch);
      //Serial.println ( string->index);      
      
      if (string->index == string->str.length()) {
        matched = i;
        clearIndexes();
        break;
      }
    }
    return matched;
  }




