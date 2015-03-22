#include "Line.h"
 
#include "Vec2.h"
#include "float_math.h"

#include <iostream>

// constructors:
Line::Line()
{
    const Vec2 origo = Vec2( 0.0f, 0.0f );
    
    points[0] = origo;
    points[1] = origo;
}

Line::Line( const float begin_x, const float begin_y,
            const float end_x, const float end_y )
{
    const Vec2 begin( begin_x, begin_y );
    const Vec2 end  ( end_x,   end_y   );

    points[0] = begin;
    points[1] = end;
}

Line::Line( Vec2 const& begin, Vec2 const& end )
{
    points[0] = begin;
    points[1] = end;
}

// accessors:

Vec2& Line::operator[]( int index )
{
    return points[ index ];
}

Vec2 const& Line::operator[]( int index ) const
{
    return points[ index ];
}

// booleans:
bool Line::isParallell( Line const& line ) const
{
    const Vec2 rotated_vec =  ( line[1] - line[0] ).rotate( M_PI / 2 );
    
    const Line orthogonal_vec( Vec2( 0.0f, 0.0f ), rotated_vec );
    
    return isOrthogonal( orthogonal_vec );
}

bool Line::isOrthogonal( Line const& line ) const
{
    const Vec2 a_direction = getDirectionVector();
    const Vec2 b_direction = line.getDirectionVector();
    
    const float dot_product = a_direction.dot( b_direction );
    
    return fequals( dot_product, 0.0f );
}

bool Line::isPoint() const
{
    return points[0] == points[1];
}

Line::Intersection_Result Line::intersection_test( Line const& line ) const
{
    Line::Intersection_Result result;
    
    const int num_lines = 2;
    
    const Vec2 position [num_lines]{ points[0], line[0] };
    const Vec2 direction[num_lines]{ getDiffVector(), line.getDiffVector() };
    
    const Vec2  difference( position[1] - position[0] );
    
    const float direction_sum[num_lines]{ direction[0].x + direction[0].y, direction[1].x + direction[1].y };
    
    const float difference_sum = difference.x + difference.y;
    
    for ( int i = 0; i < num_lines; i++ )
    {
        const bool possibly_solved = not fequals( direction_sum[i], 0.0f );
        if ( possibly_solved )
        {
            result.solution[i] = difference_sum / direction_sum[i];
            result.point[i] = position[i] + result.solution[i] * direction[i];
            result.solved[i] = ( 0.0f <= result.solution[i]
                                 and result.solution[i] <= 1.0f );
        }
    }

    return result;
}

bool Line::intersects( Line const& line ) const
{
    return intersection_test( line ).isIntersecting();
}
    
float Line::getLength() const
{
    const Vec2 diff_vector{ points[1] - points[0] };
    
    return diff_vector.getLength();
}

float Line::getAngle() const
{
    const Vec2 diff_vector{ points[1] - points[0] };
    
    return diff_vector.getAngle();
}

Vec2 Line::getDiffVector() const
{
    return points[1] - points[0];
}

Vec2 Line::getDirectionVector() const
{
    const Vec2 diff_vector{ points[1] - points[0] };
    
    return diff_vector.normalize();
}

//Intersection_result:

bool Line::Intersection_Result::isIntersecting() const
{
    return solved[0] or solved[1];
}

bool Line::Intersection_Result::isPoint() const
{
    return solved[0] xor solved[1];
}

bool Line::Intersection_Result::isLine() const
{
    return solved[0] and solved[1];
}

Vec2 Line::Intersection_Result::getPoint() const
{
    if ( not solved[1] )
    {
        return point[0];
    }
    else
    {
        return point[1];
    }
}

float Line::Intersection_Result::getPointSolution() const
{
    if ( not solved[1] )
    {
        return solution[0];
    }
    else
    {
        return solution[1];
    }
}
