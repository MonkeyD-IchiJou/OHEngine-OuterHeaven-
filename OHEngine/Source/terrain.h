/******************************************************************************/
/*!
\file	terrain.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/
#ifndef TERRAIN_H
#define TERRAIN_H

#include "TexturedModel.h"
#include "Mesh_TerrainT.h"
#include "MeshLoader.h"
#include "Material.h"
#include "Vector2.h"

class Terrain
{
private:
    static float SIZE;
    static float MAX_HEIGHT;
    static float MAX_PIXEL_COLOR;
    const static int VERTEX_COUNT = 256;

    unsigned char heights[256][256];

    float x, z;
    Mesh_RawModel model;
    Mesh_MultiTexturedModel texture;
    Material material;
    bool enableLight;

    Mesh_RawModel* GenerateTerrain(MeshLoader loader, const char *file_path);
    bool LoadHeightMap(const char *file_path, std::vector<unsigned char> &heightMap);
    float getHeight(unsigned int x, unsigned int z,  std::vector<unsigned char> &heightMap);
    Vector3 calculateNormal(int x, int z, std::vector<unsigned char> &heightMap);
    static float barryCentric(Vector3 &p1, Vector3 &p2, Vector3 &p3, Vector2 &pos);

public:
    Terrain(void);
    Terrain(int gridX, int gridZ, MeshLoader loader, unsigned int textureID, unsigned int texture2, const char *file_path);
    ~Terrain(void);

    float getX(void);
    void setX(float x);

    float getZ(void);
    void setZ(float z);

    Mesh_RawModel getRawModel(void);
    void setRawModel(Mesh_RawModel model);

    Mesh_MultiTexturedModel getTexturedModel(void);
    void setTexturedModel(Mesh_MultiTexturedModel texture);

    Material getMaterial(void);
    void setMaterial(Material material);

    bool getLight(void);
    void setLightEnable(bool enableLight);

    float getHeightOfTerrain(float worldX, float worldZ);
};

#endif