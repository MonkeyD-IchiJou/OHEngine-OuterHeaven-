/******************************************************************************/
/*!
\file	TextShader.cpp
\author Chuk Yih Jou
\brief
init all te uniformLocation, load all the info into shader (gluniform blah blah)
*/
/******************************************************************************/
#include <sstream>
#include "TextShader.h"

TextShader::TextShader(void) : ShaderProgram("Shader//comg.vertexshader","Shader//Text.fragmentshader")
{
    getAllUniformLocations();
}

void TextShader::getAllUniformLocations(void)
{
    // model transformation into world space
    m_parameters[U_MVP] = getUniformLocation("MVP");

    // model surface and material 
    m_parameters[U_MODELVIEW] = getUniformLocation("MV");
    m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = getUniformLocation("MV_inverse_transpose");

    // Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = getUniformLocation("colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = getUniformLocation("colorTexture");

    // Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = getUniformLocation("textEnabled");
	m_parameters[U_TEXT_COLOR] = getUniformLocation("textColor");
}

void TextShader::load_MVP(Mtx44 &matrix)
{
    loadU_Mat4f(m_parameters[U_MVP], matrix);
}

void TextShader::load_ModelView(Mtx44 &matrix)
{
    loadU_Mat4f(m_parameters[U_MODELVIEW], matrix);
}

void TextShader::load_ModelView_Inverse_Transpose(Mtx44 &matrix)
{
    loadU_Mat4f(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], matrix);
}

void TextShader::load_ColorTextureEnable(int i)
{
    loadU_1i(m_parameters[U_COLOR_TEXTURE_ENABLED], i);
}

void TextShader::load_TextureColor(int i)
{
    loadU_1i(m_parameters[U_COLOR_TEXTURE], i);
}

void TextShader::load_TextEnabled(bool enableText)
{
    loadU_Bool(m_parameters[U_TEXT_ENABLED], enableText);
}

void TextShader::load_TextColor(Color color)
{
    Vector3 v(color.r, color.g, color.b);
    loadU_Vec3f(m_parameters[U_TEXT_COLOR], v);
}

TextShader::~TextShader(void)
{

}