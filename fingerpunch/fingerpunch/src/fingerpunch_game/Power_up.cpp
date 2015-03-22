#include "Power_up.h"


Power_Up::Power_Up( const std::string& image_path,
                        Vec2 const& size,
                        Vec2 const& pos )
  : Game_Object( new Render_Object( pos, 1.0f, 0.0f ), nullptr ), 
    image( image_path, Vec2(), size )
{
    render_object->sprite_draw_order.push_back( &image );
}

void Power_Up::update()
{}