/******************************************************************************/
/*!
\file	StaticShader.h
\author Chuk Yih Jou
\brief
Class for calling specific shaders, init all te uniformLocation, load all the
info into shader (gluniform blah blah)
*/
/******************************************************************************/

#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

#include "ShaderProgram.h"
#include "Light.h"
#include "Material.h"

class StaticShaders : public ShaderProgram
{
    enum UNIFORM_TYPE
	{
		U_MVP = 0,
        U_MODELVIEW,                       
        U_MODELVIEW_INVERSE_TRANSPOSE,
        U_MATERIAL_AMBIENT,
        U_MATERIAL_DIFFUSE,
        U_MATERIAL_SPECULAR,
        U_MATERIAL_SHININESS,
        U_LIGHTENABLED,
        U_NUMLIGHTS,
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,
		U_TOTAL,
	};

public:
    const static int MAX_LIGHT = 8;

private:
    
    unsigned int m_parameters[U_TOTAL];
    unsigned int m_parameters_U_LIGHT_TYPE[MAX_LIGHT];
    unsigned int m_parameters_U_LIGHT_POSITION[MAX_LIGHT];
    unsigned int m_parameters_U_LIGHT_COLOR[MAX_LIGHT];
    unsigned int m_parameters_U_LIGHT_POWER[MAX_LIGHT];
    unsigned int m_parameters_U_LIGHT_KC[MAX_LIGHT];
    unsigned int m_parameters_U_LIGHT_KL[MAX_LIGHT];
    unsigned int m_parameters_U_LIGHT_KQ[MAX_LIGHT];
    unsigned int m_parameters_U_LIGHT_SPOTDIRECTION[MAX_LIGHT];
    unsigned int m_parameters_U_LIGHT_COSCUTOFF[MAX_LIGHT];
    unsigned int m_parameters_U_LIGHT_COSINNER[MAX_LIGHT];
    unsigned int m_parameters_U_LIGHT_EXPONENT[MAX_LIGHT];

protected:
    void getAllUniformLocations(void);  // get all the uniform location info into m_parameters[]

public:
    StaticShaders(void);
    ~StaticShaders(void);

    void load_MVP(Mtx44 &matrix);    // (normally during render) load the MVP matrix after getting the location in parameters
    void load_ColorTextureEnable(int i);
    void load_TextureColor(int i);
    void load_Light(Light *light);
    void load_ModelView(Mtx44 &matrix);
    void load_LightEnabled(bool light);
    void load_LightDirection(Vector3 &dir, int i);
    void load_LightDirection(Position &dir, int i);
    void load_LightSpotDirection(Vector3 &dir, int i);
    void load_ModelView_Inverse_Transpose(Mtx44 &matrix);
    void load_Material(Material &material);

    void load_TextEnabled(bool enableText);
    void load_TextColor(Color color);
};


#endif