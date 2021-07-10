//------------------------------------------------------------------------------------------------------------------------------------------------------------
// Biometric Registration System
// Sean Price
// V0.5
// Completed the class setup screen with button and keypad inputs to set the field contents
//------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <Keypad_I2C.h>

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



 //                 ********************************* KEYPAD VARIABLES ***********************************
#define I2CADDR 0x20                         // Set the I2C Address of the keypad

const byte ROWS = 4;                         // Number of keypad Rows
const byte COLS = 4;                         // Number of keypad Columns

char keys [ROWS] [COLS] = {                  // Keypad matrix
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins [ROWS] = {0, 1, 2, 3};          // Keypad row pins
byte colPins [COLS] = {4, 5, 6, 7};          // Keypad column pins

Keypad_I2C keypad(makeKeymap (keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);

 
//----------------------------------------------------------------S E T U P----------------------------------------------------------------
void setup() 
{
  display.displaySetup();                            // Setup the display
  keypad.begin(makeKeymap (keys));                   // setup the keypad
}


//-----------------------------------------------------------------M A I N-----------------------------------------------------------------
void loop() 
{
  day.selectField();                                   // select the day field

  while (day.isSelected())                             // WHILE THE DAY IS SELECTED
  {
    display.classSetupScreen();                        // Print the class setup screen
    
    if (left.buttonIsPressed())                        // the left button decrements days
    {
      day.decrementDays();
    }
    if (right.buttonIsPressed())                       // the right button increments days
    {
      day.incrementDays();
    }
    if (middle.buttonIsPressed())                      // the middle button selects the next field
    {
      selectNextField();
    }
  }


  
  while (classNo1.isSelected())                        // WHILE CLASSNO1 IS SELECTED
  {
    getAndPrintNumber(classNo1);                       // get and print the number
  }
  while (classNo2.isSelected())                        // WHILE CLASSNO2 IS SELECTED
  {
    getAndPrintNumber(classNo2);                       // get and print the number
  }
  while (classNo3.isSelected())                        // WHILE CLASSNO3 IS SELECTED
  {
    getAndPrintNumber(classNo3);                       // get and print the number
  }
  while (classNo4.isSelected())                        // WHILE CLASSNO4 IS SELECTED
  {
    getAndPrintNumber(classNo4);                       // get and print the number
  }
    
  
  while (timeOpen.isSelected())                        // WHILE TIME OPEN IS SELECTED
  {
    display.classSetupScreen();                        // Print the class setup screen
     
    if (left.buttonIsPressed())                        // the left button decrements time
    {
      timeOpen.decrementTime();
    }
    if (right.buttonIsPressed())                       // the left button increments time
    {
      timeOpen.incrementTime();
    }
    if (middle.buttonIsPressed())
    {
      //MOVE TO THE NEXT SCREEN
    }
  }
  
} 


//-------------------------------------------------G E T   A N D   P R I N T   N U M B E R-------------------------------------------------
void getAndPrintNumber(Field &field)
{
  
  display.classSetupScreen();                                 // Print the class setup screen
    
  while((field.value = (int)(keypad.getKey()))==NO_KEY) {     // wait for a key to be pressed and set the classNo value to that number
    delay(1);                                            
  } 

  field.value = field.value - 48;                             // convert char value to int value ( 1 = 49 )

  display.classSetupScreen();                                 // Print the class setup screen

  selectNextField();
}

//----------------------------------------------------S E L E C T   N E X T   F I E L D----------------------------------------------------
void selectNextField()
{
  if (day.isSelected())                       
  {
    day.deselectField();
    classNo1.selectField();
  }
  else if (classNo1.isSelected())
  {
    classNo1.deselectField();
    classNo2.selectField();
  }
  else if (classNo2.isSelected())
  {
    classNo2.deselectField();
    classNo3.selectField();
  }
  else if (classNo3.isSelected())
  {
    classNo3.deselectField();
    classNo4.selectField();
  }
  else if (classNo4.isSelected())
  {
    classNo4.deselectField();
    timeOpen.selectField();
  }
}
