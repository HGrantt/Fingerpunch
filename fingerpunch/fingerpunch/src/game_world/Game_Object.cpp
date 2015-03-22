#include "Game_Object.h"
 
Game_Object::Game_Object( Render_Object*  render_obj,
                          Physics_Object* physics_obj )
  : render_object ( render_obj ),
    physics_object( physics_obj )
{}

Game_Object::~Game_Object()
{}
