/******************************************************************************/
/*!
\file	ShaderProgram.h
\author Chuk Yih Jou
\brief
Class for Opening shader file and load it into the shader program
*/
/******************************************************************************/

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H


#include "Vector3.h"
#include "Mtx44.h"
#include "Utility.h"

class ShaderProgram
{
private:
    unsigned int ProgramID, VertexShaderID, FragmentShaderID;
    static unsigned int LoadShader(const char * file_path, unsigned int type);

    static int Result; 
    static int InfoLogLength;    // variable used to validate program

protected:
    unsigned int getUniformLocation(const char* uniformName);
    virtual void getAllUniformLocations(void) = 0;

    void loadU_1f(unsigned int location, float value);  // glUniform1f
    void loadU_Vec3f(unsigned int location, Vector3 vec3f); // glUniform3f
    void loadU_Pos3f(unsigned int location, Position pos); // glUniform3f
    void loadU_1i(unsigned int location, int value);    // glUniform1i
    void loadU_Bool(unsigned int location, bool value);
    void loadU_Mat4f(unsigned int location, Mtx44 matrix);  //glUniformMatrix4fv

public:
    ShaderProgram();        // constructor
    ShaderProgram(const char * vertex_file_path, const char * fragment_file_path);
    ~ShaderProgram();

    void Start(void);       // start shader
    void Stop(void);        // stop shader
    void CleanUp(void);     // delete shader to save memory space after link program
};
#endif