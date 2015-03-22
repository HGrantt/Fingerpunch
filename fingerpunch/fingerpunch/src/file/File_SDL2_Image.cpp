#include "File_SDL2_Image.h"
 
#include <iostream>
#include <SDL2/SDL.h>

#ifdef __APPLE__
    #include <SDL2_image/SDL_image.h>
#else
    #include <SDL2/SDL_image.h>
#endif

SDL_Renderer* File_SDL2_Image::renderer = nullptr;

File_SDL2_Image::File_SDL2_Image( std::string const& path )
  : File_Type( path )
{
    texture = nullptr;
}
    
File_SDL2_Image::~File_SDL2_Image()
{

    if ( texture != nullptr )
    {
        SDL_DestroyTexture( texture );
        texture = nullptr;
    }
}

void File_SDL2_Image::init( Renderer_SDL2* renderer )
{
    File_SDL2_Image::renderer = renderer->renderer;
}

bool File_SDL2_Image::load()
{
    if ( renderer == nullptr )
    {
        std::cerr << "ERROR: Renderer not initialized." << std::endl;
        return false;
    }

    SDL_Surface* surface = IMG_Load( path.c_str() );
    
    if ( surface != nullptr )
    {
        // calculate aspect ratio:
        aspect_ratio.x = static_cast<float>( surface->w );
        aspect_ratio.y = static_cast<float>( surface->h );
        
        const float aspect_max = fmax( aspect_ratio.x, aspect_ratio.y );
        aspect_ratio /= aspect_max;
        
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if ( texture == nullptr )
        {
            std::cerr << "ERROR: failed to create texture." << std::endl;
        }
    }
    else
    {
        std::cerr << "ERROR: could not load '"
            << getPath() << "'" << std::endl;
    }
    
    // clean up dat shiet!
    SDL_FreeSurface( surface );
    surface = nullptr;
    
    return ( texture != nullptr );
}