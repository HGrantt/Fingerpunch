#include <iostream>

#include "menu.h"

using namespace std;


int main()
{
  pt_cord ins_cord{0, 0};
  cout << "x: " << ins_cord.x << ", y: " << ins_cord.y << endl;
  float top{0}, left{0}, bottom{10}, right{10};
  MENU box(0.0, 0.0, -20.0, 20.0);
  box.set_values(top, left, bottom, right);
  cout << top << left << bottom << right << endl; //Prints the box coordinates
  if( box.contain(0, 0) )
  {
    cout << "sant" << endl;
  }
  cout << box.contain( ins_cord ) << endl;
  return 0;
}

