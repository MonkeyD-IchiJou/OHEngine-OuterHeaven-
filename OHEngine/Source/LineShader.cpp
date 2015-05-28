#include "LineShader.h"

LineShader::LineShader(void) : ShaderProgram("Shader//SimpleVertexShader.vertexshader","Shader//SimpleFragmentShader.fragmentshader")
{
    getAllUniformLocations();
}

LineShader::~LineShader(void)
{

}

void LineShader::getAllUniformLocations(void)
{
    // model transformation into world space
    m_parameters[U_MVP] = getUniformLocation("MVP");
}

void LineShader::load_MVP(Mtx44 &matrix)
{
    loadU_Mat4f(m_parameters[U_MVP], matrix);
}

