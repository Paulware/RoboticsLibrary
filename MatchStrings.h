#ifndef MATCHSTRINGS_H
#define MATCHSTRINGS_H
#include "Arduino.h"
struct CommandStringType
{
  int index;
  String str;
};

class MatchStrings 
{
  public:
    MatchStrings (CommandStringType * _strings);
    void clearIndexes () ;
    void addString (String str);
    int matchString ( char ch);
    int numStrings;
    CommandStringType * strings;
    void showStrings();
};
#endif
