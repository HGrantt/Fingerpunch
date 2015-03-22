#include "Renderer_SDL2.h"

#include <iostream>
#include <string>
#include <chrono>

#include "../math/AABB.h"
#include "../file/Loader.h"
 
Renderer_SDL2::Renderer_SDL2()
{
    
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
    
    const int pos_x{ SDL_WINDOWPOS_UNDEFINED };
    const int pos_y{ SDL_WINDOWPOS_UNDEFINED };
    
    window = SDL_CreateWindow( nullptr, pos_x, pos_y,
                                window_width, window_height,
                                SDL_WINDOW_BORDERLESS  | SDL_WINDOW_FULLSCREEN  );
    
	renderer = SDL_CreateRenderer( window, -1, 0 );

    
    SDL_RenderSetLogicalSize( renderer, window_width, window_height );
    
    //buffer_renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_TARGETTEXTURE );
    //screen_buffer = SDL_CreateTexture( renderer,
    //                                   SDL_PIXELFORMAT_RGBA8888,
    //                                   SDL_TEXTUREACCESS_TARGET,
    //                                   width, height );
 
    //SDL_SetRenderTarget( buffer_renderer, screen_buffer );
    
}

Renderer_SDL2::~Renderer_SDL2()
{
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow  ( window   );
}


void Renderer_SDL2::draw( Render_Space* render_space )
{
    std::vector<Render_Object*> const& objects_to_draw
        = render_space->getDrawOrder();
    
    SDL_GetWindowSize( window, &window_width, &window_height );
    
    const Vec2 screen_size
    {
        static_cast<float>( window_width ),
        static_cast<float>( window_height )
    };
    //const float screen_size_max = fmaxf( screen_size.x, screen_size.y );
    
    SDL_RenderClear( renderer );
    
    for ( Render_Object* object : objects_to_draw )
    {
        if ( ( object == nullptr or not object->enabled ) ){ continue; }
        
        const Vec2 parallax_offset = calcParallaxOffset( *object, render_space );
        
        for ( Sprite* sprite_data : object->sprite_draw_order )
        {
            if (sprite_data == nullptr ){ continue; }
            // there's no guarantee that the sprite texture is loaded
            SDL_Texture* texture = fetchTexture( sprite_data->getPath() );

            if ( texture != nullptr )
            {
                const AABB sprite
                {
                    Vec2
                    {
                        ( sprite_data->pos * object->size )
                            + object->pos + parallax_offset
                    },
                    Vec2
                    {
                        ( sprite_data->size * object->size ) / 2
                    }
                };

                const Vec2 sprite_pos_transformed
                {
                    ((( 1.0f + sprite.pos.x ) - sprite.size.x ) / 2 ),
                    ((( 1.0f - sprite.pos.y ) - sprite.size.y ) / 2 )
                };

                const SDL_Rect draw_box
                {
                    static_cast<int>( sprite_pos_transformed.x * screen_size.x ),
                    static_cast<int>( sprite_pos_transformed.y * screen_size.y ),
                    static_cast<int>( sprite.size.x * screen_size.x  ),
                    static_cast<int>( sprite.size.y * screen_size.y  )
                };
            
                SDL_RenderCopy( renderer, texture, nullptr, &draw_box );
            }
        }
    }
    
    SDL_RenderPresent( renderer );
    SDL_Delay(30);// this should be moved elsewhere
}

Vec2 Renderer_SDL2::calcParallaxOffset( Render_Object const& render_obj, Render_Space* render_space ) const
{
    const float circle_speed_mod = 2250.0f;
    const float circle_offset_div = 125.0f;
    
    const float time
        = static_cast<float>( SDL_GetTicks() ) / circle_speed_mod;

    
    const Vec2 circle_vec
    {
        Vec2( cos( time ), sin( time ) ) / circle_offset_div
    };

    return render_obj.z_pos * 
            ( render_space->parallax_focus_point
            * render_space->parallax_mult + circle_vec );

}

SDL_Texture* Renderer_SDL2::fetchTexture( std::string const& path_name )
{
    // fetch the file from the database:
    File_Type* image_file = database.getFile( path_name );
    
    // if the file wasn't in the database, we load it:
    if ( image_file == nullptr )
    {
        database.addFileRef( new File_SDL2_Image( path_name ) );
        image_file = database.getFile( path_name );
    }
    
    // if loading was successful, we can return the texture:
    if ( image_file != nullptr )
    {
        File_SDL2_Image* image = dynamic_cast<File_SDL2_Image*>( image_file );
        return image->texture;
    }
    else
    {
        return nullptr;
    }
}






