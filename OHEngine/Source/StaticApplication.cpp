/******************************************************************************/
/*!
\file	StaticApplication.cpp
\author Chuk Yih Jou
\brief
creating window and init opengl here, hardware abstraction input also done here
*/
/******************************************************************************/

#include "StaticApplication.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>

GLFWwindow* window;

double StaticApplication::scroll_y = 0;

static void Error_Callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

static void Resize_Callback(GLFWwindow* window, int w, int h)
{
	glViewport(0,0,w,h);
}


static void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
{
    StaticApplication::setScrollInfo(yoffset);
}

StaticApplication::StaticApplication(void)
{

}

StaticApplication::~StaticApplication(void)
{

}

void StaticApplication::InitGL(void)
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

void StaticApplication::DisableCursor(void)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void StaticApplication::MouseScrollUpdate(void)
{
    glfwSetScrollCallback(window, Scroll_Callback);
}

void StaticApplication::cleanGLFW(void)
{
    glfwTerminate();
}

int StaticApplication::closeGLFWwindow(void)
{
    return glfwWindowShouldClose(window);
}

void StaticApplication::CreateGLWindow(const int width, const int height, const char *title)
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

void StaticApplication::CreateFullScreenWindow(const int width, const int height, const char *title)
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

void StaticApplication::InitGLEW(void)
{
    glewExperimental = true; // Needed for core profile

    //Initialize GLEW
    GLenum err = glewInit();

    //If GLEW hasn't initialized
    if (err != GLEW_OK) 
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        //return -1;
    }
}

void StaticApplication::SwapBuffers(void)
{
    //Swap buffers
    glfwSwapBuffers(window);
}

void StaticApplication::PollEvents(void)
{
    //Get and organize events, like keyboard and mouse input, window resizing, etc...
    glfwPollEvents();
}

void StaticApplication::ReSizeGLScene(void)		// currently dunno how to use this yet
{
    glfwSetWindowSizeCallback(window, Resize_Callback);
}

void StaticApplication::KillGLWindow(void)
{
    glfwDestroyWindow(window);
}

bool StaticApplication::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

bool StaticApplication::IsMousePressed(unsigned short key)
{
    return glfwGetMouseButton(window, key) != 0;
}

double StaticApplication::getScrollInfo(void)
{
    return scroll_y;
}

void StaticApplication::setScrollInfo(double scroll)
{
    scroll_y = scroll;
}

void StaticApplication::getCursorPosition(double &mouse_x, double &mouse_y)
{
    glfwGetCursorPos(window, &mouse_x, &mouse_y);
}

void StaticApplication::setCursorPosition(double &mouse_x, double &mouse_y)
{
    glfwSetCursorPos(window, mouse_x, mouse_y);
}