#ifndef _Line_h_
#define _Line_h_
 
#include "Vec2.h"
#include <array>

#define POINTS_IN_LINE 2

/**
 * a line between two points
 */
class Line
{
public:

    /// constructor
    Line();
    
    /**
     * constructor
     * @param begin_x
     * @param begin_y
     * @param end_x
     * @param end_y
     */
    Line( const float begin_x, const float begin_y,
          const float end_x,   const float end_y );

    /**
     * constructor
     * @param begin is the starting point
     * @param end is the end point
     */
    Line( Vec2 const& begin, Vec2 const& end );

    /// the result of an intersection between two lines
    struct Intersection_Result;
    
    /**
     * tests if two lines intersect.
     * @param line is the line that will be tested with the current line
     * @return detailed information about the intersection
     */
    Intersection_Result intersection_test( Line const& line ) const;
    
    /**
     * tests if two lines intersect.
     * @param line is the line that will be tested with the current line
     * @return true if the lines intersect somehow
     */
    bool intersects  ( Line const& line ) const;
    
    /// true if the lines are parallell
    bool isParallell ( Line const& line ) const;
    
    /// true if the lines are orthogonal
    bool isOrthogonal( Line const& line ) const;
    
    /// true if the line is just a point
    bool isPoint() const;
    
    /// the length of the line
    float getLength() const;
    
    /// the angle of the line
    float getAngle () const;
    
    /// a normalized direction vector
    Vec2  getDirectionVector() const;
    
    /// the difference of the end and the beginning of the line
    Vec2  getDiffVector() const;

    /// access for the points in the line
    Vec2&       operator[]( int index );
    
    /// access for the points in the line
    Vec2 const& operator[]( int index ) const;
    
private:

    /// the points in the line
    Vec2 points[ POINTS_IN_LINE ];

};

/**
 * detailed information of a line intersection.
 */
struct Line::Intersection_Result
{
    /// solved line equations used for validation
    bool  solved  [ POINTS_IN_LINE ];
    /// percentages on the line where the intersection occured
    float solution[ POINTS_IN_LINE ];
    /// the points where the collision occured
    Vec2  point   [ POINTS_IN_LINE ];

    /// is intersecting
    bool isIntersecting() const;
    /// intersection is a point
    bool isPoint() const;
    /// intersection is a line
    bool isLine() const;
    
    /// the first point where an intersection occurs
    Vec2  getPoint() const;
    /// the percentage solution where an intersection occurs
    float getPointSolution() const;
};

#endif /* defined(_Line_h_) */
