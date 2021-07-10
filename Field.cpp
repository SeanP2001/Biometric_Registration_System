
#include "Field.h"

#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;            // 1602 LCD Setup



Field::Field(enum Field::Format _format, int _value, int _column, int _row)
  {
    this->cursors = false;
    this->format = _format;
    this->value = _value;
    this->row = _row;
    this->column = _column;
  }


//--------------------------------------------P R I N T   F I E L D--------------------------------------------
  void Field::printField()
  {
    lcd.setCursor(column, row);                    // move to the specified location on the screen
    
    if (format == DAY)                             // DAY FIELDS
    {    
      switch(value) {                              // display the day
      case 1 : lcd.print("MON"); break;
      case 2 : lcd.print("TUE"); break;
      case 3 : lcd.print("WED"); break;
      case 4 : lcd.print("THU"); break;
      case 5 : lcd.print("FRI"); break;
      }
    }
    if (format == NUMBER)                          // NUMBER FIELDS
    {
      if (value < 10)                              // values above 9 represent a blank digit
      {
        lcd.print(value);                          // print digits that are not blank
      }
    }
    if (format == TIME)                            // TIME FIELDS
    {
      lcd.print(value);                            // print the time
    }
  }
  
