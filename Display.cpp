
#include "Field.h"
#include "Display.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);            // 1602 LCD Setup

extern Field day;                            // access Field objects 
extern Field classNo1;
extern Field classNo2;
extern Field classNo3;
extern Field classNo4;
extern Field timeOpen;


//------------------------------------------------D I S P L A Y   S E T U P------------------------------------------------
  void Display::displaySetup(){
    lcd.init();                                   // initialise the LCD
    lcd.backlight();                              // Turn on the LCD Backlight
  }


//-------------------------------------------C L A S S   S E T U P   S C R E E N-------------------------------------------
  void Display::classSetupScreen()
  {
    day.printField();                                      // print the day
    
    lcd.setCursor((classNo1.column - 4), classNo1.row);    // print class prefix
    lcd.print("ICE-");
    
    classNo1.printField();                                 // print the class number
    classNo2.printField();
    classNo3.printField();
    classNo4.printField();

    lcd.setCursor((timeOpen.column - 6), timeOpen.row);    // print the time open
    lcd.print("OPEN:");
    
    timeOpen.printField();                                 
    
    lcd.setCursor((timeOpen.column + 3), timeOpen.row);
    lcd.print("MINS");
  }
  
