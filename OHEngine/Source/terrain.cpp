/******************************************************************************/
/*!
\file	terrain.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "terrain.h"


float Terrain::SIZE = 800.f;
float Terrain::MAX_HEIGHT = 40.f;
float Terrain::MAX_PIXEL_COLOR = 256.f * 256.f * 256.f;


Terrain::Terrain(void)
{
}

Terrain::Terrain(int gridX, int gridZ, MeshLoader loader, Mesh_TexturedModel texture, const char *file_path)
{
    this->texture = texture;
    this->x = gridX * SIZE;
    this->z = gridZ * SIZE;
    this->model = *this->GenerateTerrain(loader, file_path);
    this->enableLight = true;
    this->material.setkDiffuse(Component(0.9f, 0.9f, 0.9f));
    this->material.setkSpecular(Component(0.1f, 0.1f, 0.1f));
    this->material.setkAmbient(Component(0.1f, 0.1f, 0.1f));
    this->material.setkShininess(0.7f);
}

Terrain::~Terrain(void)
{

}

Mesh_RawModel* Terrain::GenerateTerrain(MeshLoader loader, const char *file_path)
{
    std::vector<Vertex> vertex_buffer_data;
    Vertex v;

    std::vector<unsigned char> heightMap;
    LoadHeightMap(file_path, heightMap);


    for(int i=0;i<VERTEX_COUNT;i++)
    {
        for(int j=0;j<VERTEX_COUNT;j++)
        {
            float height =  getHeight(i, j, heightMap);
            heights[j][i] = static_cast<unsigned char> (height);

            v.pos.Set((static_cast<float>(j)/(static_cast<float>(VERTEX_COUNT - 1))) * SIZE, height,
                ((static_cast<float>(i)/static_cast<float>(VERTEX_COUNT - 1)) * SIZE));
            v.color.Set(static_cast<float>(heightMap[i * VERTEX_COUNT + j]) / VERTEX_COUNT, static_cast<float>(heightMap[i * VERTEX_COUNT + j]) / VERTEX_COUNT, static_cast<float>(heightMap[i * VERTEX_COUNT + j]) / VERTEX_COUNT);
            v.normal = calculateNormal(i, j, heightMap);
            //v.normal.Set(0, 1.f, 0);
            v.texCoord.Set(static_cast<float>(j)/static_cast<float>((VERTEX_COUNT - 1)), static_cast<float>(i)/static_cast<float>((VERTEX_COUNT - 1)));
            vertex_buffer_data.push_back(v);  
        }
    }

    std::vector<GLuint> index_buffer_data;

    int pointer = 0;
    for(int gz=0;gz<VERTEX_COUNT-1;gz++)
    {
        for(int gx=0;gx<VERTEX_COUNT-1;gx++)
        {
            int topLeft = (gz*VERTEX_COUNT)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
            int bottomRight = bottomLeft + 1;
            index_buffer_data.push_back(topLeft);
            index_buffer_data.push_back(bottomLeft);
            index_buffer_data.push_back(topRight);
            index_buffer_data.push_back(topRight);
            index_buffer_data.push_back(bottomLeft);
            index_buffer_data.push_back(bottomRight);
        }
    }

    heightMap.clear();
    return loader.loadToVAO(vertex_buffer_data, index_buffer_data);
}

float Terrain::barryCentric(Vector3 &p1, Vector3 &p2, Vector3 &p3, Vector2 &pos)
{
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);      // ok

    float l1 = 0;
    float l2 = 0;
    if (det != 0)
    {
        l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det; // ok
        l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    }
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ)
{

    float terrainX = worldX - this->x;
    float terrainZ = worldZ - this->z;

    float gridSquareSize = SIZE / (VERTEX_COUNT - 1.f);

    int gridX = static_cast<int>(floor(terrainX / gridSquareSize));
    int gridZ = static_cast<int>(floor(terrainZ / gridSquareSize));

    if (gridX >= (VERTEX_COUNT - 1) || gridZ >=(VERTEX_COUNT - 1) || gridX < 0 || gridZ < 0)
    {
        return 0;
    }

    int pX = 0;
    int pZ = 0;
    int cX = static_cast<int>(gridSquareSize);

    if (cX != 0)
    {
         pX = static_cast<int>(terrainX) % cX;
         pZ = static_cast<int>(terrainZ) % cX;
    }
    
    float xCoord = static_cast<float>(pX) / gridSquareSize;
    float zCoord = static_cast<float>(pZ) / gridSquareSize;
    

    float answer = 0;
    if(xCoord <= (1-zCoord))
    {
        answer = barryCentric(Vector3(0, heights[gridX][gridZ], 0), Vector3(1.f, static_cast<float>(heights[gridX + 1][gridZ]), 0),
            Vector3(0, heights[gridX][gridZ + 1], 1.f), Vector2(xCoord, zCoord));
    }

    else
    {
        answer = barryCentric(Vector3(1, heights[gridX + 1][gridZ], 0), Vector3(1.f, static_cast<float>(heights[gridX + 1][gridZ + 1]), 1.f),
            Vector3(0, heights[gridX][gridZ + 1], 1.f), Vector2(xCoord, zCoord));
    }

    return answer;
}

float Terrain::getHeight(unsigned int x, unsigned int z, std::vector<unsigned char> &heightMap)
{
    if (x < 0 || x >= 256 || z < 0 || z >= 256)
        return 0;

    float height = static_cast<float>(heightMap[x * 256 + z]);

    return height;
}

bool Terrain::LoadHeightMap(const char *file_path, std::vector<unsigned char> &heightMap)
{
	std::ifstream fileStream(file_path, std::ios::binary);
	if(!fileStream.is_open())
	{
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return false;
	}

    fileStream.seekg(0, std::ios::end);
    std::streampos fsize = (unsigned)fileStream.tellg();
	
	fileStream.seekg(0, std::ios::beg);
	heightMap.resize((unsigned)fsize);
	fileStream.read((char *)&heightMap[0], fsize);
	
	fileStream.close();
	return true;
}

float Terrain::getX(void)
{
    return x;
}

void Terrain::setX(float x)
{
    this->x = x;
}

float Terrain::getZ(void)
{
    return z;
}

void Terrain::setZ(float z)
{
    this->z = z;
}

Mesh_RawModel Terrain::getRawModel(void)
{
    return model;
}

void Terrain::setRawModel(Mesh_RawModel model)
{
    this->model = model;
}

Mesh_TexturedModel Terrain::getTexturedModel(void)
{
    return texture;
}

void Terrain::setTexturedModel(Mesh_TexturedModel texture)
{
    this->texture = texture;
}

Material Terrain::getMaterial(void)
{
    return material;
}

void Terrain::setMaterial(Material material)
{
    this->material = material;
}

bool Terrain::getLight(void)
{
    return enableLight;
}

void Terrain::setLightEnable(bool enableLight)
{
    this->enableLight = enableLight;
}

Vector3 Terrain::calculateNormal(int x, int z, std::vector<unsigned char> &heightMap)
{
    float heightL = getHeight(x - 1, z, heightMap);
    float heightR = getHeight(x + 1, z, heightMap);
    float heightD = getHeight(x, z - 1, heightMap);
    float heightU = getHeight(x, z + 1, heightMap);

    return Vector3(heightL - heightR, 2.f, heightD - heightU).Normalized();
}