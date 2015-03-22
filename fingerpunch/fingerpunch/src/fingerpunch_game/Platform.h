#ifndef _Platform_h_
#define _Platform_h_

#include "../game_world/Game_Object.h"

class Platform : public Game_Object
{
public:

    /**
     * constructor
     * @param image_path is the image that will be shown
     * @param pos is the position of the platform
     * @param size is the size of the platform
     */
    Platform( std::string const& image_path, Vec2 const& pos, Vec2 const& size );

    /// does nothing
    virtual void update();

private:

    /// the image that will be shown
    Sprite image;

};

#endif /* defined(_Platform_h_) */
