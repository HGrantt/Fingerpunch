#ifndef _Physics_Space_h_
#define _Physics_Space_h_
 
#include "Physics_Object.h"
#include "../math/Vec2.h"

#include <vector>
#include <array>

class Physics_Object;

/**
 * Controls the behaviour of physics_objects
 */
class Physics_Space
{
public:

    /**
     * collider types are used to separate
     * collision types to different containers
     */
    enum COLLIDER_TYPE
    {
        ACTOR,
        PLATFORM,
        POWER_MOD,
        NUM_TYPES,
        NONE
    };

    /// gravity direction and strength
    Vec2 gravity;
    
    /**
     * Constructor
     * @param gravity direction and strength
     */
    Physics_Space( const Vec2 gravity = Vec2( 0.0f, -9.82f ) );
    ~Physics_Space();

    /**
     * updates all positions of objects
     * @param time_delta is used to control new positions
     */
    void update( float time_delta );
    
    /**
     * adds an object
     * @param phys_obj is the object that will be added.
     * @param cldr_type decides how the object is treated on update.
     */
    void add( Physics_Object* phys_obj, COLLIDER_TYPE cldr_type );
    
    /**
     * removes the requested object.
     * @param phys_obj is the object that will be removed.
     */
    void remove( Physics_Object* phys_obj );

private:

    /// the container type used for each type of collider:
    using Phys_Container = std::vector<Physics_Object*>;
    
    /// actors ( objects affected by gravity )
    Phys_Container actors;
    
    /// platforms that actors can stand on
    Phys_Container platforms;
    
    /// any object that can be touched
    Phys_Container power_mods;
    
    const std::array<Phys_Container*, COLLIDER_TYPE::NUM_TYPES> p_containers;
    
};

#endif /* defined(_Physics_Space_h_) */
