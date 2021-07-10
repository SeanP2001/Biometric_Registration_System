//------------------------------------------------------------------------------------------------------------------------------------------------------------
// Biometric Registration System
// Sean Price
// V0.3
// Setup the selectField, deselectField, printCursors and removeCursors functions 
//------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "Field.h"
#include "Display.h"

                      //***** Field obj(Format, Value, Column, Row) ******//

 Field day(Field::DAY, 1, 1, 0);                 // Setup day field (Monday by default)

 Field classNo1(Field::NUMBER, 10, 11, 0);       // Setup classNo digit fields
 Field classNo2(Field::NUMBER, 10, 12, 0);       // All of the digits are blank (10) by default
 Field classNo3(Field::NUMBER, 10, 13, 0);
 Field classNo4(Field::NUMBER, 10, 14, 0);

 Field timeOpen(Field::TIME, 10, 6, 1);          // Setup timeOpen Field (10 mins by default)

 Display display; 


//----------------------------------------------------------------S E T U P----------------------------------------------------------------
void setup() 
{
  display.displaySetup();                            // Setup the display
}


//-----------------------------------------------------------------M A I N-----------------------------------------------------------------
void loop() 
{
  day.selectField();
  display.classSetupScreen();                        // Print the class setup screen
  delay(2000);
  day.deselectField();
  timeOpen.selectField();
  display.classSetupScreen();                        // Print the class setup screen
  delay(2000);
  timeOpen.deselectField();
} 
