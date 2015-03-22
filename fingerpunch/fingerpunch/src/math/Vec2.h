#ifndef _Vec2_h_
#define _Vec2_h_

/**
 * a point or a direction in two dimensions
 */
class Vec2
{
public:

    /// x component
    float x;

    /// y component
    float y;
    
    /// Constructor
    Vec2();
    
    /// constructor for both x and y components
    explicit Vec2( const float scalar );
    
    /// constructor for x and y components 
    Vec2( const float component_x, const float component_y );
    
    /// copy constructors
    Vec2( Vec2 const& vec );
    
    /// copy assignment
    Vec2& operator= ( Vec2 const& rhs );
    
    /// opposite direction of the vector
    Vec2  operator- () const;
    
    // add two vectors
    Vec2  operator+ ( Vec2 const& rhs ) const;
    
    // subtract two vectors
    Vec2  operator- ( Vec2 const& rhs ) const;
    
    /// multiply a vector with a scalar value
    Vec2  operator* ( const float rhs ) const;
    
    /// divide the vector with a scalar value
    Vec2  operator/ ( const float rhs ) const;
    
    /// add a vectors components to the current one
    Vec2& operator+=( Vec2 const& rhs );
    
    /// subtract a vectors components from the current one
    Vec2& operator-=( Vec2 const& rhs );
    
    /// multiply the current vectors components with a scalar value
    Vec2& operator*=( const float rhs );
    
    /// divide the current vectors components with a scalar value
    Vec2& operator/=( const float rhs );
    
    /// compare if two vectors are almost exactly the same
    bool operator==( Vec2 const& rhs ) const;
    
    /// compare if two vectors are not the same
    bool operator!=( Vec2 const& rhs ) const;

    /// the length of the vector
    float getLength() const;
    
    /// the angle of the vector
    float getAngle () const;
    
    /// the distance between two vectors
    float getDistance( Vec2 const& v ) const;
    
    /// a rotated version of the current vector
    Vec2  getRotated( const float angle ) const;
    
    /// the dot product of two vectors
    float dot( Vec2 const& v ) const;
    
    /// a vector in the same direction but with the length 1.0
    Vec2  normalize() const;
    
    /// a vector in the same direction but with the length 1.0
    static Vec2  normalize( Vec2 const& v );
    
    /// the distance between two vectors
    static float distance ( Vec2 const& a, Vec2 const& b );
    
    /// the dot product of two vectors
    static float dot      ( Vec2 const& a, Vec2 const& b );
    
    /// a rotated vector with the requested angle
    static Vec2  rotate   ( const float angle, Vec2 const& v=Vec2{ 1.0f, 0.0f } );

};

/// multiply a scalar value with a vector
Vec2 operator*( const float lhs, Vec2 const& rhs );

#endif /* defined(_Vec2_h_) */
