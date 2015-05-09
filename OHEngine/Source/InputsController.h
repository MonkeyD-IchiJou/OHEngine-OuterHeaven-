/******************************************************************************/
/*!
\file	InputsController.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef INPUTSCONTROLLER_H
#define INPUTSCONTROLLER_H



class InputsController
{
public:
    enum MouseInput
    {
        LEFT_CLICK = 0,
        RIGHT_CLICK,
        MIDDLE_CLICK,
        SCROLL_UP,
        SCROLL_DOWN,
        JERRY,                  // Tom and Jerry
    };

private:
    bool myKeys[256];
    bool myMouseKeys[JERRY];

public:

    InputsController(void);
    ~InputsController(void);

    bool getKeysInputs(const unsigned char key);        // automatically switch it off, hardware abstraction
    void UpdateMyKeysStatus(const unsigned char key);

    bool getMouseInputs(const unsigned char key);       // automatically switch it off, hardware abstraction
    void UpdateMyMouseKeyStatus(const unsigned char key);
};

#endif

