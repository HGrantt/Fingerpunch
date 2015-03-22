#include "Decoration.h"

Decoration::Decoration( const std::string& image_path,
                        Vec2 const& size,
                        const float z_pos,
                        Vec2 const& pos )
  : Game_Object( new Render_Object( pos, 1.0f, z_pos ), nullptr ), 
    background( image_path, Vec2(), size )
{
    render_object->sprite_draw_order.push_back( &background );
}

void Decoration::update()
{}