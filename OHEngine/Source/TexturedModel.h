/******************************************************************************/
/*!
\file	TexturedModel.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include <fstream>

#include "Mesh_R.h"
#include "Mesh_T.h"

class TexturedModel
{
private:
    Mesh_RawModel r;
    Mesh_TexturedModel t;

public:
    TexturedModel(void);
    TexturedModel(Mesh_RawModel r, Mesh_TexturedModel t);
    ~TexturedModel(void);

    Mesh_RawModel getRawModel(void) const;
    Mesh_TexturedModel getTexturedModel(void) const;

    bool operator<(const TexturedModel that) const;
};

#endif 