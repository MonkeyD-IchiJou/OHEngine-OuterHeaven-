/******************************************************************************/
/*!
\file	MeshLoader.h
\author Chuk Yih Jou
\brief
To store VBOs and IBO (index buffer) and bind both under VAO
*/
/******************************************************************************/

#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include <GL\glew.h>
#include <vector>
#include "vertex.h"
#include "Mesh_R.h"
#include "Mesh_T.h"
#include "TextureData.h"

class MeshLoader
{
private:
    void StoreDataInAttributeList(std::vector<Vertex> vertex_buffer_data);
    void bindIndicesBuffer(std::vector<GLuint> index_buffer_data);

    unsigned int createVAO(void);
    void unbindVAO(void);

    TextureData decodeTextureFile(const char *file_path);           // for skybox de .. dun care this first

    static std::vector<unsigned int> vaos;
    static std::vector<unsigned int> vbos;
    static std::vector<unsigned int> textures;

public:
    MeshLoader();
    ~MeshLoader();

    Mesh_RawModel* loadToVAO(std::vector<Vertex> vertex_buffer_data, std::vector<GLuint> index_buffer_data);
    Mesh_TexturedModel* loadTexture(const char *file_path);

    unsigned int loadCubeMap(const char *file_path[6]);     // for skybox .. ignore this 

    void CleanUpBufferObjects(void);
};

#endif