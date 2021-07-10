
#ifndef _FIELD_H_
#define _FIELD_H_

#include <Arduino.h>

class Field{
public:

  enum Format {     
    UNSPECIFIED,                       
    DAY,
    NUMBER,
    TIME,
  };

  bool cursors;
  Format format;
  int value;
  int row;
  int column;
  
  Field(enum Field::Format _format, int _value, int _column, int _row);
  
  void printField();
};

#endif // _FIELD_H_
