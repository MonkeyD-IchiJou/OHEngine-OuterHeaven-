///////////////////////////////////////////////////////////////////////////////
/*!
\file   MyApplication.h
\author Chuk Yih Jou
\brief
Header file for glfw functions .. Inputs hardware abstraction
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef MY_APPLICATION_H
#define MY_APPLICATION_H

#include <windows.h>

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


/******************************************************************************/
/*!
\brief
Application namespace
*/
/******************************************************************************/

namespace Application
{
    static GLFWwindow* window;
    static double scroll_y = 0;

    static void Resize_Callback(GLFWwindow* window, GLint w, GLint h)
    {
        glViewport(0,0,w,h);
    }

    static void Error_Callback(int error, const char* description)
    {
        fputs(description, stderr);
        _fgetchar();
    }

    inline void InitGLFW(void)
    {
        //Set the error callback
        glfwSetErrorCallback(Error_Callback);

        //Initialize GLFW
        if (!glfwInit())
        {
            exit(EXIT_FAILURE);
        }

        //Set the GLFW window creation hints - these are optional
        glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
    }

    inline void DisableCursor(void)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
    inline double getScrollInfo(void)
    {
        return scroll_y;
    }

    inline void setScrollInfo(double scroll)
    {
        scroll_y = scroll;
    }

    inline static void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        setScrollInfo(yoffset);
    }

    inline void MouseScrollUpdate(void)
    {
        glfwSetScrollCallback(window, Scroll_Callback);
    }

    inline void cleanGLFW(void)
    {
        glfwTerminate();
    }

    inline int closeGLFWwindow(void)
    {
        return glfwWindowShouldClose(window);
    }

    inline void CreateGLWindow(const int width, const int height, const char *title)
    {
        window = glfwCreateWindow(width, height, title, NULL, NULL);

        //If the window couldn't be created
        if (!window)
        {
            fprintf(stderr, "Failed to open GLFW window.\n" );
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        //This function makes the context of the specified window current on the calling thread. 
        glfwMakeContextCurrent(window);
    }

    inline void CreateFullScreenWindow(const int width, const int height, const char *title)
    {
        window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);

        //If the window couldn't be created
        if (!window)
        {
            fprintf(stderr, "Failed to open GLFW window.\n" );
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        //This function makes the context of the specified window current on the calling thread. 
        glfwMakeContextCurrent(window);
    }

    inline void SwapBuffers(void)
    {
        //Swap buffers
        glfwSwapBuffers(window);
    }

    inline void PollEvents(void)
    {
        //Get and organize events, like keyboard and mouse input, window resizing, etc...
        glfwPollEvents();
    }

    inline void ReSizeGLScene(void)		// currently dunno how to use this yet
    {
        glfwSetWindowSizeCallback(window, Resize_Callback);
    }

    inline void KillGLWindow(void)
    {
        glfwDestroyWindow(window);
    }

    inline bool IsKeyPressed(unsigned short key)
    {
        return ((GetAsyncKeyState(key) & 0x8001) != 0);
    }

    inline bool IsMousePressed(unsigned short key)
    {
        return glfwGetMouseButton(window, key) != 0;
    }

    inline void getCursorPosition(double &mouse_x, double &mouse_y)
    {
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
    }

    inline void setCursorPosition(double &mouse_x, double &mouse_y)
    {
        glfwSetCursorPos(window, mouse_x, mouse_y);
    }
}//end namespace Application


#endif      // MY_APPLICATION_H