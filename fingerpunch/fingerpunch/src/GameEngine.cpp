#include "GameEngine.h"
 
#include <SDL2/SDL.h>
#ifdef __APPLE__
    #include <SDL2_mixer/SDL_mixer.h>
    #include <SDL2_image/SDL_image.h>
#else
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_image.h>
#endif

#include <iostream>
#include <stack>

#include "graphics/Renderer_SDL2.h"
#include "file/File_SDL2_Image.h"
#include "input/User_Target.h"

GameEngine::GameEngine( User_Target* game )
  : game_target( game )
{
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 )
    {
        std::cerr << "ERROR: initializing SDL" << std::endl;
    }
    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) != 0 )
    {
        std::cerr << "ERROR: initializing SDL_Mixer" << std::endl;
    }
    /*
    if ( IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG ) != 0 )
    {
        std::cerr << "ERROR: initializing SDL_Image" << std::endl;
    }*/
    
    
    renderer = new Renderer_SDL2;
    File_SDL2_Image::init( dynamic_cast<Renderer_SDL2*>( renderer ) );
    
    user_input = new Input_Manager( renderer );

}

void GameEngine::run()
{
    std::stack<User_Target*> user_target_stack;
    
    user_target_stack.push( game_target );

    while ( not user_target_stack.empty() )
    {
        User_Target*& current_target = user_target_stack.top();
        
        user_input->update();
        
        User_Target::TARGET_STATUS status = current_target->update( user_input );
        
        switch ( status )
        {
            case User_Target::TARGET_STATUS::CONTINUE:
            {
                renderer->draw( current_target->getRenderSpace() );
                
            } break;
            case User_Target::TARGET_STATUS::NEW_TARGET:
            {
                User_Target* new_target = current_target->getNewTarget();

                if ( new_target != nullptr )
                {
                    user_target_stack.push( new_target );
                }
                
            } break;
            case User_Target::TARGET_STATUS::GO_BACK:
            {
                if ( not user_target_stack.empty() )
                {
                    user_target_stack.pop();
                }
                
            } break;
            case User_Target::TARGET_STATUS::EXIT:
            {
                return;
            } break;
        }
    }
}

GameEngine::~GameEngine()
{
    // the operating system takes care of
    // deleting resources, no need to
    // clean up when you have someone
    // else who does it ( rikeh HG ).
    /* 
    delete renderer;
    delete user_input;

    IMG_Quit();
    Mix_Quit();
    SDL_Quit();*/
}
