
#include "Field.h"
#include "TextField.h"
#include "Display.h"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);            // 1602 LCD Setup

// ********************** Access Field Objects **********************

extern TextField registerFinger;
extern TextField setupClass;

extern Field idNo1;
extern Field idNo2;
extern Field idNo3;

extern Field day;                            
extern Field classNo1;
extern Field classNo2;
extern Field classNo3;
extern Field classNo4;
extern Field timeOpen;


//------------------------------------------------D I S P L A Y   S E T U P------------------------------------------------
  void Display::displaySetup()
  {
    lcd.init();                                   // initialise the LCD
    lcd.backlight();                              // Turn on the LCD Backlight
  }


//-------------------------------------------------C L E A R   S C R E E N-------------------------------------------------
  void Display::clearScreen()
  {
    lcd.clear();
  }

  
//---------------------------------------------M A I N   M E N U   S C R E E N---------------------------------------------
  void Display::mainMenuScreen()
  {
    registerFinger.printField();
    setupClass.printField();
  }


//----------------------------------------------E N T E R   I D   S C R E E N----------------------------------------------
  void Display::enterIDScreen()
  {
    lcd.setCursor(0,0);
    lcd.print("ENTER ID NUMBER:");

    lcd.setCursor(6,1);
    lcd.print("#");

    idNo1.printField();
    idNo2.printField();
    idNo3.printField();
  }


//--------------------------------------------I N V A L I D   I D   S C R E E N--------------------------------------------
  void Display::invalidIDScreen()
  {
    lcd.setCursor(0,0);
    lcd.print("   INVALID ID   ");
  }


//----------------------------------------------D I S P L A Y   U S E R   I D----------------------------------------------
  void Display::userID(int idNo)
  {
    lcd.setCursor(0,0);
    lcd.print("   USER  #");
  
    if (idNo < 100)
      lcd.print("0");
    if (idNo < 10)
      lcd.print("0");
    
    lcd.print(idNo);
  }


//------------------------------------------D I S P L A Y   S C A N   F I N G E R------------------------------------------
  void Display::scanFinger()
  {
    lcd.setCursor(0,1);
    lcd.print("  SCAN  FINGER  ");
  }


//----------------------------------------D I S P L A Y   R E M O V E   F I N G E R----------------------------------------
  void Display::removeFinger()
  {
    lcd.setCursor(0,1);
    lcd.print(" REMOVE  FINGER ");
  }


//-------------------------------------------D I S P L A Y   S C A N   A G A I N-------------------------------------------
  void Display::scanAgain()
  {
    lcd.setCursor(0,1);
    lcd.print("   SCAN AGAIN   ");
  }

  
//------------------------------------D I S P L A Y   F I N G E R   R E G I S T E R E D------------------------------------
  void Display::fingerRegistered()
  {
    lcd.setCursor(0,1);
    lcd.print("   REGISTERED   ");
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


//-----------------------------------------A U T H O R I S A T I O N   S C R E E N-----------------------------------------
  void Display::authorisationScreen()
  {
    lcd.setCursor(0,0);                                        
    lcd.print("    SCAN  TO    ");
    lcd.setCursor(0,1);
    lcd.print(" OPEN  REGISTER ");
  }


//----------------------------------------A U T H O R I S A T I O N   S U C C E S S----------------------------------------
  void Display::authorisationSuccess()
  {
    lcd.setCursor(0,0);                                        
    lcd.print("    REGISTER    ");
    lcd.setCursor(0,1);
    lcd.print("      OPEN      ");
  }


//-------------------------------------------A U T H O R I S A T I O N   F A I L-------------------------------------------
  void Display::authorisationFail()
  {
    lcd.setCursor(0,0);                                      
    lcd.print("  AUTHORISATION ");
    lcd.setCursor(0,1);
    lcd.print("     FAILED     ");
  }


//---------------------------------------------S C A N   T O   R E G I S T E R---------------------------------------------
  void Display::scanToRegister()
  {
    lcd.setCursor(0,0);                                        
    lcd.print("    SCAN  TO    ");
    lcd.setCursor(0,1);
    lcd.print("    REGISTER    ");
  }
