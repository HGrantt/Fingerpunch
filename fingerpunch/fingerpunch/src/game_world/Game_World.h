#ifndef _Game_World_h_
#define _Game_World_h_


#include "../input/User_Target.h"

#include "../graphics/Render_Space.h"
#include "../physics/Physics_Space.h"

#include "Game_Object.h"
#include "../graphics/Render_Object.h"
#include "../physics/Physics_Object.h"

#include <vector>

class Game_World : public User_Target
{
public:

    virtual Render_Space* getRenderSpace();
    std::vector<Render_Object*> const& getDrawOrder();
    virtual ~Game_World(){};
    
    void addGameObject( Game_Object* game_object,
                        Physics_Space::COLLIDER_TYPE c_type
                            = Physics_Space::COLLIDER_TYPE::NONE );
                            
    void removeGameObject( Game_Object* game_object );

    //virtual TARGET_STATUS update( Input_Manager* input_manager )=0;
    virtual User_Target*  getNewTarget(){ return nullptr; }
    
    void updatePositions( const float time_delta = 1.0f / 60.0f );
    
    void clear();

    std::vector<Game_Object*> game_objects;
    
    Render_Space  render_space;
    Physics_Space physics_space;

};

#endif /* defined(_Game_World_h_) */
