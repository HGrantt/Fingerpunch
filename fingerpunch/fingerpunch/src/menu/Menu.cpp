#include "Menu.h"

#include <iostream>

void Menu::addElement( Vec2 const&        pos,
                       Vec2 const&        size,
                       std::string const& image_path )
{
    Sprite image( image_path, pos, size );
    Menu_Element* menu_element = new Menu_Element( image );

    render_space.add( menu_element );
    menu_elements.push_back( menu_element );
    
    render_space.updateDrawOrder();
}

void Menu::addDecoration( Vec2 const&        pos,
                          Vec2 const&        size,
                          const float        z_pos,
                          std::string const& image_path )
{
    Sprite image( image_path, pos, size );
    
    Render_Object* decoration
        = new Render_Object( Vec2( 0.0f, 0.0f ), 1.0f, z_pos );

    decoration->sprite_draw_order.push_back( new Sprite( image ) );

    render_space.add( decoration );
    decorations.push_back( decoration );

    render_space.updateDrawOrder();
}

Menu_Element* Menu::getActiveElement( Vec2 const& point )
{
    for ( std::vector<Menu_Element*>::iterator it = menu_elements.begin();
          it != menu_elements.end(); ++it )
    {
        if ( (*it)->contains( point ) )
        {
            return *it;
        }
    }
    return nullptr;
}

Render_Space* Menu::getRenderSpace()
{
    return &render_space;
}

Menu::Menu()
{}

Menu::~Menu()
{
    for ( Menu_Element*& menu_element : menu_elements )
    {
        delete menu_element;
        menu_element = nullptr;
    }
    
    for ( Render_Object* r_obj : decorations )
    {
        for ( Sprite* sprite : r_obj->sprite_draw_order )
        {
            delete sprite;
        }
        delete r_obj;
    }
}
