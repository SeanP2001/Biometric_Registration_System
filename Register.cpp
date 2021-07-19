
#include "Field.h"
#include "Register.h"


// ********************** Access Field Objects **********************
extern Field idNo1;
extern Field idNo2;
extern Field idNo3;

extern Field day;                            
extern Field classNo1;
extern Field classNo2;
extern Field classNo3;
extern Field classNo4;

//--------------------------------------------S E T U P   R E G I S T E R--------------------------------------------
  void Register::setup(int _baudRate)
  {
    Serial.begin(_baudRate);
  }


//---------------------------------------------O P E N   R E G I S T E R---------------------------------------------
  void Register::open()
  {
    Serial.print("~~~~~~~~~~~~~~~~~~~~~~~ ");
    
    switch(day.value) {                              // display the day
      case 1 : Serial.print("Monday"); break;
      case 2 : Serial.print("Tuesday"); break;
      case 3 : Serial.print("Wednesday"); break;
      case 4 : Serial.print("Thursday"); break;
      case 5 : Serial.print("Friday"); break;
    }

     Serial.print(" ICE-");

     Serial.print(classNo1.value);
     Serial.print(classNo2.value);
     Serial.print(classNo3.value);
     Serial.print(classNo4.value);

     Serial.print(" Register");
     Serial.println(" ~~~~~~~~~~~~~~~~~~~~~~~");
  }


//------------------------------------------R E G I S T E R   S T U D E N T------------------------------------------
  void Register::user(int _userId)
  {
    Serial.print("User #");

    if (_userId < 100)                // print preceeding zeros
      Serial.print("0");
    if (_userId < 10)
      Serial.print("0");

    
    Serial.println(_userId);
  }


//--------------------------------------------C L O S E   R E G I S T E R--------------------------------------------
  void Register::close()
  {
    
  }
