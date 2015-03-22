#include "Render_Space.h"
#include <algorithm>

std::vector<Render_Object*> const& Render_Space::getDrawOrder() const
{
    return render_objects;
}

void Render_Space::updateDrawOrder()
{
    auto compare_dereferenced
        = []( Render_Object* a, Render_Object* b )->bool { return *a < *b; };
        
    std::sort( render_objects.begin(), render_objects.end(), compare_dereferenced );
}

void Render_Space::add( Render_Object* render_object )
{
    render_objects.push_back( render_object );
}

void Render_Space::remove( Render_Object* render_object )
{
    for ( std::vector<Render_Object*>::iterator it = render_objects.begin();
            it != render_objects.end(); ++it )
    {
        if ( *it == render_object )
        {
            render_objects.erase( it );
            return;
        }
    }
}