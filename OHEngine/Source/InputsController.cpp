/******************************************************************************/
/*!
\file	InputsController.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "InputsController.h"

InputsController::InputsController(void)
{
    for(int i = 0; i < 256; i++)
    {
        myKeys[i] = false;
    }

    for(int i = 0; i < JERRY; i++)
    {
        myMouseKeys[i] = false;
    }
}

InputsController::~InputsController(void)
{
}

bool InputsController::getKeysInputs(const unsigned char key)
{
    bool tempBool = this->myKeys[key];
    myKeys[key] = false;
    return tempBool;
}

void InputsController::UpdateMyKeysStatus(const unsigned char key)
{
    myKeys[key] = true;
}

bool InputsController::getMouseInputs(const unsigned char key)
{
    bool tempBool = this->myMouseKeys[key];
    myMouseKeys[key] = false;
    return tempBool;
}

void InputsController::UpdateMyMouseKeyStatus(const unsigned char key)
{
    myMouseKeys[key] = true;
}

