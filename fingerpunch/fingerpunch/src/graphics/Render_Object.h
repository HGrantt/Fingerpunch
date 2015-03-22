#ifndef _Render_Object_h
#define _Render_Object_h
 
#include "../math/Vec2.h"
#include "Sprite.h"

#include <vector>

/**
 * Class for holding information about render objects
 */
class Render_Object
{
public:

  /**
   * Constructor
   * @param pos position of the object
   * @param size size of the object
   * @param z_pos position for paralax purposes
   * @param enabled if the object should be showed
   */
    Render_Object( Vec2 const& pos,
                   const float size  = 1.0f,
                   const float z_pos = 0.0f,
                   bool  enabled     = true );
  
    /// position on the screen
    Vec2  pos;

    /// size of the object
    float size;

    /// z_pos position for paralax purposes
    float z_pos;
  
    ///enabled if the object should be showed
    bool  enabled;

  /**
   * Used for sorting draw order regarding the paralax effect
   * @param rhs is the object that will be compared
   * @return returns true if rhs should be infornt
   */
    bool operator<( Render_Object const& rhs ) const;

    /// vector containing sprites with draw order
    std::vector<Sprite*> sprite_draw_order;
    
};

#endif /* defined(_Render_Object_h_) */
