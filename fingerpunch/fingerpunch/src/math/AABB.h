#ifndef _AABB_H_
#define _AABB_H_
 
#include "Vec2.h"

/**
 * Axis aligned bounding box
 */
class AABB
{
public:

    /// position of the bounding box
    Vec2 pos;
    /// size of
    Vec2 size;

    /**
     * Constructor:
     * @param pos_x is x position
     * @param pos_y is y position
     * @param width
     * @param height
     */
    AABB( const float pos_x, const float pos_y,
          const float width, const float height );

    /**
     * Contructor:
     * @param pos is the position
     * @param size contains width and height
     */
    AABB( Vec2 const& pos, Vec2 const& size );
    
    /**
     * Checks if a point is inside the AABB
     * @param x
     * @param y
     */
    bool contains( float x, float y  ) const;
    
    /**
     * Checks if a point is inside the AABB
     * @param point contains x position and y position
     */
    bool contains( Vec2 const& point ) const;
    
    /**
     * check intersection between two AABBs
     * @param a is the first box
     * @param b is the second box
     * @return true if an intersection exists between a and b
     */
    static bool intersects( AABB const& a, AABB const& b );
    
    /**
     * get the smallest box that can contain both boxes 
     * @param a is the first box
     * @param b is the second box
     * @return the smallest box that both boxes fit within.
     */
    static AABB min_bounding_box( AABB const& a, AABB const& b );
    
    /**
     * tells if the object b is close enough to
     * possibly collide when a moves to its destination
     * @param a is the moving box
     * @param b is the box we want to check collision with
     * @param a_destination is the position that a will move to
     * @return false if the object b is nowhere near a collision with a
     */
    static bool may_collide( AABB const& a, AABB const& b,
                             Vec2 const& a_destination );

};

#endif /* defined(_AABB_h_) */
