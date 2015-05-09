#include "GL\glew.h"
#include "Mesh_R.h"

Mesh_RawModel::Mesh_RawModel(void)
{
    vaoID = 0;
    indexSize = 0;
}

Mesh_RawModel::Mesh_RawModel(unsigned int vaoID, unsigned int indexSize)
{
    this->vaoID = vaoID;
    this->indexSize = indexSize;
}

Mesh_RawModel::~Mesh_RawModel(void)
{
}

unsigned int Mesh_RawModel::getVaoID(void)
{
    return vaoID;
}

unsigned int Mesh_RawModel::getIndexSize(void)
{
    return indexSize;
}