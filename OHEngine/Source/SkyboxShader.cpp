#include "SkyboxShader.h"

SkyboxShaders::SkyboxShaders(void) : ShaderProgram("Shader//Skybox.vertexshader","Shader//Skybox.fragmentshader")
{
    getAllUniformLocations();
}

SkyboxShaders::~SkyboxShaders(void)
{

}

void SkyboxShaders::getAllUniformLocations(void)
{
    m_parameters[U_VP] = getUniformLocation("VP");
}

void SkyboxShaders::load_ViewProjection(Mtx44 &matrix)
{
    loadU_Mat4f(m_parameters[U_VP], matrix);
}

