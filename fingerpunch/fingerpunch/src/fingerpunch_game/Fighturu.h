#ifndef _fingerpunch_Main_Menu_h_
#define _fingerpunch_Main_Menu_h_

#include "../game_world/Game_World.h"
#include "fingerpunch_game.h"

#include "health_display.h"
#include "Power_up.h"
#include "Player.h"
#include "Platform.h"
#include "Decoration.h"

#include <SDL2/SDL.h>

#include "../file/File_SDL2_Audio.h"

#include <string>

/**
 * The basic game mode. It's quite fun!
 */
class Fighturu : public Game_World
{
public:

    /// updates the game
    virtual User_Target::TARGET_STATUS update( Input_Manager* input_manager );

    //virtual TARGET_STATUS update( Input_Manager* input_manager )=0;
    
    /// used by GameEngine to acquire new targets
    virtual User_Target*  getNewTarget();//{ return nullptr; }
    
    //virtual Render_Space* getRenderSpace()=0;
    
    /// constructor
    Fighturu();
    
    /// destructor
    virtual ~Fighturu();
    

private:

    /// all files loaded by the game mode
    Loader  data;

    /// player one
    Player* player_one;
    
    /// player two
    Player* player_two;
    
    /// the background image
    Decoration* background;
    
    /// game over
    bool game_over{ false };
    
    /// true when game over state has started
    bool game_over_init{ false };
    
    /// the current music that is played
    File_SDL2_Music* music{ nullptr };

    /// player one health indicator
    Health_Display* p1_healthbar{ nullptr };
    
    /// player two health indicator
    Health_Display* p2_healthbar{ nullptr };
    
    /// all powerups in the level
    std::vector<Power_Up*> power_ups;
    
    /// last tick when a powerup spawned
    int last_power_spawn{ static_cast<int>( SDL_GetTicks() ) };
    
    /// last tick when a powerup was removed
    int last_power_kill { static_cast<int>( SDL_GetTicks() ) };
    
    /// time until the next powerup appears
    int time_until_next_spawn{ 0 };
    
    /// the image that is displayed when the game is over
    Decoration* win_decoration{ nullptr };
    
    /// the tick when the game was finished
    int win_time_stamp{ -1 };

};

#endif /* defined(_fingerpunch_Main_Menu_h_) */
