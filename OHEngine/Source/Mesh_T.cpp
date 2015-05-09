/******************************************************************************/
/*!
\file	Mesh_T.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "Mesh_T.h"

Mesh_TexturedModel::Mesh_TexturedModel(void)
{
    textureID = 0;
}

Mesh_TexturedModel::Mesh_TexturedModel(unsigned int textureID)
{
    this->textureID = textureID;
}

Mesh_TexturedModel::~Mesh_TexturedModel(void)
{

}

unsigned int Mesh_TexturedModel::getTextureID(void)
{
    return textureID;
}

void Mesh_TexturedModel::setTextureID(unsigned int textureID)
{
    this->textureID = textureID;
}