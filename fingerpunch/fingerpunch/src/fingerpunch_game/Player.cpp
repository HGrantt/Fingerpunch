#include "Player.h"

#include <iostream>
#include <SDL2/SDL.h> // ticks
#include "../math/float_math.h"

Player::Player( std::string const& name, Vec2 const& pos, Vec2 const& size, bool look_right )
  : Game_Object( new Render_Object( pos ), new Physics_Object( pos, size ) ),
    name( name ),
    health( 100 ),
    look_right( look_right ),
    fist_back_start_x ( 0.11f ),
    fist_front_start_x( 0.13f ),
    boot_start_y( -0.225f ),
    head_start_y( 0.275f ),
    fist_tick_start_back ( SDL_GetTicks() ),
    fist_tick_start_front( SDL_GetTicks() ),
    fist_back_state ( FIST_STATE::IDLE ),
    fist_front_state( FIST_STATE::IDLE ),
    
    head                ( "./images/" + name + "_head.png",
                          Vec2( 0.0f, 0.275f ), Vec2( 0.25f, 0.4f ) ),
    body                ( "./images/" + name + "_body.png",
                          Vec2( 0.0f, 0.0f ), Vec2( 0.2f, 0.35f ) ),
    
    fist_right_standard ( "./images/" + name + "_fist_right.png",
                          Vec2( .13f, 0.1f ), Vec2( 0.1f ) ),
    fist_left_standard  ( "./images/" + name + "_fist_left.png",
                          Vec2( .11f, 0.05f ), Vec2( 0.1f ) ),
    
    fist_right_mirror   ( "./images/" + name + "_fist_right_m.png",
                          Vec2( -.11f, 0.05f ), Vec2( 0.1f )  ),
    fist_left_mirror    ( "./images/" + name + "_fist_left_m.png",
                          Vec2( -.13f, 0.1f ), Vec2( 0.1f )  ),
    
    boot_right          ( "./images/" + name + "_boot_right.png",
                          Vec2( .0575f, -0.225f ), Vec2( .15f, .225f )  ),
    boot_left           ( "./images/" + name + "_boot_left.png",
                          Vec2( -.0575f, -0.225f ), Vec2( .15f, .225f ) )
{
    update();

    render_object->size = 0.4f;
    physics_object->size *= render_object->size;

}

void Player::update()
{
    const float time = static_cast<float>( SDL_GetTicks() );
    
    // head animation
    head.pos.y = head_start_y + sinf( time * 0.005f ) * 0.0125f;
    
    // leg animations:
    if ( physics_object->state == Physics_Object::COLLISION_STATE::COLLIDING )
    {
        if ( std::fabs( physics_object->velocity.x ) >= 0.1f )
        {
            boot_left.pos.y  = boot_start_y + sinf( time * 0.025f ) * 0.025f;
            boot_right.pos.y = boot_start_y - sinf( time * 0.025f ) * 0.025f;
        }
        else
        {
            boot_left.pos.y  = boot_start_y;
            boot_right.pos.y = boot_start_y;
        }
    }
    else
    {
        if ( physics_object->velocity.x > 0.0f )
        {
            boot_left.pos.y  = boot_start_y + 0.02f;
            boot_right.pos.y = boot_start_y + 0.05f;
        }
        else
        {
            boot_left.pos.y  = boot_start_y + 0.05f;
            boot_right.pos.y = boot_start_y + 0.02f;
        }
    }

    render_object->pos = physics_object->pos;

    // swap hand images based on direction:
    if ( look_right )
    {
        fist_back  = &fist_right_standard;
        fist_front = &fist_left_standard; 
    }
    else
    {
        fist_back  = &fist_right_mirror;
        fist_front = &fist_left_mirror; 
    }
    
    // fist fighting:
    const float time_start = 0.1f;
    const float time_start_squared = time_start * time_start;
    const float fist_amp   = 0.225f;    
    // fist back
    if ( fist_back_state != FIST_STATE::IDLE )
    {
        const float time_from_start
            = static_cast<float>( ( SDL_GetTicks() - fist_tick_start_back ) ) / 1000; // seconds since start

        float fist_pos_back = fist_back_start_x
            + ( (-powf( time_from_start - time_start, 2 )
                + time_start_squared ) * fist_amp / time_start_squared );
        
        if ( fist_back_start_x > fist_pos_back )
        {
            fist_back_state = FIST_STATE::IDLE;
        }
        else
        {
            if ( fist_back_start_x * 1.1f < fist_pos_back )
            {
                fist_back_state = FIST_STATE::RECOVER;
            }
            fist_back->pos.x = ( look_right ? 1.0f : -1.0f ) * fist_pos_back;
        }
    }
    else
    {
        fist_back->pos.x = ( look_right ? 1.0f : -1.0f ) * fist_back_start_x;
    }
    
    // fist front
    if ( fist_front_state != FIST_STATE::IDLE )
    {
        const float time_from_start
            = static_cast<float>( ( SDL_GetTicks() - fist_tick_start_front ) ) / 1000; // seconds since start

        float fist_pos_front = fist_front_start_x
            + ( (-powf( time_from_start - time_start, 2 )
                + time_start_squared ) * fist_amp / time_start_squared );
        
        if ( fist_front_start_x > fist_pos_front )
        {
            fist_front_state = FIST_STATE::IDLE;
        }
        else
        {
            if ( fist_front_start_x * 1.1f < fist_pos_front )
            {
                fist_front_state = FIST_STATE::RECOVER;
            }
            fist_front->pos.x = ( look_right ? 1.0f : -1.0f ) * fist_pos_front;
        }
    }
    else
    {
        fist_front->pos.x = ( look_right ? 1.0f : -1.0f ) * fist_front_start_x;
    }
    
    
    
    
    // update draw_order:
    render_object->sprite_draw_order.clear();
    
    render_object->sprite_draw_order.push_back( &boot_left );
    render_object->sprite_draw_order.push_back( &boot_right );
    
    render_object->sprite_draw_order.push_back( fist_back );
    
    render_object->sprite_draw_order.push_back( &body );
    render_object->sprite_draw_order.push_back( &head );
    
    render_object->sprite_draw_order.push_back( fist_front );
}
