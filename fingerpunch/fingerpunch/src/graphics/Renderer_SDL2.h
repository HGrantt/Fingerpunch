#ifndef _Renderer_SDL2_h_
#define _Renderer_SDL2_h_
 
#include "Renderer.h"
#include "Sprite.h"

#include "../file/Loader.h"
#include "../file/File_SDL2_Image.h"
#include <SDL2/SDL.h>
#include <string>

/**
 * Class for handeling the window and renderer
 * inherits from Renderer
 */
class Renderer_SDL2 : public Renderer
{
public:

  /**
   * Constructor
   */
    Renderer_SDL2();

  /**
   * Destructor
   */
    ~Renderer_SDL2();
    
  /**
   * Clears the renderer and draws all of the objects on the screen
   *
   */
    virtual void draw( Render_Space* render_space );

private:

    /// gives acces to window and renderer
    friend class File_SDL2_Image;

    SDL_Window*   window;
    SDL_Renderer* renderer;
    
    //SDL_Renderer* buffer_renderer;
    //SDL_Texture*  screen_buffer;

    /// A database containing strings with the image that should be loaded
    Loader database;

  /**
   * Offsett for the paralax effect
   * @param render_obj a render object containing
   * position size, z position and if it shows
   * @param render_space the space where something should be drawn
   * @return a position for the paralax offset
   */
    Vec2 calcParallaxOffset( Render_Object const& render_obj,
                             Render_Space* render_space ) const;

  /**
   * Fetches the wanted texture from the database of loads it
   * @param path_name the name of the path for a image file
   * @returns the texture or nullptr if not found
   */
    SDL_Texture* fetchTexture( std::string const& path_name );

  
};

#endif /* defined(_Renderer_SDL2_h_) */
