#ifndef _Decoration_h_
#define _Decoration_h_

#include "../game_world/Game_Object.h"

#include <string>

class Decoration : public Game_Object
{
public:

    /**
     * Constructor
     * @param image_path is the image that will be shown
     * @param size is the size of the image
     * @param z_pos is used for draw order sort and parallax effects
     * @param pos is the position of the decoration
     */
    Decoration( const std::string& image_path,
                Vec2 const& size,
                const float z_pos,
                Vec2 const& pos = Vec2( 0.0f ) );
    
    /// does nothing
    virtual void update();
    
private:

    /// the image that will be shown
    Sprite background;
};

#endif /* defined(_Decoration_h_) */
