/******************************************************************************/
/*!
\file	TerrainRenderer.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include "TerrainShader.h"
#include "MatrixStack.h"
#include "terrain.h"
#include "Camera.h"

class TerrainRenderer
{
private:
    TerrainShader *shader;
    MS model, view, projection;

    void prepareTerrain(Terrain terrain);
    void unbindTexturedModel(void);
    void loadModelMatrix(Terrain &terrain);

public:
    TerrainRenderer(void);
    TerrainRenderer(TerrainShader *shader, Mtx44 projection);
    ~TerrainRenderer(void);

    void render(std::vector<Terrain> terrains);

    void LoadProjection(Mtx44 projection);
    void createViewMatrix(Camera &camera);      // will optimised this later
    void renderLight(Light *light);
};

#endif