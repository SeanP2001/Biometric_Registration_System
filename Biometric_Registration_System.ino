//------------------------------------------------------------------------------------------------------------------------------------------------------------
// Biometric Registration System
// Sean Price
// V1.0
// Fixed device reset and updated README.md
//------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <Keypad_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <math.h>


#include "Field.h"
#include "TextField.h"
#include "Display.h"
#include "Button.h"
#include "Register.h"


 void(* resetFunc) (void) = 0;                   // reset function declared at address 0

                         //***** TextField obj(Text, Column, Row) ******//
 TextField registerFinger("REGISTER FINGER", 1, 0);
 TextField setupClass("SETUP CLASS", 1, 1);
 
                      //***** Field obj(Format, Value, Column, Row) ******//

 Field idNo1(Field::NUMBER, 10, 7, 1);           // Setup idNo digit fields
 Field idNo2(Field::NUMBER, 10, 8, 1);           // All of the digits are blank (10) by default
 Field idNo3(Field::NUMBER, 10, 9, 1);
                      
 Field day(Field::DAY, 1, 1, 0);                 // Setup day field (Monday by default)

 Field classNo1(Field::NUMBER, 10, 11, 0);       // Setup classNo digit fields
 Field classNo2(Field::NUMBER, 10, 12, 0);       // All of the digits are blank (10) by default
 Field classNo3(Field::NUMBER, 10, 13, 0);
 Field classNo4(Field::NUMBER, 10, 14, 0);

 Field timeOpen(Field::TIME, 10, 6, 1);          // Setup timeOpen Field (10 mins by default)

                                  //***** Display obj ******//
 Display display; 

                       //***** Button obj(AnalogValue, Tolerance) ******//
 Button left(700, 100);          
 Button middle(500, 100);
 Button right(300, 100);

                                 //***** Register obj ******//
 Register registration;

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


//               ***************************** FINGER SCANNING VARIABLES *****************************
int id = 0;                                   // variable storing user typed ID for enrollment

volatile int fingerID = -1;                  // variable storing scanned finger ID

SoftwareSerial mySerial(2, 3);               // TX/RX on fingerprint sensor

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

bool authorised = false;                     // variable indicating if the register has been authorised

int startTime = 0;                           // variable storing the time that the register opened

 
//----------------------------------------------------------------S E T U P----------------------------------------------------------------
void setup() 
{
  display.displaySetup();                            // setup the display
  keypad.begin(makeKeymap (keys));                   // setup the keypad
  finger.begin(57600);                               // setup fingerprint scanner
  registration.setup(9600);                          // setup the register serial connection
}


//-----------------------------------------------------------------M A I N-----------------------------------------------------------------
void loop() 
{ 
  mainMenu();                                          // go to the main menu
} 


//------------------------------------------------------------M A I N   M E N U------------------------------------------------------------
void mainMenu()
{
  display.clearScreen();                               // clear the screen
  
  registerFinger.selectField();                        // select register finger
  
  while (registerFinger.isSelected())                  // WHILE THE REGISTER FINGER OPTION IS SELECTED
  {
    display.mainMenuScreen();                          // update the display
    
    if (right.buttonIsPressed())                       // the right button moves the cursor down
    {
      registerFinger.deselectField();
      setupClass.selectField();
    }
    if (middle.buttonIsPressed())                      // the middle button opens the finger registration
    {
      registerFinger.deselectField();
      fingerRegistration();
    }
  }

  while (setupClass.isSelected())                      // WHILE THE SETUP CLASS OPTION IS SELECTED
  {
    display.mainMenuScreen();                          // update the display
    
    if (left.buttonIsPressed())                        // the left button moves the cursor up
    {
      registerFinger.selectField();
      setupClass.deselectField();    
    }
    if (middle.buttonIsPressed())                      // the middle button opens the class setup menu
    {
      setupClass.deselectField();
      classSetup();                                    
    }
  }
}


//--------------------------------------------------F I N G E R   R E G I S T R A T I O N--------------------------------------------------
void fingerRegistration()
{
  display.clearScreen();                                                                                    // clear the screen
  
  idNo1.resetField();                                                                                       // reset the ID number
  idNo2.resetField();
  idNo3.resetField();

  idNo1.selectField();                                                                                      // select the first ID number Field

  while (idNo1.isSelected())                                                                                // WHILE IDNO1 IS SELECTED
  {
    display.enterIDScreen();                         
    getAndPrintNumber(idNo1);                                                                               // get and print the number
  }
  while (idNo2.isSelected())                                                                                // WHILE IDNO2 IS SELECTED
  {
    display.enterIDScreen();
    getAndPrintNumber(idNo2);                                                                               // get and print the number
  }
  while (idNo3.isSelected())                                                                                // WHILE IDNO3 IS SELECTED
  {
    display.enterIDScreen();
    getAndPrintNumber(idNo3);                                                                               // get and print the number
    display.enterIDScreen();
    delay(1000);
  }

  id = ((idNo1.value * pow(10, 2)) + (idNo2.value * pow(10, 1)) + (idNo3.value * pow(10, 0)));              // convert the 3 digits to a single int

  if ((id == 0) || (id > 127)){                                                                             // if the ID is invalid
    display.clearScreen(); 
    display.invalidIDScreen();                                                                              // display the invalid ID message
    delay(2000);
    fingerRegistration();                                                                                   // and return to the user ID entry screen
  }
   
  display.clearScreen();
  display.userID(id);                                                                                       // otherwise, show the user ID
  
  display.scanFinger();                                                                                     // display the scan finger message
  
  while (!  getFingerprintEnroll() );                                                                       // start the fingerprint enrollment process

  display.fingerRegistered();                                                                               // when it comletes successfully, show the "registered" message
  delay(2000);

  mainMenu();                                                                                               // and return to the main menu
}
//----------------------------------------------------------C L A S S   S E T U P----------------------------------------------------------
void classSetup()
{
  display.clearScreen();                               // clear the screen

  day.resetField();                                    // reset all of the fields
  classNo1.resetField();
  classNo2.resetField();
  classNo3.resetField();
  classNo4.resetField();
  timeOpen.resetField();

  authorised = false;       

  
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
    display.classSetupScreen();                        // Print the class setup screen
    getAndPrintNumber(classNo1);                       // get and print the number
  }
  while (classNo2.isSelected())                        // WHILE CLASSNO2 IS SELECTED
  {
    display.classSetupScreen();                        // Print the class setup screen
    getAndPrintNumber(classNo2);                       // get and print the number
  }
  while (classNo3.isSelected())                        // WHILE CLASSNO3 IS SELECTED
  {
    display.classSetupScreen();                        // Print the class setup screen
    getAndPrintNumber(classNo3);                       // get and print the number
  }
  while (classNo4.isSelected())                        // WHILE CLASSNO4 IS SELECTED
  {
    display.classSetupScreen();                        // Print the class setup screen
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
    if (middle.buttonIsPressed())                      // the middle button advances to the authorise screen
    {
      timeOpen.deselectField();
      authorise();                                                 
    }
  }
}


//---------------------------------------------------A U T H O R I S E-------------------------------------------------------
void authorise()
{
  display.clearScreen();
  
  while(!authorised)                                           // wait until the register is authorised
  {
    display.authorisationScreen();                             // update display
        
    fingerID = getFingerprintID();                             // scan finger
    
    if ((fingerID > 0)&&(fingerID <= 5))                       // if a lecturer scans (ID 1-5)
    {
      display.authorisationSuccess();
  
      delay(2000);
 
      authorised = true;                                       // set the register to authorised
    }
    else if (fingerID > 5)                                     // if somebody else scans
    {
      display.authorisationFail();                             // do not authorise
       
      delay(2000);
    }
    
    delay(50);                                                 // don't need to run this at full speed.
  }
  scan();                                                      // once authorised, open the register
}


//-------------------------------------------------------S C A N-------------------------------------------------------------
void scan()
{
  startTime = millis();                                                         // set the current time as the time the register opened

  //int classNo = ((classNo1.value * pow(10, 3)) + (classNo2.value * pow(10, 2)) 
  //+ (classNo3.value * pow(10, 1)) + (classNo4.value * pow(10, 0)));

  registration.open();                                         
  
  while((millis() - startTime) < (timeOpen.value * 60000))    // until the registration time is complete   
  {
    display.scanToRegister();
  
    fingerID = getFingerprintID();                            // get the ID of the fingerprint being scanned
    
    if (fingerID > 0)                                         // if a finger has been scanned
    {
      display.userID(fingerID);                               // display the user ID number
      display.fingerRegistered();                             

      registration.user(fingerID);                            // log the user ID on the register
      
      delay(2000);
    }
    
    delay(50);                                                // don't need to run this at full speed.
  }

  resetFunc();                                                // reset the arduino to the start of the program
}


//-------------------------------------------------G E T   A N D   P R I N T   N U M B E R-------------------------------------------------
void getAndPrintNumber(Field &field)
{
    
  while((field.value = (int)(keypad.getKey()))==NO_KEY) {     // wait for a key to be pressed and set the classNo value to that number
    delay(1);                                            
  } 

  field.value = field.value - 48;                             // convert char value to int value ( 1 = 49 )

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

  if (idNo1.isSelected())
  {
    idNo1.deselectField();
    idNo2.selectField();
  }
  else if (idNo2.isSelected())
  {
    idNo2.deselectField();
    idNo3.selectField();
  }
  else if (idNo3.isSelected())
  {
    idNo3.deselectField();
  }
}


//--------------------------------------------G E T   F I N G E R P R I N T   I D----------------------------------------
int getFingerprintID() {
  uint8_t p = finger.getImage();
  
  if (p != FINGERPRINT_OK)  return -1;
  
  p = finger.image2Tz();

  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -2;

  
  // found a match!
  return finger.fingerID; 
}


//----------------------------------------G E T   F I N G E R P R I N T   E N R O L L------------------------------------
uint8_t getFingerprintEnroll() {

  int p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  // OK success!

  p = finger.image2Tz(1);
  
  display.removeFinger();
  
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  
  display.scanAgain();
  
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  // OK success!

  p = finger.image2Tz(2);

  // OK converted!
  
  p = finger.createModel();
  
  p = finger.storeModel(id);

  return true;
}
