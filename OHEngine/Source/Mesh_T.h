/******************************************************************************/
/*!
\file	Mesh_T.h
\author Chuk Yih Jou
\brief
main class to store textureID
*/
/******************************************************************************/

#ifndef MESH_T 
#define MESH_T

class Mesh_TexturedModel
{
private:
    unsigned int textureID;

public:
    Mesh_TexturedModel(void);
    Mesh_TexturedModel(unsigned int textureID);
    ~Mesh_TexturedModel(void);

    void setTextureID(unsigned int textureID);
    unsigned int getTextureID(void);
};

#endif