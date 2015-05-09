/******************************************************************************/
/*!
\file	TextShader.h
\author Chuk Yih Jou
\brief
Class for calling specific shaders, init all te uniformLocation, load all the
info into shader (gluniform blah blah)
*/
/******************************************************************************/

#ifndef TEXT_SHADER_H
#define TEXT_SHADER_H

#include "ShaderProgram.h"

class TextShader : public ShaderProgram
{
  enum UNIFORM_TYPE
	{
		U_MVP = 0,
        U_MODELVIEW,                       
        U_MODELVIEW_INVERSE_TRANSPOSE,
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,
		U_TOTAL,
	};

private:
    unsigned int m_parameters[U_TOTAL];

protected:
    void getAllUniformLocations(void);  // get all the uniform location info into m_parameters[]

public:
    TextShader(void);
    ~TextShader(void);

    void load_MVP(Mtx44 &matrix);    // (normally during render) load the MVP matrix after getting the location in parameters
    void load_ColorTextureEnable(int i);
    void load_TextureColor(int i);
    void load_ModelView(Mtx44 &matrix);
    void load_ModelView_Inverse_Transpose(Mtx44 &matrix);

    void load_TextEnabled(bool enableText);
    void load_TextColor(Color color);

};

#endif