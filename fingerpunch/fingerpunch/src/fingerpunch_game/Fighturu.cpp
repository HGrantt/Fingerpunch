#include "Fighturu.h"

#include "../math/float_math.h"
#include <iostream>

#include "../math/AABB.h"

User_Target::TARGET_STATUS Fighturu::update( Input_Manager* input_manager )
{
    // Check exit / go back-status
    if ( input_manager->escape.isReleased() )
    {
        if ( music != nullptr )
        {
            music->stop();
        }
        return User_Target::TARGET_STATUS::GO_BACK;
    }
    else if ( input_manager->quit )
    {
        if ( music != nullptr )
        {
            music->stop();
        }
        return User_Target::TARGET_STATUS::EXIT;
    }
    else if ( game_over )
    {
        // set parallax point:
        getRenderSpace()->parallax_focus_point = input_manager->mouse_position * 4;
        // slowmotion:
        Player* winner = ( player_one->health > 0 ) ? player_one : player_two;
        Player* loser  = ( player_one->health > 0 ) ? player_two : player_one;
        

        if ( not game_over_init )
        {
            win_time_stamp = SDL_GetTicks();
            loser->render_object->enabled = false;
            
            // hide objects:
            for ( Power_Up* p_up : power_ups )
            {
                p_up->render_object->enabled = false;
            }
            win_decoration = new Decoration( "./images/" + winner->name + "_win.png",
                                            Vec2( 1.5f, 2.75f ), 10.0f );
            win_decoration->render_object->enabled = false;
            addGameObject( win_decoration );
            
            game_over_init = true;
            
            // swap background:
            std::cerr << "game ovah, prease come pray won moah time." << std::endl;
            background->render_object->sprite_draw_order.at(0)->path_name
                = "./images/mao.jpg";
                
                
            // play sound
            if ( music != nullptr )
            {
                music->stop();
            }
            
            const std::string win_sound_path = "./Audio/win.wav";
            File_Type* win_sound_file = data.getFile( win_sound_path );
    
            if ( win_sound_file == nullptr )
            {
                data.addFileRef( new File_SDL2_Music( win_sound_path ) );
                win_sound_file = data.getFile( win_sound_path );
            }
            if ( win_sound_file != nullptr )
            {
                music = dynamic_cast<File_SDL2_Music*>( win_sound_file );
                music->play(0);
            }
            
        }
        
        if ( SDL_GetTicks() > win_time_stamp + 500 )
        {
            p1_healthbar->render_object->enabled = false;
            p2_healthbar->render_object->enabled = false;
            winner->render_object->enabled = false;
            
            win_decoration->render_object->enabled = true;
        }
        else
        {
            winner->update();
            updatePositions( 1.0f / 120.0f );
        }
    
        return User_Target::TARGET_STATUS::CONTINUE;
    }
    
    updatePositions();
    
    // Set parallax focus point:
    Vec2* focus_point = &getRenderSpace()->parallax_focus_point;
    
    
    *focus_point = Vec2( player_one->physics_object->pos
                       + player_two->physics_object->pos );

    *focus_point = Vec2
    {
        fclamp( getRenderSpace()->parallax_focus_point.x, -1.5f, 1.5f ) * 8,
        fclamp( getRenderSpace()->parallax_focus_point.y, -1.5f, 1.5f ) * 8
    };
    
    // Jump:
    if ( input_manager->p2_jump.isTapped()
        and player_two->physics_object->state == Physics_Object::COLLIDING )
    {
        player_two->physics_object->velocity += Vec2( 0.0f, 3.0f );
    }
    if ( input_manager->p1_jump.isTapped()
        and player_one->physics_object->state == Physics_Object::COLLIDING )
    {
        player_one->physics_object->velocity += Vec2( 0.0f, 3.0f );
    }
    
    // Move right / left:
    if ( input_manager->p1_left.isPressed()
         xor input_manager->p1_right.isPressed() )
    {
        const float direction_mult = ( input_manager->p1_right.isPressed()
                                       ? 1.0f : -1.0f );
        player_one->physics_object->velocity += Vec2( 0.15f, 0.0f )
                                                * direction_mult;
    }
    
    if ( input_manager->p2_left.isPressed()
         xor input_manager->p2_right.isPressed() )
    {
        const float direction_mult = ( input_manager->p2_right.isPressed()
                                       ? 1.0f : -1.0f );
        
        player_two->physics_object->velocity += Vec2( 0.15f, 0.0f )
                                                * direction_mult;

    }
    bool play_hit_sound = false;
    // hit start animation:
    
    // front
    if ( input_manager->p1_hit_front.isTapped()
            and player_one->fist_front_state == Player::FIST_STATE::IDLE )
    {
        player_one->fist_tick_start_front = SDL_GetTicks();
        player_one->fist_front_state = Player::FIST_STATE::DANGEROUS;
        play_hit_sound = true;
    }
    
    if ( input_manager->p2_hit_front.isTapped()
            and player_two->fist_front_state == Player::FIST_STATE::IDLE )
    {
        player_two->fist_tick_start_front = SDL_GetTicks();
        player_two->fist_front_state = Player::FIST_STATE::DANGEROUS;
        play_hit_sound = true;
    }
    
    // back
    if ( input_manager->p1_hit_back.isTapped()
            and player_one->fist_back_state == Player::FIST_STATE::IDLE )
    {
        std::cerr << "h1" << std::endl;
        player_one->fist_tick_start_back = SDL_GetTicks();
        player_one->fist_back_state = Player::FIST_STATE::DANGEROUS;
        play_hit_sound = true;
    }
    
    if ( input_manager->p2_hit_back.isTapped()
            and player_two->fist_back_state == Player::FIST_STATE::IDLE )
    {
        std::cerr << "h2" << std::endl;
        player_two->fist_tick_start_back = SDL_GetTicks();
        player_two->fist_back_state = Player::FIST_STATE::DANGEROUS;
        play_hit_sound = true;
    }

    // hit sound:
    if ( play_hit_sound )
    {
        const std::string hit_sound_path = "./Audio/whip.wav";
        // fetch the file from the database:
        File_Type* hit_sound_file = data.getFile( hit_sound_path );
    
        // if the file wasn't in the database, we load it:
        if ( hit_sound_file == nullptr )
        {
            data.addFileRef( new File_SDL2_Sound( hit_sound_path ) );
            hit_sound_file = data.getFile( hit_sound_path );
        }
    
        // if loading was successful, we can return the texture:
        if ( hit_sound_file != nullptr )
        {
            File_SDL2_Sound* sound = dynamic_cast<File_SDL2_Sound*>( hit_sound_file );
            sound->play();
        }

    }

    // hits:
    const float hit_dist = 0.2f;
    const int   hit_dmg  = 1;
    
    if ( Vec2::distance( player_one->physics_object->pos,
                                    player_two->physics_object->pos ) < hit_dist )
    {
        if ( (  player_one->fist_front_state == Player::FIST_STATE::DANGEROUS
             or player_one->fist_back_state  == Player::FIST_STATE::DANGEROUS ) )
        {
            player_two->health -= hit_dmg;
            std::cerr << "praya to, no doctah: "
                << player_two->health << std::endl;
        }
    
        if ( (  player_two->fist_front_state == Player::FIST_STATE::DANGEROUS
             or player_two->fist_back_state  == Player::FIST_STATE::DANGEROUS ) )
        {
            player_one->health -= hit_dmg;
            std::cerr << "praya won, no doctah: "
                << player_one->health << std::endl;
        }
    }
    
    // win condition?
    if ( player_one->health <= 0 or player_two->health <= 0 )
    {
        game_over = true;
    }
    else if ( player_one->physics_object->pos.y < -0.95f )
    {
        player_one->health = 0;
        game_over = true;
    }
    else if ( player_two->physics_object->pos.y < -0.95f )
    {
        player_two->health = 0;
        game_over = true;
    }
    
    // powerup spawn:
    if ( SDL_GetTicks() > last_power_spawn + time_until_next_spawn )
    {
        std::cerr << "prease, hafe bowr of rice! very dericioush!" << std::endl;
        last_power_spawn = SDL_GetTicks();
        time_until_next_spawn = ( ( rand() % 3 ) + 3 ) * 1000;
        
        const float x_pos = static_cast<float>( ( ( rand() % 5 ) ) - 2 ) * 0.45f;
        const float y_pos = (static_cast<float>( rand() % 10 ) / 10 ) - 0.1f;
        
        Power_Up* new_power_up = new Power_Up( "./images/health_pickup.jpg",
              Vec2( 0.1f ),
              Vec2( x_pos, y_pos ) );

        
        power_ups.push_back( new_power_up );
        addGameObject( new_power_up );
    
    }

    // kill powerups:
    while ( power_ups.size() > 3 
        or ( SDL_GetTicks() > last_power_kill + 5000
                          and power_ups.size() > 0 ) )
    {
        last_power_kill = SDL_GetTicks();
        Power_Up* p_up = power_ups.front();
        power_ups.erase( power_ups.begin() );
        removeGameObject( p_up );
    }
    
    // pickup powerups:
    const float power_pick_dist    = 0.15f;
    const int   power_health_bonus = 10;
    for ( std::vector<Power_Up*>::iterator it = power_ups.begin();
            it != power_ups.end(); ++it )
    {
        bool picked_up = false;
        if ( player_one->physics_object->pos.getDistance(
                                (*it)->render_object->pos ) < power_pick_dist )
        {
            player_one->health += power_health_bonus;
            picked_up = true;
            std::cerr << "prayah won, eat veru hearthy rice! A prus: "
                << player_one->health << std::endl;
        }
        if ( player_two->physics_object->pos.getDistance(
                                (*it)->render_object->pos ) < power_pick_dist )
        {
            player_two->health += power_health_bonus;
            picked_up = true;
            std::cerr << "prayah to, eat veru hearthy rice! A prus: "
                << player_two->health << std::endl;
        }
        
        if ( picked_up )
        {
            Power_Up* p_up = *it;
            power_ups.erase( it );
            removeGameObject( p_up );
            --it;
            last_power_kill = SDL_GetTicks();
        }
    }
    
    // update health display
    p1_healthbar->setPercent( static_cast<float>( player_one->health ) / 100 );
    p2_healthbar->setPercent( static_cast<float>( player_two->health ) / 100 );
    
    // Update direction:
    player_one->look_right = player_one->physics_object->pos.x <
        player_two->physics_object->pos.x;
    
    player_two->look_right = player_two->physics_object->pos.x <
        player_one->physics_object->pos.x;
        
    player_one->update();
    player_two->update();
    
    
    return User_Target::TARGET_STATUS::CONTINUE;
}

Fighturu::Fighturu()
{
    std::cerr << "Fighturu begin!" << std::endl;

    background = new Decoration( "./images/tempwre.jpg",
                                    Vec2( 3.0f ), -20.0f );
    addGameObject( background );
    
    addGameObject( new Decoration( "./images/smoke_puff.png",
                                    Vec2( 4.5f ),  15.0f ) );
    //addGameObject( new Decoration( "./images/smoke_puff.png",
    //                                Vec2( 3.5f ), -10.0f ) );
    addGameObject( new Decoration( "./images/smoke_puff.png",
                                    Vec2( 4.0f ), -15.0f ) );
    
    addGameObject( new Platform( "./images/platform.png",
                                       Vec2( 0.0f, -0.8f ), Vec2( 1.1f, 0.7f ) ),
                                       Physics_Space::COLLIDER_TYPE::PLATFORM );

    addGameObject( new Platform( "./images/platform_wood.png",
                                       Vec2( 0.0f, -1.5f ), Vec2( 1.5f ) ),
                                       Physics_Space::COLLIDER_TYPE::PLATFORM );

    const Vec2 player_collision_size( 0.4f, 0.675f );
    
    player_one = new Player( "chan", Vec2( -0.5f, 0.1f ),
                                player_collision_size, true );
    
    player_two = new Player( "clint", Vec2(  0.5f, 0.1f ),
                                player_collision_size, false );
    
    
    addGameObject( player_one, Physics_Space::COLLIDER_TYPE::ACTOR );
    addGameObject( player_two, Physics_Space::COLLIDER_TYPE::ACTOR );
    
    render_space.parallax_mult /= 8;
    

    const std::string music_path = "./Audio/warrelicious.wav";
    /*File_SDL2_Music**/ music = nullptr;

    data.addFileRef( new File_SDL2_Music( music_path ) );
    File_Type* music_file = data.getFile( music_path );
    
    if ( music_file != nullptr )
    {
        music = dynamic_cast<File_SDL2_Music*>( music_file );
        music->play();
    }
    
    const std::string sound_path = "./Audio/yeha.wav";
    File_SDL2_Sound* sound = nullptr;

    data.addFileRef( new File_SDL2_Sound( sound_path ) );
    File_Type* sound_file = data.getFile( sound_path );
    
    if ( sound_file != nullptr )
    {
        sound = dynamic_cast<File_SDL2_Sound*>( sound_file );
        sound->play();
    }


    p1_healthbar = new Health_Display( player_one->name, true );
    p2_healthbar = new Health_Display( player_two->name, false );
    addGameObject( p1_healthbar );
    addGameObject( p2_healthbar );

}

Fighturu::~Fighturu()
{}

User_Target* Fighturu::getNewTarget()
{
    return nullptr;
}
