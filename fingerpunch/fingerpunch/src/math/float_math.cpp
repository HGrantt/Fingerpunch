#include "float_math.h"
 
float fequals( const float a, const float b )
{
    return std::fabs( a - b ) < FLT_EPSILON;
}

float fclamp( const float f, const float min, const float max )
{
    const float clamped_lower = std::fmax( min, f );
    const float clamped_both  = std::fmin( max, clamped_lower );
    
    return clamped_both;
}
