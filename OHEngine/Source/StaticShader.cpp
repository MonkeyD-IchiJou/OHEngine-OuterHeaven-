/******************************************************************************/
/*!
\file	StaticShader.cpp
\author Chuk Yih Jou
\brief
init all te uniformLocation, load all the info into shader (gluniform blah blah)
*/
/******************************************************************************/
#include <sstream>
#include "StaticShader.h"

StaticShaders::StaticShaders(void) : ShaderProgram("Shader//comg.vertexshader","Shader//comg.fragmentshader")
{
    getAllUniformLocations();
}

void StaticShaders::getAllUniformLocations(void)
{
    // model transformation into world space
    m_parameters[U_MVP] = getUniformLocation("MVP");
    

    // model surface and material 
    m_parameters[U_MODELVIEW] = getUniformLocation("MV");
    m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = getUniformLocation("MV_inverse_transpose");
    m_parameters[U_MATERIAL_AMBIENT] = getUniformLocation("material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = getUniformLocation("material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = getUniformLocation("material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = getUniformLocation("material.kShininess");

	m_parameters[U_LIGHTENABLED] = getUniformLocation("lightEnabled");

    // ligth type uniform 
    m_parameters[U_NUMLIGHTS] = getUniformLocation("numLights");

    m_parameters_U_LIGHT_TYPE[0] = getUniformLocation("lights[0].type");
    m_parameters_U_LIGHT_POSITION[0] = getUniformLocation("lights[0].position_cameraspace");
    m_parameters_U_LIGHT_COLOR[0] = getUniformLocation("lights[0].color");
    m_parameters_U_LIGHT_POWER[0] = getUniformLocation("lights[0].power");
    m_parameters_U_LIGHT_KC[0] = getUniformLocation("lights[0].kC");
    m_parameters_U_LIGHT_KL[0] = getUniformLocation("lights[0].kL");
    m_parameters_U_LIGHT_KQ[0] = getUniformLocation("lights[0].kQ");
    m_parameters_U_LIGHT_SPOTDIRECTION[0] = getUniformLocation("lights[0].spotDirection");
    m_parameters_U_LIGHT_COSCUTOFF[0] = getUniformLocation("lights[0].cosCutoff");
    m_parameters_U_LIGHT_COSINNER[0] = getUniformLocation("lights[0].cosInner");
    m_parameters_U_LIGHT_EXPONENT[0] = getUniformLocation("lights[0].exponent");

    m_parameters_U_LIGHT_TYPE[1] = getUniformLocation("lights[1].type");
    m_parameters_U_LIGHT_POSITION[1] = getUniformLocation("lights[1].position_cameraspace");
    m_parameters_U_LIGHT_COLOR[1] = getUniformLocation("lights[1].color");
    m_parameters_U_LIGHT_POWER[1] = getUniformLocation("lights[1].power");
    m_parameters_U_LIGHT_KC[1] = getUniformLocation("lights[1].kC");
    m_parameters_U_LIGHT_KL[1] = getUniformLocation("lights[1].kL");
    m_parameters_U_LIGHT_KQ[1] = getUniformLocation("lights[1].kQ");
    m_parameters_U_LIGHT_SPOTDIRECTION[1] = getUniformLocation("lights[1].spotDirection");
    m_parameters_U_LIGHT_COSCUTOFF[1] = getUniformLocation("lights[1].cosCutoff");
    m_parameters_U_LIGHT_COSINNER[1] = getUniformLocation("lights[1].cosInner");
    m_parameters_U_LIGHT_EXPONENT[1] = getUniformLocation("lights[1].exponent");


    m_parameters_U_LIGHT_TYPE[2] = getUniformLocation("lights[2].type");
    m_parameters_U_LIGHT_POSITION[2] = getUniformLocation("lights[2].position_cameraspace");
    m_parameters_U_LIGHT_COLOR[2] = getUniformLocation("lights[2].color");
    m_parameters_U_LIGHT_POWER[2] = getUniformLocation("lights[2].power");
    m_parameters_U_LIGHT_KC[2] = getUniformLocation("lights[2].kC");
    m_parameters_U_LIGHT_KL[2] = getUniformLocation("lights[2].kL");
    m_parameters_U_LIGHT_KQ[2] = getUniformLocation("lights[2].kQ");
    m_parameters_U_LIGHT_SPOTDIRECTION[2] = getUniformLocation("lights[2].spotDirection");
    m_parameters_U_LIGHT_COSCUTOFF[2] = getUniformLocation("lights[2].cosCutoff");
    m_parameters_U_LIGHT_COSINNER[2] = getUniformLocation("lights[2].cosInner");
    m_parameters_U_LIGHT_EXPONENT[2] = getUniformLocation("lights[2].exponent");

    m_parameters_U_LIGHT_TYPE[3] = getUniformLocation("lights[3].type");
    m_parameters_U_LIGHT_POSITION[3] = getUniformLocation("lights[3].position_cameraspace");
    m_parameters_U_LIGHT_COLOR[3] = getUniformLocation("lights[3].color");
    m_parameters_U_LIGHT_POWER[3] = getUniformLocation("lights[3].power");
    m_parameters_U_LIGHT_KC[3] = getUniformLocation("lights[3].kC");
    m_parameters_U_LIGHT_KL[3] = getUniformLocation("lights[3].kL");
    m_parameters_U_LIGHT_KQ[3] = getUniformLocation("lights[3].kQ");
    m_parameters_U_LIGHT_SPOTDIRECTION[3] = getUniformLocation("lights[3].spotDirection");
    m_parameters_U_LIGHT_COSCUTOFF[3] = getUniformLocation("lights[3].cosCutoff");
    m_parameters_U_LIGHT_COSINNER[3] = getUniformLocation("lights[3].cosInner");
    m_parameters_U_LIGHT_EXPONENT[3] = getUniformLocation("lights[3].exponent");


    m_parameters_U_LIGHT_TYPE[4] = getUniformLocation("lights[4].type");
    m_parameters_U_LIGHT_POSITION[4] = getUniformLocation("lights[4].position_cameraspace");
    m_parameters_U_LIGHT_COLOR[4] = getUniformLocation("lights[4].color");
    m_parameters_U_LIGHT_POWER[4] = getUniformLocation("lights[4].power");
    m_parameters_U_LIGHT_KC[4] = getUniformLocation("lights[4].kC");
    m_parameters_U_LIGHT_KL[4] = getUniformLocation("lights[4].kL");
    m_parameters_U_LIGHT_KQ[4] = getUniformLocation("lights[4].kQ");
    m_parameters_U_LIGHT_SPOTDIRECTION[4] = getUniformLocation("lights[4].spotDirection");
    m_parameters_U_LIGHT_COSCUTOFF[4] = getUniformLocation("lights[4].cosCutoff");
    m_parameters_U_LIGHT_COSINNER[4] = getUniformLocation("lights[4].cosInner");
    m_parameters_U_LIGHT_EXPONENT[4] = getUniformLocation("lights[4].exponent");


    m_parameters_U_LIGHT_TYPE[5] = getUniformLocation("lights[5].type");
    m_parameters_U_LIGHT_POSITION[5] = getUniformLocation("lights[5].position_cameraspace");
    m_parameters_U_LIGHT_COLOR[5] = getUniformLocation("lights[5].color");
    m_parameters_U_LIGHT_POWER[5] = getUniformLocation("lights[5].power");
    m_parameters_U_LIGHT_KC[5] = getUniformLocation("lights[5].kC");
    m_parameters_U_LIGHT_KL[5] = getUniformLocation("lights[5].kL");
    m_parameters_U_LIGHT_KQ[5] = getUniformLocation("lights[5].kQ");
    m_parameters_U_LIGHT_SPOTDIRECTION[5] = getUniformLocation("lights[5].spotDirection");
    m_parameters_U_LIGHT_COSCUTOFF[5] = getUniformLocation("lights[5].cosCutoff");
    m_parameters_U_LIGHT_COSINNER[5] = getUniformLocation("lights[5].cosInner");
    m_parameters_U_LIGHT_EXPONENT[5] = getUniformLocation("lights[5].exponent");


    m_parameters_U_LIGHT_TYPE[6] = getUniformLocation("lights[6].type");
    m_parameters_U_LIGHT_POSITION[6] = getUniformLocation("lights[6].position_cameraspace");
    m_parameters_U_LIGHT_COLOR[6] = getUniformLocation("lights[6].color");
    m_parameters_U_LIGHT_POWER[6] = getUniformLocation("lights[6].power");
    m_parameters_U_LIGHT_KC[6] = getUniformLocation("lights[6].kC");
    m_parameters_U_LIGHT_KL[6] = getUniformLocation("lights[6].kL");
    m_parameters_U_LIGHT_KQ[6] = getUniformLocation("lights[6].kQ");
    m_parameters_U_LIGHT_SPOTDIRECTION[6] = getUniformLocation("lights[6].spotDirection");
    m_parameters_U_LIGHT_COSCUTOFF[6] = getUniformLocation("lights[6].cosCutoff");
    m_parameters_U_LIGHT_COSINNER[6] = getUniformLocation("lights[6].cosInner");
    m_parameters_U_LIGHT_EXPONENT[6] = getUniformLocation("lights[6].exponent");

    m_parameters_U_LIGHT_TYPE[7] = getUniformLocation("lights[7].type");
    m_parameters_U_LIGHT_POSITION[7] = getUniformLocation("lights[7].position_cameraspace");
    m_parameters_U_LIGHT_COLOR[7] = getUniformLocation("lights[7].color");
    m_parameters_U_LIGHT_POWER[7] = getUniformLocation("lights[7].power");
    m_parameters_U_LIGHT_KC[7] = getUniformLocation("lights[7].kC");
    m_parameters_U_LIGHT_KL[7] = getUniformLocation("lights[7].kL");
    m_parameters_U_LIGHT_KQ[7] = getUniformLocation("lights[7].kQ");
    m_parameters_U_LIGHT_SPOTDIRECTION[7] = getUniformLocation("lights[7].spotDirection");
    m_parameters_U_LIGHT_COSCUTOFF[7] = getUniformLocation("lights[7].cosCutoff");
    m_parameters_U_LIGHT_COSINNER[7] = getUniformLocation("lights[7].cosInner");
    m_parameters_U_LIGHT_EXPONENT[7] = getUniformLocation("lights[7].exponent");

    // Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = getUniformLocation("colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = getUniformLocation("colorTexture");

    // Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = getUniformLocation("textEnabled");
	m_parameters[U_TEXT_COLOR] = getUniformLocation("textColor");
}

void StaticShaders::load_MVP(Mtx44 &matrix)
{
    loadU_Mat4f(m_parameters[U_MVP], matrix);
}

void StaticShaders::load_ModelView(Mtx44 &matrix)
{
    loadU_Mat4f(m_parameters[U_MODELVIEW], matrix);
}

void StaticShaders::load_LightEnabled(bool light)
{
    loadU_Bool(m_parameters[U_LIGHTENABLED], light);
}

void StaticShaders::load_ModelView_Inverse_Transpose(Mtx44 &matrix)
{
    loadU_Mat4f(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], matrix);
}

void StaticShaders::load_Material(Material &material)
{
    loadU_Vec3f(m_parameters[U_MATERIAL_AMBIENT], Vector3(material.getkAmbient().r, material.getkAmbient().g, material.getkAmbient().b));
    loadU_Vec3f(m_parameters[U_MATERIAL_DIFFUSE], Vector3(material.getkDiffuse().r, material.getkDiffuse().g, material.getkDiffuse().b));
    loadU_Vec3f(m_parameters[U_MATERIAL_SPECULAR], Vector3(material.getkSpecular().r, material.getkSpecular().g, material.getkSpecular().b));
    loadU_1f(m_parameters[U_MATERIAL_SHININESS], material.getkShininess());
}

void StaticShaders::load_ColorTextureEnable(int i)
{
    loadU_1i(m_parameters[U_COLOR_TEXTURE_ENABLED], i);
}

void StaticShaders::load_TextureColor(int i)
{
    loadU_1i(m_parameters[U_COLOR_TEXTURE], i);
}

void StaticShaders::load_Light(Light *light) 
{
    loadU_1i(m_parameters[U_NUMLIGHTS], MAX_LIGHT);         // current is only one light for testing
    for(int i = 0 ; i< MAX_LIGHT; i++)
    {
        loadU_1i( m_parameters_U_LIGHT_TYPE[i], light[i].getType());
        loadU_Vec3f(m_parameters_U_LIGHT_COLOR[i], Vector3(light[i].getColor().r, light[i].getColor().g, light[i].getColor().b));
        loadU_1f(m_parameters_U_LIGHT_POWER[i], light[i].getPower());
        loadU_1f(m_parameters_U_LIGHT_KC[i], light[i].getkC());
        loadU_1f(m_parameters_U_LIGHT_KL[i], light[i].getkL());
        loadU_1f(m_parameters_U_LIGHT_KQ[i], light[i].getkQ());
        loadU_1f(m_parameters_U_LIGHT_COSCUTOFF[i], light[i].getcosCutoff());
        loadU_1f(m_parameters_U_LIGHT_COSINNER[i], light[i].getcosInner());
        loadU_1f(m_parameters_U_LIGHT_EXPONENT[i], light[i].getExponent());
    }
}

void StaticShaders::load_LightDirection(Vector3 &dir, int i)
{
        loadU_Vec3f(m_parameters_U_LIGHT_POSITION[i], dir);
}

void StaticShaders::load_LightDirection(Position &dir, int i)
{
    loadU_Pos3f(m_parameters_U_LIGHT_POSITION[i], dir);
}

void StaticShaders::load_LightSpotDirection(Vector3 &dir, int i)
{
    loadU_Vec3f(m_parameters_U_LIGHT_SPOTDIRECTION[i], dir);
}

void StaticShaders::load_TextEnabled(bool enableText)
{
    loadU_Bool(m_parameters[U_TEXT_ENABLED], enableText);
}

void StaticShaders::load_TextColor(Color color)
{
    Vector3 v(color.r, color.g, color.b);
    loadU_Vec3f(m_parameters[U_TEXT_COLOR], v);
}

StaticShaders::~StaticShaders(void)
{

}