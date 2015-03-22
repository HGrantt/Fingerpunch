#ifndef __aaa__SDL2_Image__
#define __aaa__SDL2_Image__
 
#include "File_Type.h"
#include "../graphics/Renderer_SDL2.h"
#include "../math/Vec2.h"
#include <SDL2/SDL.h>

class Renderer_SDL2;

/**
 * Class for handeling images,
 * Inherits from File_Type
 */
class File_SDL2_Image : public File_Type
{
public:

  /**
   * Constructor sets texture to nullptr
   * @param path path for the File_Type
   */
    File_SDL2_Image( std::string const& path );

  /**
   * Destructor
   */
    virtual ~File_SDL2_Image();

  /**
   * For the purpose that surfaces can be rendered to textures
   */
    static void init( Renderer_SDL2* renderer );


private:

  /**
   * Renderer_SDL2 is friend for the init function
   */
    friend class Renderer_SDL2;

  /**
   * loads images and creates textures
   */
    virtual bool load();

    /// renderer used by load() 
    static SDL_Renderer* renderer;

    /// texture used by load()
    SDL_Texture* texture;

    /// aspect ratio wanted
    Vec2         aspect_ratio;

};

#endif /* defined(__aaa__SDL2_Image__) */
