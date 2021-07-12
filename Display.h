
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>

class Display
{
public:

  void displaySetup();
  void clearScreen();
  void mainMenuScreen();
  void enterIDScreen();
  void invalidIDScreen();
  void userID(int idNo);
  void scanFinger();
  void removeFinger();
  void scanAgain();
  void fingerRegistered();
  void classSetupScreen();
};

#endif // _DISPLAY_H_
