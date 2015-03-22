#ifndef _Input_Manager_h_
#define _Input_Manager_h_

#include <SDL2/SDL.h>

#include "User_Target.h"

#include "../graphics/Renderer.h"
#include "../math/Vec2.h"

#include <array>

/**
 * Class for key input
 */
class Key
{
public:

    SDL_Scancode key;

   /**
    * Constructor for Key
    * @param k represents a Scancode and is set to UNKNOWN
    * instead of nullpointer
    */
    Key( SDL_Scancode k = SDL_SCANCODE_UNKNOWN )
      : key( k ),
        pressed_before( false ),
        pressed_now( false )
    {}
  
   /**
    * Updates current button state
    * @param is_pressed is the current button state
    */
    void update( bool is_pressed );

    /// returns true if key is currently pressed
    bool isPressed() const;

    /// returns true when key is tapped
    bool isTapped() const;

    /// returns true when key is released
    bool isReleased() const;
    
private:

    /// if true, the key can be tapped, otherwise released
    bool pressed_before;

    /// true if pressed
    bool pressed_now;

};

/**
 * Class that remembers keystates
 */
class Input_Manager
{
public:

  /**
   * Constructor for Input_Manager
   * @param renderer is used to get information,
   * about screen resolution
   */
    Input_Manager( Renderer* renderer );

    /// Destructor
    ~Input_Manager();

    /// Updates all keystates and mouse position
    void update();

    /// keeps track of mouse clicks
    Key mouse_button;

    /// Escape button
    Key escape{ SDL_SCANCODE_ESCAPE };

    /// SDL_Quitevent
    bool quit{ false };

    /// Keeps track of the mouse position it gets from update()
    Vec2 mouse_position;

    ///P1 controls
    Key p1_jump     { SDL_SCANCODE_W };
    Key p1_left     { SDL_SCANCODE_A };
    Key p1_right    { SDL_SCANCODE_D };
    Key p1_hit_back { SDL_SCANCODE_V };
    Key p1_hit_front{ SDL_SCANCODE_B };

    ///P2 controls
    Key p2_jump     { SDL_SCANCODE_UP    };
    Key p2_left     { SDL_SCANCODE_LEFT  };
    Key p2_right    { SDL_SCANCODE_RIGHT };
    Key p2_hit_back { SDL_SCANCODE_KP_1  };
    Key p2_hit_front{ SDL_SCANCODE_KP_2  };

private:
    /// handles all of the keys
    std::array<Key*, 11> keys;

    /// checks if quit is called
    void updateExitStatus();

    /// in this case handles screen resolution
    Renderer* renderer;
};

#endif /* defined(_Input_Manager_h_) */
