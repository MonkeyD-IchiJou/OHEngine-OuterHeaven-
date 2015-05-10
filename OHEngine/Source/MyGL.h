///////////////////////////////////////////////////////////////////////////////
/*!
\file   MyGL.h
\author Chuk Yih Jou
\brief
Header file for opengl functions
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef MY_GL_H
#define MY_GL_H

//Include GLEW
#include <GL/glew.h>

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

namespace GL
{
    inline void ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {
        // Set background color to dark blue
        glClearColor(r, g, b, a);
    }

    inline void DepthFunc(GLint GL)
    {
	    glDepthFunc(GL); 
    }

    inline void Enable(GLint GL)
    {
	    glEnable(GL);
    }
    
    inline void PolygonMode(GLint GL, GLint GLs)
    {
        glPolygonMode(GL, GLs);
    }
	
    inline void BlendFunc(GLint GL, GLint GLs)
    {
        glBlendFunc(GL, GLs);
    }
	
    inline void Clear(GLint GL, GLint GLs)
    {
        glClear(GL | GLs);
    }

    inline void AttachShader(GLuint pID, GLuint vID)
    {
        glAttachShader(pID, vID);
    }
    
    inline void LinkProgram(GLuint pID)
    {
        glLinkProgram(pID);
    }

    inline unsigned int CreateProgram(void)
    {
        return glCreateProgram();
    }

    inline void GetProgramiv(GLuint pID, GLint GL, GLint* I)
    {
        glGetProgramiv(pID, GL, I);
    }

    inline GLuint CreateShader(GLenum type)
    {
        return glCreateShader(type);
    }

    inline void CompileShader(GLuint ShaderID)
    {
        glCompileShader(ShaderID);
    }

    inline void UseProgram(GLuint ProgramID)
    {
        glUseProgram(ProgramID);
    }

    inline void DetachShader(GLuint ProgramID, GLuint vID)
    {
        glDetachShader(ProgramID, vID);
    }

    inline void DeleteShader(GLuint ID)
    {
        glDeleteShader(ID);
    }

    inline void DeleteProgram(GLuint pID)
    {
        glDeleteProgram(pID);
    }

    inline void BindVertexArray(GLuint vaoID)
    {
        glBindVertexArray(vaoID);
    }

    inline void EnableVertexAttribArray(GLuint n)
    {
        glEnableVertexAttribArray(n); // 1st attribute buffer : vertices
    }

    inline void DisableVertexAttribArray(GLuint n)
    {
         glDisableVertexAttribArray(n);
    }

    inline void BindTexture(GLenum target, GLuint texture)
    {
        glBindTexture(target, texture);
    }

    inline void ActiveTexture(GLenum texture)
    {
        glActiveTexture(texture);
    }
   
    inline void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
    {
        glDrawElements(mode, count, type, indices);
    }

    inline void InitGLEW(void)
    {
        glewExperimental = true; // Needed for core profile

        //Initialize GLEW
        GLenum err = glewInit();

        //If GLEW hasn't initialized
        if (err != GLEW_OK) 
        {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        }
    }
}

#endif 