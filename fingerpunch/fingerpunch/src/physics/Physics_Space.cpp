#include "Physics_Space.h"

#include "../math/float_math.h"
#include "../math/Vec2.h"
#include "../math/AABB.h"

#include <SDL2/SDL.h>
#include <iomanip>

#include <iostream>

void Physics_Space::add( Physics_Object* phys_obj, COLLIDER_TYPE cldr_type )
{
    if ( cldr_type < COLLIDER_TYPE::NUM_TYPES and phys_obj != nullptr )
    {
        p_containers[cldr_type]->push_back( phys_obj );
    }
}

void Physics_Space::remove( Physics_Object* phys_obj )
{
    for ( std::vector<Physics_Object*>* pv : p_containers )
    {
        for ( std::vector<Physics_Object*>::iterator it = pv->begin();
              it != pv->end(); ++it )
        {
            if ( *it == phys_obj )
            {
                pv->erase( it );
                return;
            }
        }
    }
}

void Physics_Space::update( float time_delta )
{
    // reset powerups:
    // actor is moved, try to touch power-mods:
    for ( Physics_Object* p_mod : power_mods )
    {
        p_mod->state = Physics_Object::COLLISION_STATE::NONE;
    }

    for ( Phys_Container::iterator actor_it = actors.begin();
          actor_it != actors.end();
          ++actor_it )
    {
        Physics_Object* actor = *actor_it;
        
        // if the object shouldn't be moved, we need to continue:
        if ( not actor->enabled )
        {
            std::cerr << "disabred actor" << std::endl;
            continue;
        }
        
        // reset state, update velocity and generate a new position:
        actor->state       = Physics_Object::COLLISION_STATE::NONE;
        actor->velocity   += ( gravity + actor->acceleration ) * time_delta;
        Vec2 new_position  = actor->pos + actor->velocity * time_delta;
        
        // friction:
        actor->velocity.x *= 0.98f * ( 1.0f - time_delta );
        
        if ( std::fabs( actor->velocity.x ) < 0.1f )
        {
            actor->velocity.x = 0.0f;
        } 
        
        // limit position:
        if ( std::fabs( new_position.x ) >= 1.0f )
        {
            new_position.x = fclamp( new_position.x, -1.0f, 1.0f );
            actor->velocity.x = 0.0f;
        }
        
        
        const float min_pos_y = -1.0f;
        if ( new_position.y < min_pos_y )
        {
            new_position.y    = min_pos_y;
            actor->velocity.y = 0.0f;
            actor->state      = Physics_Object::COLLISION_STATE::COLLIDING;
        }
        
        // colliding with platforms?
        if ( actor->state != Physics_Object::COLLISION_STATE::COLLIDING  )
        {
            for ( Physics_Object* platform : platforms )
            {
                const float pos_diff_x = std::fabs(   platform->pos.x  - actor->pos.x        );
                const float size_sum_x = std::fabs( ( platform->size.x + actor->size.x ) / 2 );
                
                const bool inside_x    = pos_diff_x <= size_sum_x;
                
                const float actor_bottom     = actor->pos.y    - actor->size.y    / 2;
                const float actor_bottom_new = new_position.y  - actor->size.y    / 2;
                const float platform_top     = platform->pos.y + platform->size.y / 2;
                
                
                
                if ( inside_x and actor_bottom     >= platform_top
                              and actor_bottom_new <= platform_top )
                {
                    actor->velocity.y = 0.0f;
                    new_position.y = platform_top + actor->size.y / 2;
                    
                    actor->state = Physics_Object::COLLISION_STATE::COLLIDING;
                    break;
                }
            }
        }
        
        actor->pos = new_position;
        
        // actor is moved, try to touch power-mods:
        for ( Physics_Object* p_mod : power_mods )
        {
            if ( AABB::intersects( actor->collision_box, p_mod->collision_box ) )
            {
                p_mod->state = Physics_Object::COLLISION_STATE::COLLIDING;
            }
        }
    }
}

Physics_Space::Physics_Space( const Vec2 _gravity )
  : gravity( _gravity ),
    p_containers
    {
        &actors,
        &platforms,
        &power_mods
    }
{}

Physics_Space::~Physics_Space()
{}
