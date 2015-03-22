#ifndef _Sprite_h_
#define _Sprite_h_
 
#include "../math/Vec2.h"

#include <string>

/**
 * Class for holding information about elements
 */
class Sprite
{
public:

  /// position on the screen
    Vec2  pos;

  /// size of the sprite
    Vec2  size;

  /**
   * Constructor for Sprite
   * @param path_name the path name of a specific image
   * @param pos the position on the screen
   * @param the size
   */
    Sprite( std::string const& path_name,
            Vec2 const&        pos  = Vec2( 0.0f ),
            Vec2 const&        size = Vec2( 1.0f ) );
    
    /// returns the path name
    std::string const& getPath() const;

    /// the path name of a specific image
    std::string path_name;

};

#endif /* defined(_Sprite_h_) */
