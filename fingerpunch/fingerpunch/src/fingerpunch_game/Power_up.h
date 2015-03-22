#ifndef _Settings_Menu_h_
#define _Settings_Menu_h_

#include "../game_world/Game_Object.h"

class Power_Up : public Game_Object
{
public:

    /**
     * constructor
     * @param image_path is the image that will be displayed
     * @param size is the size of the image
     * @param pos is the position of the image
     */
    Power_Up( const std::string& image_path,
              Vec2 const& size,
              Vec2 const& pos );
    
    /// updates nothing
    virtual void update();
    
    /// the image that is displayed
    Sprite image;
};

#endif /* defined(_Settings_Menu_h_) */
