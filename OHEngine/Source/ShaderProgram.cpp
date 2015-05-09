/******************************************************************************/
/*!
\file	ShaderProgram.h
\author Chuk Yih Jou
\brief
applying methods to load shader file here
*/
/******************************************************************************/

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include "ShaderProgram.h"

GLint ShaderProgram::Result = GL_FALSE;
int ShaderProgram::InfoLogLength = 0;

ShaderProgram::ShaderProgram()
{
    ProgramID = VertexShaderID = FragmentShaderID = NULL;
}

ShaderProgram::ShaderProgram(const char * vertex_file_path, const char * fragment_file_path)
{
    VertexShaderID = LoadShader(vertex_file_path, GL_VERTEX_SHADER);
    FragmentShaderID = LoadShader(fragment_file_path, GL_FRAGMENT_SHADER);

    // Link the program
	printf("Linking program\n");
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);


    // validate the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

    // delete shader
    CleanUp();
}

GLuint ShaderProgram::LoadShader(const char * file_path, GLenum type)
{
    // Create the shaders
	GLuint ShaderID = glCreateShader(type);

	// Read the Vertex Shader code from the file
	std::string ShaderCode;
	std::ifstream ShaderStream(file_path, std::ios::in);

	if(ShaderStream.is_open()){
		std::string Line = "";
		while(getline(ShaderStream, Line))
			ShaderCode += "\n" + Line;
		ShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file_path);
		getchar();
		return 0;
	}

	// Compile Shader
	printf("Compiling shader : %s\n", file_path);
	char const * ShaderSourcePointer = ShaderCode.c_str();
	glShaderSource(ShaderID, 1, &ShaderSourcePointer , NULL);
	glCompileShader(ShaderID);

    // Check Shader
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}

    return ShaderID;
}

void ShaderProgram::Start(void)
{
    glUseProgram(ProgramID);
}

void ShaderProgram::Stop(void)
{
    glUseProgram(0);
}

void ShaderProgram::CleanUp(void)
{
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
}

unsigned int ShaderProgram::getUniformLocation(const char* uniformName)
{
    return glGetUniformLocation(ProgramID, uniformName);
}

void ShaderProgram::loadU_1f(unsigned int location, float value)
{
    glUniform1f(location, value);
}

void ShaderProgram::loadU_Vec3f(unsigned int location, Vector3 vec3f)
{
    glUniform3fv(location, 1, &vec3f.x);
}

void ShaderProgram::loadU_Pos3f(unsigned int location, Position pos) // glUniform3f
{
    glUniform3fv(location, 1, &pos.x);
}

void ShaderProgram::loadU_1i(unsigned int location, int value)
{
    glUniform1i(location, value);
}

void ShaderProgram::loadU_Bool(unsigned int location, bool value)
{
    int toLoad = 0;
    if (value)
    {
        toLoad = 1;
    }

    glUniform1i(location, value);
}

void ShaderProgram::loadU_Mat4f(unsigned int location, Mtx44 matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.a[0]);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(ProgramID);
}