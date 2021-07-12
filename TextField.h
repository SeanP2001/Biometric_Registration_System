
#ifndef _TEXT_FIELD_H_
#define _TEXT_FIELD_H_

#include <Arduino.h>

class TextField{
public:

  bool cursors;
  String text;
  int row;
  int column;
  
  TextField(String _text, int _column, int _row);
  
  void printField();
  void selectField();
  void deselectField();

  bool isSelected();

private:

  void printCursors();
  void removeCursors();
};

#endif // _TEXT_FIELD_H_
