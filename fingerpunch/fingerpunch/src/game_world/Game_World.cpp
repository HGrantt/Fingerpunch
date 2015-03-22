#include "Game_World.h"

#include <iostream>

void Game_World::addGameObject( Game_Object* game_object,
                                Physics_Space::COLLIDER_TYPE c_type  )
{
    render_space.add( game_object->render_object );
    
    physics_space.add( game_object->physics_object, c_type );
    
    game_objects.push_back( game_object );
    
    render_space.updateDrawOrder();
}

Render_Space* Game_World::getRenderSpace()
{
    return &render_space;
}

std::vector<Render_Object*> const& Game_World::getDrawOrder()
{
    return render_space.getDrawOrder();
}

void Game_World::updatePositions( const float time_delta )
{
    physics_space.update( time_delta );
    
    for ( Game_Object* game_object : game_objects )
    {
        if ( game_object->physics_object != nullptr
                and game_object->render_object != nullptr )
        {
            game_object->render_object->pos
                = game_object->physics_object->collision_box.pos;
        }
    }
}

void Game_World::removeGameObject( Game_Object* game_object )
{
    for ( std::vector<Game_Object*>::iterator it = game_objects.begin();
              it != game_objects.end(); ++it )
    {
        if ( *it == game_object )
        {
            render_space.remove( (*it)->render_object );
            physics_space.remove( (*it)->physics_object );
            
            delete *it;
            game_objects.erase( it );
            
            render_space.updateDrawOrder();
            
            return;
        }
    }
}

void Game_World::clear()
{
    for ( Game_Object* g_obj : game_objects )
    {
        delete g_obj->render_object;
        delete g_obj->physics_object;
        delete g_obj;
    }
}