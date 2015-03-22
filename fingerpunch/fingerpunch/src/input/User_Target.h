#ifndef _User_Target_h_
#define _User_Target_h_
 
#include "Input_Manager.h"
#include "../graphics/Render_Space.h"

/**
 * Class where input and keys are handled
 */
class Input_Manager;

/**
 * Abstract class that handles in wich view the game is
 */
class User_Target
{
public:

  /**
   * TARGET_STATUS handles the games state
   */
    enum class TARGET_STATUS
    {
        CONTINUE,
        NEW_TARGET,
        GO_BACK,
        EXIT
    };

  /**
   * Destructor for User_Target
   */
    virtual ~User_Target(){}

  /**
   * Pure virtual function for updating the TARGET_STATUS
   * @param input_manager handles input from keyboard and mouse
   * @return current target status
   */
    virtual TARGET_STATUS update( Input_Manager* input_manager )=0;

  /**
   * If the return status is NEW_TARGET,
   * this function can be used to acquire the next target
   * @return nullptr will not be treated as a new target
   */
    virtual User_Target*  getNewTarget(){ return nullptr; }

  /**
   * Pure virtual function
   * @return the space that shall be drawn
   */
    virtual Render_Space* getRenderSpace()=0;

};

#endif /* defined(_User_Target_h_) */
