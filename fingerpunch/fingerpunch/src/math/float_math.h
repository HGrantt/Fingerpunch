#ifndef _float_math_h_
#define _float_math_h_
 
#include <cmath>
#include <cfloat>

/**
 * non-binary comparison of floats
 * @param a float
 * @param b float
 * @return true if almost exactly equal
 */
float fequals( const float a, const float b );

/**
 * limits the upper and lower value of a float
 * @param f is the float
 * @param min is the lower limit
 * @param max is the upper limit
 */
float fclamp( const float f, const float min = 0.0f, const float max = 1.0f );

#endif /* defined(_float_math_h_) */
