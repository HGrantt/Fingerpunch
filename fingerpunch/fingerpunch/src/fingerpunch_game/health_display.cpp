#include "health_display.h"

#include "../math/float_math.h"

Health_Display::Health_Display( const std::string& name,
                                bool _go_right )
  : Game_Object( new Render_Object( Vec2(), 1.0f, 0.0f ), nullptr ),
    head( "./images/" + name + "_head.png", Vec2(), Vec2( 0.15f ) ),
    go_right( _go_right )
{
    render_object->sprite_draw_order.push_back( &head );
    render_object->pos.y = 0.9f;
}

void Health_Display::setPercent( float percent )
{
    percent = fclamp( percent );
    
    const float dir_mult = ( go_right ? 1.0f : -1.0f );
    
    render_object->pos.x = dir_mult * ( 0.1f + ( 1.0f - percent ) * 0.8f ); 
}

void Health_Display::update()
{}
