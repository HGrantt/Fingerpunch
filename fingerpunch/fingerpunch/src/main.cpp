#include "GameEngine.h"
#include "fingerpunch_game/fingerpunch_game.h"
 
int main()
{
    User_Target* game = new Fingerpunch_Game;

    GameEngine game_engine( game );
    
    game_engine.run();
    
    delete game;
    
    return 0;
}
