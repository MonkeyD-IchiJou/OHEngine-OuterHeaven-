/******************************************************************************/
/*!
\file	Controller.h
\author Chuk Yih Jou
\brief
Contains model and view, Main run loop is here, checking inputs and update 
input status, create main window ...
*/
/******************************************************************************/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "timer.h"
#include "View.h"
#include "InputsController.h"

class Controller
{
private:
	StopWatch m_timer;
    double m_dElapsedTime;
    double m_dAccumulatedTime;

    Model* theModel;
    View* theView;

    const static int m_window_width = 640;
    const static int m_window_height = 480;
    const static int m_window_deadzone = 100;

    InputsController inputs;

    bool GetKeyBoardUpdate(void);
    bool GetMouseUpdate(void);

public:
    Controller(void);
    Controller(Model *theModel, View *theView);
    ~Controller(void);

    static Controller& GetInstance()
	{
		static Controller app;
		return app;
	}

    void ControllerInit(void);
    void RunMainLoop(void);

    //Declare variables to store the last and current mouse position
    static double mouse_last_x, mouse_last_y, mouse_current_x,
        mouse_current_y, mouse_diff_x, mouse_diff_y;
    static double camera_yaw, camera_pitch;
};

#endif 
