#include "AABB.h"
 
#include <algorithm>
#include <array>
#include <cmath>

AABB::AABB( const float pos_x, const float pos_y,
            const float width, const float height )
{
    this->pos  = Vec2( pos_x, pos_y  );
    this->size = Vec2( width, height );
}

AABB::AABB( Vec2 const& pos, Vec2 const& size )
{
    this->pos  = pos;
    this->size = size;
}


bool AABB::contains( float x, float y ) const
{
    const bool inside_x{ std::fabs( pos.x - x ) < ( size.x / 2 ) };
    const bool inside_y{ std::fabs( pos.y - y ) < ( size.y / 2 ) };
    
    return ( inside_x and inside_y );
}

bool AABB::contains( Vec2 const& point ) const
{
    return contains( point.x, point.y );
}

bool AABB::intersects( AABB const& a, AABB const& b )
{
    const bool overlap_x{ std::fabs( a.pos.x - b.pos.x ) < ( ( a.size.x + b.size.x ) / 2 ) };
    const bool overlap_y{ std::fabs( a.pos.y - b.pos.y ) < ( ( a.size.y + b.size.y ) / 2 ) };
                          
    return ( overlap_x and overlap_y );
                  
}
    
AABB AABB::min_bounding_box( AABB const& a, AABB const& b )
{
    const Vec2 a_half_size( a.size / 2 );
    const Vec2 b_half_size( b.size / 2 );
    
    const std::array<float, 4> corners_x
    {
        a.pos.x - a_half_size.x,
        a.pos.x + a_half_size.x,
        
        b.pos.x - b_half_size.x,
        b.pos.x + b_half_size.x
    };
    
    const std::array<float, 4> corners_y
    {
        a.pos.y - a_half_size.y,
        a.pos.y + a_half_size.y,
        
        b.pos.y - b_half_size.y,
        b.pos.y + b_half_size.y
    };
    
    const Vec2 top_left
    {
        *std::min_element( corners_x.begin(), corners_x.end() ),
        *std::min_element( corners_y.begin(), corners_y.end() )
    };
    
    const Vec2 bottom_right
    {
        *std::max_element( corners_x.begin(), corners_x.end() ),
        *std::max_element( corners_y.begin(), corners_y.end() )
    };

    return AABB{ top_left, bottom_right - top_left };

}

bool AABB::may_collide( AABB const& a, AABB const& b, Vec2 const& a_destination )
{
    const  AABB a_final{ a_destination, a.size };
    return intersects( min_bounding_box( a, a_final ), b );
}
