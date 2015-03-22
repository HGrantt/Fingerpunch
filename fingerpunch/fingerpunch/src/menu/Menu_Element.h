#ifndef _Menu_Item_h_
#define _Menu_Item_h_
 
#include "../math/Vec2.h"
#include "../graphics/Render_Object.h"
#include "../graphics/Sprite.h"

/**
 * Class for elements in a menu
 * inherits from Render_Object
 */
class Menu_Element : public Render_Object
{
public:

  /**
   * Constructor for Menu_Element
   * @param sprite the images path name, size and position
   */
    Menu_Element( Sprite const& sprite );

  /**
   * Function for getting an image and gain access to its attributes
   * @return reference for the images attributes
   */
    Sprite* getImage();

  /**
   * Checks if a point is inside a Menu_Element
   * @param point a position on the screen, in this case mouse pointer
   * @return true if the point is inside the Menu_Element
   */
    bool contains( Vec2 const& point );

private:

    /// Contains attributes of a Menu_Element
    Sprite image;

};

#endif /* defined(_Menu_Item_h_) */
