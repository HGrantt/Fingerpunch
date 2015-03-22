#ifndef _Player_h_
#define _Player_h_

#include "../game_world/Game_Object.h"

#include <string>

class Player : public Game_Object
{
public:

    /**
     * constructor:
     * @param name is the name of the character
     * @param pos is the position of the character
     * @param size is the size of the character
     * @param look_right is the direction the player is facing
     */
    Player( std::string const& name,
            Vec2 const& pos,
            Vec2 const& size,
            bool look_right = true );

    /// updates the animations for all sprites
    virtual void update();

    /// the name of the character
    std::string name;
    
    /// the current health of the character
    int         health;
    
    /// the direction the player is facing
    bool        look_right;

    /// start pos for fist
    float fist_back_start_x;
    
    /// start pos for fist
    float fist_front_start_x;
    
    /// start pos for boot
    float boot_start_y;
    
    /// start pos for head
    float head_start_y;
    
    /// the tick when fist animation started
    int fist_tick_start_back;
    
    /// the tick when fist animation started
    int fist_tick_start_front;
    
    
    /// state for a fist
    enum class FIST_STATE
    {
        /// fist is idling
        IDLE,
        /// the fist is in aggressive mode and can do damage
        DANGEROUS,
        /// the fist is moving back to its original position
        RECOVER
    };
    
    /// fist back state
    FIST_STATE fist_back_state;
    
    /// fist front state
    FIST_STATE fist_front_state;
    
    /// head image
    Sprite head;
    
    /// body image
    Sprite body;
    
    /// pointer to the current fist back image
    Sprite* fist_back;
    /// pointer to the current fist front image
    Sprite* fist_front;
    
    /// fist image
    Sprite fist_right_standard;
    
    /// fist image
    Sprite fist_left_standard;
    
    /// fist image
    Sprite fist_right_mirror;
    
    /// fist image
    Sprite fist_left_mirror;
    
    /// boot image
    Sprite boot_right;
    
    /// boot image
    Sprite boot_left;

};

#endif /* defined(_Player_h_) */
