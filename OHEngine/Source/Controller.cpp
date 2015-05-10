/******************************************************************************/
/*!
\file	Controller.cpp
\author Chuk Yih Jou
\brief
Receive model and view, Main run loop is here, checking inputs and update 
input status
*/
/******************************************************************************/

#include "MyApplication.h"
#include "MyGL.h"
#include "Controller.h"

const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000/FPS; // time for each frame

double Controller::mouse_last_x = 0.0, Controller::mouse_last_y = 0.0,
 Controller::mouse_current_x = 0.0, Controller::mouse_current_y = 0.0,
 Controller::mouse_diff_x = 0.0, Controller::mouse_diff_y = 0.0;
double Controller::camera_yaw = 0.0, Controller::camera_pitch = 0.0;

Controller::Controller(void)
{

}

Controller::Controller(Model *theModel, View *theView) : theModel(NULL), theView(NULL)
{
    this->theModel = theModel;
    this->theView = theView;
}

bool Controller::GetKeyBoardUpdate(void)
{
    if(Application::IsKeyPressed('A'))
    {
        theModel->UpdateCameraStatus('a');
        theModel->UpdatePlayerStatus('a');
    }

    if(Application::IsKeyPressed('D'))
    {
        theModel->UpdateCameraStatus('d');
        theModel->UpdatePlayerStatus('d');
    }

    if(Application::IsKeyPressed('W'))
    {
        theModel->UpdateCameraStatus('w');
        theModel->UpdatePlayerStatus('w');
    }

    if(Application::IsKeyPressed('S'))
    {
        theModel->UpdateCameraStatus('s');
        theModel->UpdatePlayerStatus('s');
    }

    if(Application::IsKeyPressed(VK_SPACE))
    {
        theModel->UpdatePlayerStatus(' ');
    }

    if(Application::IsKeyPressed('Z'))
    {
        theModel->UpdateCameraStatus('z');
    }

    if(Application::IsKeyPressed('X'))
    {
        theModel->UpdateCameraStatus('x');
    }

    if (Application::IsKeyPressed('1'))
    {
        theModel->UpdateGLStatus('1');
    }

    if(Application::IsKeyPressed('2'))
    {
        theModel->UpdateGLStatus('2');
    }

    if(Application::IsKeyPressed(VK_ESCAPE))
    {
        inputs.UpdateMyKeysStatus(VK_ESCAPE);
    }
    return true;
}

bool Controller::GetMouseUpdate(void)
{
    Application::getCursorPosition(mouse_current_x, mouse_current_y);

    //// Calculate the difference in positions
    mouse_diff_x = mouse_current_x - mouse_last_x;
    mouse_diff_y = mouse_current_y - mouse_last_y;

    //Calculate the yaw and pitch
    camera_yaw = (float) mouse_diff_x * 0.0174555555555556f;// * 3.142f / 180.0f;
    camera_pitch = mouse_diff_y * 0.0174555555555556f;// 3.142f / 180.0f );

    // Do a wraparound if the mouse cursor has gone out of the deadzone
    if ((mouse_current_x < m_window_deadzone) || (mouse_current_x > m_window_width - m_window_deadzone))
    {
        mouse_current_x = m_window_width >> 1;
        Application::setCursorPosition(mouse_current_x, mouse_current_y);
    }
    if ((mouse_current_y < m_window_deadzone) || (mouse_current_y > m_window_height - m_window_deadzone))
    {
        mouse_current_y = m_window_height >> 1;
        Application::setCursorPosition(mouse_current_x, mouse_current_y);
    }

    // Store the current position as the last position
    mouse_last_x = mouse_current_x;
    mouse_last_y = mouse_current_y;

    if (Application::IsMousePressed(0))
    {
        theModel->UpdateMouseCameraStatus(InputsController::LEFT_CLICK);
        theModel->UpdateWeaponStatus(theModel->WA_FIRE);
    }

    if(Application::IsMousePressed(1))
    {
        theModel->UpdateMouseCameraStatus(InputsController::RIGHT_CLICK);
    }

    if(Application::IsMousePressed(2))
    {
        theModel->UpdateMouseCameraStatus(InputsController::MIDDLE_CLICK);
    }

    // scrolling
    if(Application::getScrollInfo() > 0)
    {
        theModel->UpdateMouseCameraStatus(InputsController::SCROLL_UP);
        Application::setScrollInfo(0);
    }

    if(Application::getScrollInfo() < 0)
    {
        theModel->UpdateMouseCameraStatus(InputsController::SCROLL_DOWN);
        Application::setScrollInfo(0);
    }

    return false;
}

void Controller::ControllerInit(void)
{
    m_dElapsedTime = 0;
    m_dAccumulatedTime = 0;

    Application::InitGLFW();
    Application::CreateGLWindow(m_window_width, m_window_height, "Testing 1");
    Application::ReSizeGLScene(); 
    GL::InitGLEW();
    Application::DisableCursor();
    Application::MouseScrollUpdate();
}

void Controller::RunMainLoop(void)
{
    ControllerInit();
    theModel->InitModel();
    theView->InitRenderer();

    m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame

    while (!Application::closeGLFWwindow() && !inputs.getKeysInputs(VK_ESCAPE))
	{
        m_dElapsedTime = m_timer.getElapsedTime();
        m_dAccumulatedTime += m_dElapsedTime;

        GetKeyBoardUpdate();
        GetMouseUpdate();

        if(m_dAccumulatedTime > 0.01)
        {
            theModel->Update(m_dElapsedTime);
            m_dAccumulatedTime = 0.0;
        }
        
        theView->Draw();

        Application::SwapBuffers();          //Swap buffers
        Application::PollEvents();           //Get and organize events, like keyboard and mouse input, window resizing, etc...

        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   
    } //Check if the ESC key had been pressed or if the window had been closed
}

Controller::~Controller(void)
{
    Application::KillGLWindow();
    Application::cleanGLFW();

    this->theModel = NULL;
    this->theView = NULL;
}