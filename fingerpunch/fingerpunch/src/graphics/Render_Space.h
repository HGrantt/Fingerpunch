#ifndef _Render_Space_h_
#define _Render_Space_h_

#include "Render_Object.h"
#include "../math/Vec2.h"
#include "../file/Loader.h"
#include <vector>

/**
 * Class for handeling the images drawn
 */
class Render_Space
{
public:

    /// focus point for the paralax effect
    Vec2  parallax_focus_point{ 0.0f, 0.0f };

    /// the strenght of the paralax effect
    float parallax_mult{ 0.01f };

  /**
   * Fetches the draw order of the objects for overlapping purposes
   * @return the render objects
   */
    std::vector<Render_Object*> const& getDrawOrder() const;

    /// updates the draw order
    virtual void updateDrawOrder();

    /// adds render_object to the vector storage
    void add( Render_Object* render_object );
  
    /// removes the render object
    void remove( Render_Object* render_object );

protected:

    /// vector containing render objects
    std::vector<Render_Object*> render_objects;
    Loader textures;

};

#endif /* defined(_Render_Target_h_) */
