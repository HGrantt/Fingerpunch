#include "File_SDL2_Audio.h"

#include <iostream>

// -------- AUDIO --------
File_SDL2_Audio::File_SDL2_Audio( std::string const& path)
  : File_Type( path )
{}

// -------- MUSIC --------
File_SDL2_Music::File_SDL2_Music( std::string const& path )
  : File_SDL2_Audio( path ),
    music_data( nullptr )
{}
    
File_SDL2_Music::~File_SDL2_Music()
{
    if ( music_data != nullptr )
    {
        Mix_FreeMusic( music_data );
        music_data = nullptr;
    }
}

bool File_SDL2_Music::load()
{
    const char* file_path = getPath().c_str();
    
    music_data = Mix_LoadMUS( file_path );
    
    return ( music_data != nullptr );
}

void File_SDL2_Music::play( int repeat )
{
    Mix_PlayMusic( music_data, repeat );
}

void File_SDL2_Music::stop()
{
    Mix_HaltMusic();
}

// -------- SOUND --------
File_SDL2_Sound::File_SDL2_Sound( std::string const& path )
  : File_SDL2_Audio( path ),
    sound_data( nullptr )
{}
    
File_SDL2_Sound::~File_SDL2_Sound()
{
    if ( sound_data != nullptr )
    {
        Mix_FreeChunk( sound_data );
        sound_data = nullptr;
    }
}

bool File_SDL2_Sound::load()
{
    const char* file_path = getPath().c_str();
    
    sound_data = Mix_LoadWAV( file_path );

    return ( sound_data != nullptr );
}

void File_SDL2_Sound::play( int )
{
    Mix_PlayChannel( -1, sound_data, 0 );
}

void File_SDL2_Sound::stop()
{}
