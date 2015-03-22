#ifndef _Game_h_
#define _Game_h_
 
#include "graphics/Renderer.h"
#include "menu/Menu.h"
#include "game_world/Game_World.h"
#include "input/Input_Manager.h"
#include <vector>

/**
 * Game engine runs the game
 */
class GameEngine
{
public:

    /// Constructor
    GameEngine( User_Target* game );
    
    /// Destructor
    ~GameEngine();
    
    /// starts the game
    void run();
    
private:
    
    /// renderer
    Renderer*       renderer;
    
    /// input manager
    Input_Manager*  user_input;

    /// a pointer to the game itself
    User_Target*    game_target;

};

#endif /* defined(_Game_h_) */
