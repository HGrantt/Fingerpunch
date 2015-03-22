#include "Physics_Object.h"


Physics_Object::Physics_Object( Vec2 const& _pos,
                                Vec2 const& _size,
                                const bool  _enabled )
  : velocity     ( 0.0f, 0.0f ),
    acceleration ( 0.0f, 0.0f ),
    enabled      ( _enabled ),
    collision_box( _pos, _size ),
    state( COLLISION_STATE::NONE ),
    pos ( collision_box.pos ),
    size( collision_box.size )
{}
