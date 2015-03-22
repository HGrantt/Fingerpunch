#ifndef _Physics_Object_h_
#define _Physics_Object_h_
 
#include "Physics_Space.h"

#include "../math/Vec2.h"
#include "../math/AABB.h"


/**
 * Is used to define an object in a physics_space
 */
class Physics_Object
{
public:

    /// current collision state
    enum COLLISION_STATE
    {
        NONE,
        COLLIDING,
        NUM_STATES
    };

    /// velocity of the object
    Vec2  velocity;
    /// acceleration of the object
    Vec2  acceleration;
    
    /// controls if the object should be updated or not
    bool  enabled;
    
    /**
     * Constructor
     * @param pos is the start position of the object
     * @param size is the size of the collision box
     * @param enabled controls if the object should be updated.
     */
    Physics_Object( Vec2 const& pos,
                    Vec2 const& size,
                    const bool  enabled  = true );

    /// collision box
    AABB collision_box;
    
    /// current collision state
    COLLISION_STATE state;
    
    /// quick reference to collision_box.pos
    Vec2& pos;
    /// quick reference to collision_box.size
    Vec2& size;
};

#endif /* defined(_Physics_Object_h_) */
