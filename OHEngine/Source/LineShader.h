/******************************************************************************/
/*!
\file	LineShader.h
\author Chuk Yih Jou
\brief
Class for calling specific shaders, init all te uniformLocation, load all the
info into shader (gluniform blah blah)
*/
/******************************************************************************/

#ifndef LINE_SHADER_H
#define LINE_SHADER_H

#include "ShaderProgram.h"

class LineShader : public ShaderProgram
{
    enum UNIFORM_TYPE
	{
        U_MVP = 0,
		U_TOTAL,
	};

private:
    unsigned int m_parameters[U_TOTAL];

protected:
    void getAllUniformLocations(void);  // get all the uniform location info into m_parameters[]

public:
    LineShader(void);
    ~LineShader(void);
    void load_MVP(Mtx44 &matrix);    // (normally during render) load the MVP matrix after getting the location in parameters
};

#endif