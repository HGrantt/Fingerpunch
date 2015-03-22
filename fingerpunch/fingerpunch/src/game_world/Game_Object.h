#ifndef _Game_Object_h_
#define _Game_Object_h_

#include "../graphics/Render_Object.h"
#include "../physics/Physics_Object.h"

class Game_Object
{
public:

    Game_Object( Render_Object*  render_object  = nullptr,
                 Physics_Object* physics_object = nullptr );

    virtual ~Game_Object();

    virtual void update()=0;

    Render_Object*  render_object;
    Physics_Object* physics_object;

};

#endif /* defined(_Game_Object_h_) */
