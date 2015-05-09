/******************************************************************************/
/*!
\file	StaticApplication.h
\author Chuk Yih Jou
\brief
creating window and init opengl here, hardware abstraction input also done here
*/
/******************************************************************************/

#ifndef STATIC_APPLICATION_H
#define STATIC_APPLICATION_H

class StaticApplication
{
private:
    static double scroll_y;

public:
    StaticApplication(void);
    ~StaticApplication(void);

    void InitGL(void);
    void InitGLEW(void);

    void CreateGLWindow(const int width, const int height, const char *title);
    void CreateFullScreenWindow(const int width, const int height, const char *title);
    void ReSizeGLScene(void);		// Resize And Initialize The GL Window
	void KillGLWindow(void);

    static bool IsKeyPressed(unsigned short key);
    static bool IsMousePressed(unsigned short key);

    void getCursorPosition(double &mouse_x, double &mouse_y);
    void setCursorPosition(double &mouse_x, double &mouse_y);

    void DisableCursor(void);
    void MouseScrollUpdate(void);

    int closeGLFWwindow(void);
    void cleanGLFW(void);

    //Swap buffers
    void SwapBuffers();
    //Get and organize events, like keyboard and mouse input, window resizing, etc...
    void PollEvents();

    static double getScrollInfo(void);
    static void setScrollInfo(double scroll);
};

#endif