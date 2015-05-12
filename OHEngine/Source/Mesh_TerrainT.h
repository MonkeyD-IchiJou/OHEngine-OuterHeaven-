/******************************************************************************/
/*!
\file	Mesh_TerainT.h
\author Chuk Yih Jou
\brief
main class to store textureIDs, multi textures allowed for terrain
*/
/******************************************************************************/

#ifndef MESH_TERRAINT_H
#define MESH_TERRAINT_H

class Mesh_MultiTexturedModel
{
private:
    static const int MAX_TEXTURES = 2;
    unsigned int textureID[MAX_TEXTURES];

public:
    Mesh_MultiTexturedModel(void);
    Mesh_MultiTexturedModel(unsigned int textureID, unsigned int texture2);
    ~Mesh_MultiTexturedModel(void);

    void setTextureID(unsigned int textureID, unsigned int texture2);
    unsigned int getTextureID(void);
    unsigned int getTextureID2(void);
};

#endif