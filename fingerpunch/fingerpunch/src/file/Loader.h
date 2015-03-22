#ifndef _Loader_h_
#define _Loader_h_
 
#include "File_Type.h"

#include <map>

/**
 * class holding file-path information
 */
class File_Type;

/**
 * Class for loading files
 */
class Loader
{
public:

  /**
   * Constructor 
   */
    Loader();
  
  /**
   * Destructor
   */
    ~Loader();


  /**
   * Adds file reference to the database and ignores if double
   * @param file File_Type containing information about the wanted file
   * @return true if it added the file or if double, else false
   */
    bool addFileRef   ( File_Type* file );

  /**
   * Removes file reference from the database
   * @param path the name of the file
   */
    void removeFileRef( std::string const& path );

  /**
   * Fetches a wanted file
   * @param path the the name of the wanted file
   * @return the wanted file or nullptr if not found
   */
    File_Type* getFile( std::string const& path );
    
private:



    /// Struct for file references
    struct File_Ref;

    /// map containing files and references
    std::map<std::string, File_Ref> database;
    
};

/// struct for file references pointers and a counter for the number of files
struct Loader::File_Ref
{
    File_Type* file_ptr;
    int        ref_counter;
};

#endif /* defined(_Loader_h_) */
