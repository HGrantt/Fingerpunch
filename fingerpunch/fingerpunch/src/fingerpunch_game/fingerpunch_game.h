#ifndef _fingerpunch_game_h_
#define _fingerpunch_game_h_
 
#include "../input/User_Target.h"
#include "../menu/Menu.h"
#include "Fighturu.h"
class Fighturu;

#include "../file/Loader.h"
#include "../file/File_SDL2_Audio.h"

/**
 * the game itself, put this in the game engine and look at it go!
 */
class Fingerpunch_Game : public Menu
{
public:

    /// updates the menu
    virtual TARGET_STATUS update( Input_Manager* input_manager );
    
    /// acquire a new target ( the game )
    virtual User_Target*  getNewTarget();
    
    /// constructor
    Fingerpunch_Game();
    
    /// destructor
    virtual ~Fingerpunch_Game();

private:

    /// all files loaded by the game
    Loader shared;

    /// the new target
    User_Target* new_target{ nullptr };
    
    /// the playable game
    Fighturu* game{ nullptr };
    
    /// menu init for things that needs the constructor to run first
    bool menu_started{ false };
    
    /// the music that is playing in the background
    File_SDL2_Music* music{ nullptr };

};

#endif /* defined(_fingerpunch_game_h_) */
