/******************************************************************************/
/*!
\file	MeshBuilder.h
\author Chuk Yih Jou
\brief
Class to provide meshes of different shapes
*/
/******************************************************************************/
#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Vertex.h"
#include "MeshLoader.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
    static Mesh_RawModel* GenerateCube(void);
    static Mesh_RawModel* GenerateText(unsigned int numRow, unsigned int numCol);
    static Mesh_RawModel* GenerateOBJ(const std::string &file_path);
    static Mesh_RawModel* GenerateQuad(float tex);
    static Mesh_RawModel* GenerateSkyPlane(const std::string &meshName, Color color, int slices, float PlanetRadius, float AtmosphereRadius, float hTile, float vTile);
    static Mesh_RawModel* GenerateTerrain(const std::string &meshName, const std::string &file_path, std::vector<unsigned char> &heightMap);

    static Mesh_RawModel* GenerateMinimap(Color color, float length = 1.f);
    static Mesh_RawModel* GenerateMinimapBorder(Color color, float length = 1.f);
    static Mesh_RawModel* GenerateMinimapAvatar(Color color, float length = 1.f);

    static Mesh_RawModel* MeshBuilder::GenerateSpriteAnimation(unsigned numRow, unsigned numCol);
};

#endif