
#include "TextField.h"

#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;            // 1602 LCD Setup



TextField::TextField(String _text, int _column, int _row)
  {
    this->cursors = false;
    this->text = _text;
    this->row = _row;
    this->column = _column;
  }


//--------------------------------------------P R I N T   F I E L D--------------------------------------------
  void TextField::printField()
  {
    lcd.setCursor(column, row);                    // move to the specified location on the screen
    
    lcd.print(text);                               // print the text
 

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
  void TextField::selectField()
  {
    cursors = true;
  }


//------------------------------------------D E S E L E C T   F I E L D------------------------------------------
  void TextField::deselectField()
  {
    cursors = false;
  }
  

//---------------------------------------------I S   S E L E C T E D---------------------------------------------
  bool TextField::isSelected()
  {
    return cursors;          // if the cursors are on then it is selected 
  }
//-------------------------------------------P R I N T   C U R S O R S-------------------------------------------  
  void TextField::printCursors()
  {
    lcd.setCursor((column - 1), row);
    lcd.print(">");
  }


//-------------------------------------------R E M O V E   C U R S O R S-------------------------------------------  
  void TextField::removeCursors()
  {
    lcd.setCursor((column - 1), row);
    lcd.print(" ");
  }
  
