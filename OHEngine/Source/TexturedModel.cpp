/******************************************************************************/
/*!
\file	TexturedModel.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "TexturedModel.h"

TexturedModel::TexturedModel(void)
{

}

TexturedModel::TexturedModel(Mesh_RawModel r, Mesh_TexturedModel t)
{
    this->r = r;
    this->t = t;
}

TexturedModel::~TexturedModel(void)
{   

}

Mesh_RawModel TexturedModel::getRawModel(void) const
{
    return r;
}

Mesh_TexturedModel TexturedModel::getTexturedModel(void) const
{
    return t;
}

bool TexturedModel::operator<(const TexturedModel that) const
{
    return memcmp((void*)this, (void*)&that, sizeof(TexturedModel))>0;
}