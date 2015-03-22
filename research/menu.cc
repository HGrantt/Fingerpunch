#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>

#include "menu.h"



MENU::MENU(int _top, int _left, int _bot, int _right):
    top(float(_top)), left(float(_left)),
    bot(float(_bot)), right(float(_right))
    //creates a box in a coordinate system
{}

float MENU::get_top() const
{
    return top;
}

float MENU::get_left() const
{
    return left;
}

float MENU::get_bot() const
{
    return bot;
}

float MENU::get_right() const
{
    return right;
}

void MENU::set_values(int _top, int _left, int _bot, int _right)
{
  this->top = _top;
  this->left = _left;
  this->bot = _bot;
  this->right = _right;
}

SDL_Rect MENU::get_rect()
{
  SDL_Rect pos_rect;
  pos_rect.x = left;
  pos_rect.y = top;
  pos_rect.w = right;
  pos_rect.h = bot;
  
  return pos_rect;
}

bool MENU::contain ( int x, int y)
//checks if x,y coordinates are in box
{
    return left <=  x  && x <= left + right && top <= y && y <= top + bot;
}
