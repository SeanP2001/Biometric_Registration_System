
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
      if (value < 10)
      {
        lcd.print("0");
      }
      lcd.print(value);                            // print the time
    }

    if (cursors == true)
    {
      printCursors();
    }
    else
    {
      removeCursors();
    }
  }


//--------------------------------------------S E L E C T   F I E L D--------------------------------------------
  void Field::selectField()
  {
    cursors = true;
  }


//------------------------------------------D E S E L E C T   F I E L D------------------------------------------
  void Field::deselectField()
  {
    cursors = false;
  }


//------------------------------------------I N C R E M E N T   D A Y S------------------------------------------
  void Field::incrementDays()
  {
    if (value >= 5)          // if the day is set to Friday
    {
      value = 1;             // increment it to Monday
    }
    else
    {
      value++;               // otherwise just increment normally
    }  
  }


//------------------------------------------D E C R E M E N T   D A Y S------------------------------------------  
  void Field::decrementDays()
  {
    if (value <= 1)          // if the day is set to Monday
    {
      value = 5;             // decrement it to Friday
    }
    else
    {
      value--;               // otherwise just decrement normally
    } 
  }


//------------------------------------------I N C R E M E N T   T I M E------------------------------------------
  void Field::incrementTime()
  {
    if (value < 20)          // if less than 20 minutes
    {
      value = value + 5;     // increment the time by 5 minutes
    }
  }


//------------------------------------------D E C R E M E N T   T I M E------------------------------------------  
  void Field::decrementTime()
  {
    if (value > 5)          // if more than 5 minutes
    {
      value = value - 5;    // decrement the time by 5 minutes
    }
  }
  

//---------------------------------------------I S   S E L E C T E D---------------------------------------------
  bool Field::isSelected()
  {
    return cursors;          // if the cursors are on then it is selected 
  }
//-------------------------------------------P R I N T   C U R S O R S-------------------------------------------  
  void Field::printCursors()
  {
    if (format == DAY)
    {
      lcd.setCursor((column - 1), row);
      lcd.print(">");
      lcd.setCursor((column + 3), row);
      lcd.print("<");
    }
    if (format == NUMBER)
    {
      lcd.setCursor(column, row);
      lcd.print("_");
    }
    if (format == TIME)
    {
      lcd.setCursor((column - 1), row);
      lcd.print(">");
      lcd.setCursor((column + 2), row);
      lcd.print("<");
    }
  }


//-------------------------------------------R E M O V E   C U R S O R S-------------------------------------------  
  void Field::removeCursors()
  {
    if (format == DAY)
    {
      lcd.setCursor((column - 1), row);
      lcd.print(" ");
      lcd.setCursor((column + 3), row);
      lcd.print(" ");
    }
    if (format == TIME)
    {
      lcd.setCursor((column - 1), row);
      lcd.print(" ");
      lcd.setCursor((column + 2), row);
      lcd.print(" ");
    }
  }
  
