#ifndef _Renderer_h_
#define _Renderer_h_
 
#include "../file/Loader.h"
#include "Render_Space.h"

class Renderer
{
public:

    virtual ~Renderer(){};
    
    virtual void draw( Render_Space* render_space ) = 0;

    int window_width { 1920 };
    int window_height{ 1200 };

};

#endif /* defined(_Renderer_h_) */
