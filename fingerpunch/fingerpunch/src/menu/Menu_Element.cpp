#include "Menu_Element.h"

#include "../math/AABB.h"

#include <iostream>
 
Menu_Element::Menu_Element( Sprite const& sprite )
  : Render_Object( Vec2( 0.0f, 0.0f ), 1.0f ),
    image( sprite )
{
    sprite_draw_order.push_back( &image );
    sprite_draw_order.shrink_to_fit();
}

Sprite* Menu_Element::getImage()
{
    return &image;
}

bool Menu_Element::contains( Vec2 const& point )
{
    const AABB area{ image.pos, image.size };
    
    return area.contains( point );
}
