/******************************************************************************/
/*!
\file	Mesh_TerrainT.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "Mesh_TerrainT.h"

Mesh_MultiTexturedModel::Mesh_MultiTexturedModel(void)
{
    for(int i=0;i < MAX_TEXTURES; ++i)
    {
        textureID[i] = 0;
    }
    
}

Mesh_MultiTexturedModel::Mesh_MultiTexturedModel(unsigned int textureID, unsigned int texture2)
{
    this->textureID[0] = textureID;
    this->textureID[1] = texture2;
}

Mesh_MultiTexturedModel::~Mesh_MultiTexturedModel(void)
{

}

unsigned int Mesh_MultiTexturedModel::getTextureID(void)
{
    return textureID[0];
}

unsigned int Mesh_MultiTexturedModel::getTextureID2(void)
{
    return textureID[1];
}

void Mesh_MultiTexturedModel::setTextureID(unsigned int textureID, unsigned int texture2)
{
    this->textureID[0] = textureID;
    this->textureID[1] = texture2;
}