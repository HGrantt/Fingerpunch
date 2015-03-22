#ifndef _Menu_h_
#define _Menu_h_

#include "../input/User_Target.h"

 #include "../graphics/Render_Space.h"
#include "../graphics/Render_Object.h"
#include "../graphics/Sprite.h"

#include "Menu_Element.h"

#include "../math/Vec2.h"

#include <vector>

/**
 * Class for a menu with elements, inherits from User_Target
 */
class Menu : public User_Target
{
public:

    //virtual TARGET_STATUS update( Input_Manager* input_manager )=0;

   /**
    * from User_Target
    * @return the space that shall be drawn
    */
    virtual Render_Space* getRenderSpace();

    /// Constructor
    Menu();

  /**
   * Destructor for Menu
   * deletes all Menu_Elements, Sprites and Render_Objects
   */
    virtual ~Menu();

  /**
   * Adds element for the menu in menu_elements and render_space
   * @param pos position of the element
   * @param size size of the element
   * @param image_path where you can find the image
   */
    void addElement( Vec2 const&        pos,
                     Vec2 const&        size,
                     std::string const& image_path );

  /**
   * Adds decoration for the menu in decorations and render_space
   * @param pos position of the decoration
   * @param size size of the decoration
   * @param z_pos position for paralax effect
   * @param image_path where you can find the image
   */
    void addDecoration( Vec2 const&        pos,
                        Vec2 const&        size,
                        const float        z_pos,
                        std::string const& image_path );

  /**
   * Aktivates the element the mouse clicks on
   * @param point the mouse position when clicked
   * @return the correct element or nullptr
   */
    Menu_Element* getActiveElement( Vec2 const& point );
    
protected:

    /// the position and space where something will be drawn
    Render_Space render_space;

    /// vector holding decorations
    std::vector<Render_Object*> decorations;

    /// vector holding menu elements
    std::vector<Menu_Element*>  menu_elements;

};

#endif /* defined(_Menu_h_) */
