#include "File_Type.h"
 
File_Type::File_Type( std::string const& path )
{
    this->path = path;
}

std::string const& File_Type::getPath() const
{
    return path;
}
