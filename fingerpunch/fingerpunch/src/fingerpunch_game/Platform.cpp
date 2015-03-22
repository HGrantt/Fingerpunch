#include "Platform.h"

Platform::Platform( std::string const& image_path, Vec2 const& pos, Vec2 const& size )
  : Game_Object( new Render_Object( pos, 1.0f ), new Physics_Object( pos, size ) ),
    image( image_path, Vec2(), size )
{
    render_object->sprite_draw_order.push_back( &image );
}

void Platform::update()
{}
