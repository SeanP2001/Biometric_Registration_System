
#include "Field.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);            // 1602 LCD Setup



Field::Field(enum Field::Format _format, int _value, int _column, int _row)
  {
    this->cursors = false;
    this->format = _format;
    this->value = _value;
    this->row = _row;
    this->column = _column;
  }

  void Field::displaySetup(){
    lcd.init();                                   // initialise the LCD
    lcd.backlight();                              // Turn on the LCD Backlight
  }

  void Field::printField()
  {
    if (format == NUMBER)
    {
      lcd.setCursor(column, row);
      lcd.print(value);
    }
  }
  
