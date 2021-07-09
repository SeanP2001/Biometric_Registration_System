//------------------------------------------------------------------------------------------------------------------------------------------------------------
// Biometric Registration System
// Sean Price
// V0.1
// Setup Field Class variables, construcor and number print
//------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "Field.h"

 Field number(Field::NUMBER, 5, 2, 0);

void setup() {
  number.displaySetup();
}

void loop() {
  number.printField();
  //number.column++;
  delay(2000);
}
