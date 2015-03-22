#ifndef _File_SDL2_Audio_h_
#define _File_SDL2_Audio_h_
 
#include "File_Type.h"

#ifdef __APPLE__
    #include <SDL2_mixer/SDL_mixer.h>
#else
    #include <SDL2/SDL_mixer.h>
#endif

#include <string>

/**
 * Class for handeling sounds and music
 * Inherits from File_Type
 */
class File_SDL2_Audio : public File_Type
{
public:

  /**
   * Constructor
   * @param path the files path
   */
    File_SDL2_Audio( std::string const& path );

  /**
   * Pure virtual function for playing music
   * @param repeat how many times to repeat,
   * defalut = -1 for unlimited times
   */
    virtual void play( int repeat = -1 )=0;

  /**
   * Pure virtual function for stopping a sound
   */
    virtual void stop()=0;
};

/**
 * Class for handling of music
 * Inherits from File_SDL2_Audio
 */
class File_SDL2_Music : public File_SDL2_Audio
{
public:

  /**
   * Constructor
   * @param path the path of the file
   */
    File_SDL2_Music( std::string const& path );

  /**
   * Play funcion for music
   * @param repeat how many times to repeat,
   * defalut = -1 for unlimited times
   */
    virtual void play( int repeat = -1 );

   /**
    * Function for stopping a sound
    */
    virtual void stop();

   /**
    * Destructor for File_SDL2_Music
    */
    virtual ~File_SDL2_Music();
    

private:

  /**
   * Function for loading a sound or music
   */
    virtual bool load();

    /// The music data
    Mix_Music* music_data;
  
};

/**
 * Class for sounds
 * Inherits from File_SDL2_Audio
 */
class File_SDL2_Sound : public File_SDL2_Audio 
{
public:
  
  /**
   * Constructor
   * @param path path for the sound
   */
    File_SDL2_Sound( std::string const& path );

  /**
   * Funktion for playing the sound
   */
    virtual void play( int repeat = -1 );
  
  /**
   * Stop playing the sound
   */
    virtual void stop();

  /**
   * Destructor for sound
   */
    virtual ~File_SDL2_Sound();

private:
  /**
   * Load funcion for sounds
   * @return true if sound file is loaded, else false
   */
    virtual bool load();
  
    /// the sound data
    Mix_Chunk* sound_data;

};

#endif /* defined(_File_SDL2_Audio_h_) */
