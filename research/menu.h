#ifndef _MENU_H
#define _MENU_H
#include <SDL2/SDL.h>

class MENU
{

public:
  MENU(int top, int left, int bot, int right);
  
  float get_top() const;
  float get_left() const;
  float get_bot() const;
  float get_right() const;
  SDL_Rect get_rect();

  void set_values( int _top, int _left, int _bot, int _right );
  bool contain ( int x, int y );
  
private:
  float top{0};
  float left{0};
  float bot{0};
  float right{0};
};

#endif
