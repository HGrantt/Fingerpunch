#include "Render_Object.h"
 
Render_Object::Render_Object( Vec2 const& pos,
                              const float size,
                              const float z_pos,
                              bool  enabled )
  : pos( pos ),
    size( size ),
    z_pos( z_pos ),
    enabled( enabled )
{}

bool Render_Object::operator<( Render_Object const& rhs ) const
{
    return ( z_pos < rhs.z_pos );
}
