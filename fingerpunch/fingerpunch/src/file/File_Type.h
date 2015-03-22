#ifndef _File_Type_h_
#define _File_Type_h_

#include "Loader.h"

#include <string>


class Loader;

/**
 * Class for file types
 */
class File_Type
{
public:

  /**
   * Constructor
   * @param path path for file
   */
    File_Type( std::string const& path );

  /**
   * Destructor
   */
    virtual ~File_Type(){};

  /**
   * Function for getting the path of wanted file
   * @return path of the file
   */
    std::string const& getPath() const;

protected:

  /**
   * Friend for usage of the load function
   * Only the loader can load files
   */
    friend class Loader;

    /// pure virtual funktion
    virtual bool load()=0;

    /// the path of a file
    std::string path;

};

#endif /* defined(_File_Type_h_) */
