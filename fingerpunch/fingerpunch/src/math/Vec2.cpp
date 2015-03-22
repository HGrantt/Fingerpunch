#include "Vec2.h"
 
#include "float_math.h"

/******************************** Constructors ********************************/

Vec2::Vec2()
  : x( 0.0f ),
    y( 0.0f )
{}

Vec2::Vec2( const float scalar )
  : x( scalar ),
    y( scalar )
{}

Vec2::Vec2( float component_x, float component_y )
  : x( component_x ),
    y( component_y )
{}

Vec2::Vec2( Vec2 const& vec )
  : x( vec.x ),
    y( vec.y )
{}

Vec2& Vec2::operator= ( Vec2 const& rhs )
{
    x = rhs.x;
    y = rhs.y;
    
    return *this;
}

/********************************* Operators **********************************/

Vec2 Vec2::operator- () const
{
    return Vec2( -x, -y );
}

Vec2 Vec2::operator+( Vec2 const& rhs ) const
{
    const float component_x{ x + rhs.x };
    const float component_y{ y + rhs.y };
    
    return Vec2{ component_x, component_y };
}

Vec2 Vec2::operator-( Vec2 const& rhs ) const
{
    Vec2 rhs_negative = Vec2{ -rhs.x, -rhs.y };
    
    return *this + rhs_negative;
}

Vec2 Vec2::operator*( const float rhs ) const
{
    return Vec2{ x * rhs, y * rhs };
}

Vec2 Vec2::operator/( const float rhs ) const
{
    return Vec2{ x / rhs, y / rhs };
}

/**************************** Assignment operators ****************************/

Vec2& Vec2::operator+=( Vec2 const& rhs )
{
    return *this = *this + rhs;
}

Vec2& Vec2::operator-=( Vec2 const& rhs )
{
    return *this = *this - rhs;
}

Vec2& Vec2::operator*=( const float rhs )
{
    return *this = *this * rhs;
}

Vec2& Vec2::operator/=( const float rhs )
{
    return *this = *this / rhs;
}

/**************************** Comparison operators ****************************/

bool Vec2::operator==( Vec2 const& rhs ) const
{
    const bool equal_x = fequals( x, rhs.x );
    const bool equal_y = fequals( y, rhs.y );
    
    return equal_x and equal_y;
}

bool Vec2::operator!=( Vec2 const& rhs ) const
{
    return not ( *this == rhs );
}

/********************************** Methods ***********************************/

float Vec2::getAngle() const
{
    return std::atan2( y, x );
}

float Vec2::getLength() const
{
    const float squared_x = powf( x, 2.0f );
    const float squared_y = powf( y, 2.0f );
    
    return sqrtf( squared_x + squared_y );
}

float Vec2::getDistance( Vec2 const& position ) const
{
    const Vec2 difference{ *this - position };
    
    return difference.getLength();
}

Vec2 Vec2::normalize() const
{
    const float length = this->getLength();
    
    if ( fequals( length, 0.0f ) )
    {
        return *this;
    }
    else
    {
        return *this / length;
    }
}

float Vec2::dot( Vec2 const& vec ) const
{
    return ( x * vec.x ) + ( y * vec.y );
}

Vec2 Vec2::getRotated( const float angle ) const
{
    const Vec2 rotated_unit_vector{ cosf( angle ), sinf( angle ) };
    // we multiply the vector using complex multiplication,
    // this should add their angles and multiply their length:
    return ( x * rotated_unit_vector ) + ( y * rotated_unit_vector );
}

/**************************** Extra functionality  ****************************/

Vec2 operator*( const float lhs, Vec2 const& rhs )
{
    return Vec2{ lhs * rhs.x, lhs * rhs.y };
}

float Vec2::distance( Vec2 const& lhs, Vec2 const& rhs )
{
    return lhs.getDistance( rhs );
}

float Vec2::dot( Vec2 const& lhs, Vec2 const& rhs )
{
    return lhs.dot( rhs );
}

Vec2 Vec2::normalize( Vec2 const& vec )
{
    return vec.normalize();
}

Vec2 Vec2::rotate( const float angle, Vec2 const& vec )
{
    return vec.getRotated( angle );
}
