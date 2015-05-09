/******************************************************************************/
/*!
\file	SkyboxShader.h
\author Chuk Yih Jou
\brief
Class for calling specific shaders, init all te uniformLocation, load all the
info into shader (gluniform blah blah)
*/
/******************************************************************************/

#ifndef SKYBOX_SHADER_H
#define SKYBOX_SHADER_H

#include "ShaderProgram.h"

class SkyboxShaders : public ShaderProgram
{
    enum UNIFORM_TYPE
	{
        U_VP,
		U_TOTAL,
	};

private:
    unsigned int m_parameters[U_TOTAL];

protected:
    void getAllUniformLocations(void);  // get all the uniform location info into m_parameters[]

public:
    SkyboxShaders(void);
    ~SkyboxShaders(void);
    void load_ViewProjection(Mtx44 &matrix);
};

#endif