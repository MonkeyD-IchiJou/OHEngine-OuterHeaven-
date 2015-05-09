/******************************************************************************/
/*!
\file	SkyboxRenderer.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef SKY_BOX_RENDERER_H
#define SKY_BOX_RENDERER_H

#include "Mesh_R.h"
#include "SkyboxShader.h"
#include "MeshBuilder.h"
#include "Camera.h"

class SkyboxRenderer
{
private:
    static const char *texture_file[6]; 

    Mesh_RawModel cube;
    unsigned int textureID;
    SkyboxShaders *shader;

public:
    //take in meshbuilder cube
    SkyboxRenderer(void);
    SkyboxRenderer(MeshLoader loader, Mtx44 &VP);
    ~SkyboxRenderer(void);

    void render(Camera camera);
};

#endif