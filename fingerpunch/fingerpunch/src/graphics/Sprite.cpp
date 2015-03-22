#include "Sprite.h"
 
Sprite::Sprite( std::string const& path_name,
                Vec2 const& pos,
                Vec2 const& size )
  : 
    pos ( pos  ),
    size( size ),
    path_name( path_name )
{}

std::string const& Sprite::getPath() const
{
    return path_name;
}
