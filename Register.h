
#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <Arduino.h>

class Register{

public:

  void setup(int _baudRate);
  void open();
  void user(int _userId);
  void close();
};

#endif // _REGISTER_H_
