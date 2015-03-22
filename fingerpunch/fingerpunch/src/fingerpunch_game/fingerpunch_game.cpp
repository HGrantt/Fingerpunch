#include "fingerpunch_game.h"
#include <iostream>

Fingerpunch_Game::Fingerpunch_Game()
{
    std::cout << "fp_start" << std::endl;

    addDecoration( Vec2(), Vec2( 3.0f ), -25.0f, "./images/platform.png" );
    
    addDecoration( Vec2(  1.0f, -0.5f ), Vec2( 4.5f ),  10.0f, "./images/smoke_puff.png" );
    //addDecoration( Vec2( -0.1f,  0.7f ), Vec2( 3.5f ), -10.0f, "./images/smoke_puff.png" );
    addDecoration( Vec2( -0.8f, -0.3f ), Vec2( 4.0f ), -15.0f, "./images/smoke_puff.png" );
                
    addElement( Vec2( .0f,  .4f ), Vec2( 0.4f, 0.275f ), "./images/play.png" );
    
    //addElement( Vec2( .0f,  -.0f ), Vec2( 0.4f, 0.275f ), "./images/settings.png" );
    
    addElement( Vec2( .0f,  -.4f ), Vec2( 0.4f, 0.275f ), "./images/quit.png" );
    

    


}

Fingerpunch_Game::~Fingerpunch_Game()
{
    if ( game != nullptr )
    {
        delete game;
    }
}

User_Target::TARGET_STATUS Fingerpunch_Game::update( Input_Manager* input_manager )
{
    if ( not menu_started )
    {
        const std::string music_path = "./Audio/musicbox_rep.wav";

        shared.addFileRef( new File_SDL2_Music( music_path ) );
        File_Type* music_file = shared.getFile( music_path );
    
        if ( music_file != nullptr )
        {
            music = dynamic_cast<File_SDL2_Music*>( music_file );
            music->play();
        }
        menu_started = true;
    }


    if ( input_manager->escape.isReleased() )
    {
        return User_Target::TARGET_STATUS::GO_BACK;
    }
    else if ( input_manager->quit )
    {
        return User_Target::TARGET_STATUS::EXIT;
    }
    
    getRenderSpace()->parallax_focus_point = input_manager->mouse_position;
    
    if ( input_manager->mouse_button.isTapped() )
    {
        
        Menu_Element* element = getActiveElement( input_manager->mouse_position );
        
        if ( element != nullptr )
        {
            std::cerr << element->getImage()->getPath() << std::endl;
            
            if ( element->getImage()->getPath() == "./images/play.png"  )
            {
                std::cerr << "purei" << std::endl;
                if ( game != nullptr )
                {
                    delete game;
                }
                menu_started = false;
                if ( music != nullptr )
                {
                    std::cerr << "music stopped" << std::endl;
                    music->stop();
                }
                
                game = new Fighturu();
                new_target = game;
            
                return User_Target::TARGET_STATUS::NEW_TARGET;
            }
            /*else if ( element->getImage()->getPath() == "./images/settings.png" )
            {
                std::cerr << "opur shrettins" << std::endl;
                new_target = settings;
                return User_Target::TARGET_STATUS::NEW_TARGET;
            }*/
            else if ( element->getImage()->getPath() == "./images/quit.png" )
            {
                std::cerr << "You Chiker!" << std::endl;
                return User_Target::TARGET_STATUS::EXIT;
            }

        }
        else
        {
            std::cerr << "you no findu butturu?" << std::endl;
        }
    }

    return User_Target::TARGET_STATUS::CONTINUE;
}

User_Target*  Fingerpunch_Game::getNewTarget()
{
    return new_target;
}

