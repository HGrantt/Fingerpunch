#include <SDL2/SDL.h>
#include "Input_Manager.h"

#include <iostream>

void Key::update( bool is_pressed )
{
    pressed_before = pressed_now;
    pressed_now = is_pressed;
}

bool Key::isPressed() const
{
    return pressed_now;
}

bool Key::isTapped() const
{
    return pressed_now and not pressed_before;
}

bool Key::isReleased() const
{
    return pressed_before and not pressed_now;
}

void Input_Manager::update()
{
    // mouse:
    int mouse_x;
    int mouse_y;
    SDL_PumpEvents();
    
    quit = static_cast<bool>( SDL_QuitRequested() );

    mouse_button.update( static_cast<bool>( SDL_GetMouseState( &mouse_x, &mouse_y ) ) );

    const Vec2 mouse_screen_pos
    {
        static_cast<float>( mouse_x ) / renderer->window_width,
        static_cast<float>( renderer->window_height - mouse_y ) / renderer->window_height
    };
    
    mouse_position = 2.0f * ( mouse_screen_pos - Vec2{ 0.5f, 0.5f } );
  
    // update keys
    const Uint8* keystates = SDL_GetKeyboardState( nullptr );

    for ( Key* key : keys )
    {
        key->update( static_cast<bool>( keystates[ key->key ] ) );
    }
}


Input_Manager::Input_Manager( Renderer* _renderer ) : 
    keys
    {
        &p1_jump,
        &p1_left,       &p1_right,
        &p1_hit_back,   &p1_hit_front,
          
        &p2_jump,
        &p2_left,       &p2_right,
        &p2_hit_back,   &p2_hit_front,
        &escape
    },
    renderer( _renderer )
{}

Input_Manager::~Input_Manager()
{}
