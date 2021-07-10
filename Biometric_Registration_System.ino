//------------------------------------------------------------------------------------------------------------------------------------------------------------
// Biometric Registration System
// Sean Price
// V0.4
// Added the Button class and the selectNextField function
//------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "Field.h"
#include "Display.h"
#include "Button.h"

                      //***** Field obj(Format, Value, Column, Row) ******//

 Field day(Field::DAY, 1, 1, 0);                 // Setup day field (Monday by default)

 Field classNo1(Field::NUMBER, 10, 11, 0);       // Setup classNo digit fields
 Field classNo2(Field::NUMBER, 10, 12, 0);       // All of the digits are blank (10) by default
 Field classNo3(Field::NUMBER, 10, 13, 0);
 Field classNo4(Field::NUMBER, 10, 14, 0);

 Field timeOpen(Field::TIME, 10, 6, 1);          // Setup timeOpen Field (10 mins by default)

 Display display; 

 Button left(700, 100);
 Button middle(500, 100);
 Button right(300, 100);

 
//----------------------------------------------------------------S E T U P----------------------------------------------------------------
void setup() 
{
  display.displaySetup();                            // Setup the display
}


//-----------------------------------------------------------------M A I N-----------------------------------------------------------------
void loop() 
{
  day.selectField();
  int i = 0;
  while (i < 6)
  {
    display.classSetupScreen();                        // Print the class setup screen
    if (middle.buttonIsPressed())
    {
      selectNextField();
      i++;
    }
  }
  timeOpen.deselectField();
} 


//----------------------------------------------------S E L E C T   N E X T   F I E L D----------------------------------------------------
void selectNextField()
{
  if (day.cursors == true)
  {
    day.deselectField();
    classNo1.selectField();
  }
  else if (classNo1.cursors == true)
  {
    classNo1.deselectField();
    classNo2.selectField();
  }
  else if (classNo2.cursors == true)
  {
    classNo2.deselectField();
    classNo3.selectField();
  }
  else if (classNo3.cursors == true)
  {
    classNo3.deselectField();
    classNo4.selectField();
  }
  else if (classNo4.cursors == true)
  {
    classNo4.deselectField();
    timeOpen.selectField();
  }
}
