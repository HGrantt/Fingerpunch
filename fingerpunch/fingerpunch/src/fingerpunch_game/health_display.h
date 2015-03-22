#ifndef _Health_Display_h_
#define _Health_Display_h_


#include "../game_world/Game_Object.h"

#include <string>

/**
 * shows the heads of the characters in
 * positions that indicate their current health
 */
class Health_Display : public Game_Object
{
public:

    /**
     * Constructor
     * @param name is the name of the character
     * @param go_right indicates the direction of low health
     */
    Health_Display( const std::string& name,
                    bool go_right );

    /**
     * decides the position of the health indicator
     * @param percent the percent of base health that is left 
     */
    void setPercent( float percent );
    
    /// updates nothing
    virtual void update();
    
private:
    
    /// the image that will be shown
    Sprite head;
    
    /// direction towards low health
    bool go_right;
};


#endif /* defined(_Health_Display_h_) */
