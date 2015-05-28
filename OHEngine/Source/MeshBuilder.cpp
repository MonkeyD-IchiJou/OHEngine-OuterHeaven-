/******************************************************************************/
/*!
\file	MeshBuilder.cpp
\author Chuk Yih Jou
\brief
Build meshes and object here
*/
/******************************************************************************/
#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include "MyMath.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a OBJ; 
\param meshName - name of mesh
\param file_path - name of the file
\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/



Mesh_RawModel* MeshBuilder::GenerateOBJ(const std::string &file_path) {
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;

	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);

	if(!success)
		return NULL;

	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
    
    MeshLoader *LockAndLoad = new MeshLoader();

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);
}

Mesh_RawModel* MeshBuilder::GenerateLine(void)
{
    Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

    v.pos.Set(1, -0.75, 4.5);
    v.color.Set(1, 1, 1);
    vertex_buffer_data.push_back(v);

    v.pos.Set(0, 0, -0.2);
    v.color.Set(1, 1, 1);
    vertex_buffer_data.push_back(v);

    index_buffer_data.push_back(1);
    index_buffer_data.push_back(0);

    MeshLoader *LockAndLoad = new MeshLoader();

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object
\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2
\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/

/******************************************************************************/
/*!
\brief
Generate the vertices of a text quad; 
\param meshName - name of mesh
\param numRow - width of quad
\param numCol - height of quad
\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/

Mesh_RawModel* MeshBuilder::GenerateText(unsigned int numRow, unsigned int numCol)
{
    float width = 1.0f / numCol;
	float height = 1.0f / numRow;
    Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

    int offset = 0;

	for(int i = numRow - 1; i >= 0; --i)
	{
		for(unsigned int j = 0; j < numCol; ++j)
		{
            v.pos.Set(-0.5, -0.5, 0);
            v.texCoord.Set(j * width, i * height);
            vertex_buffer_data.push_back(v);

            v.pos.Set(0.5, -0.5, 0);
            v.texCoord.Set(j * width + width, i * height);
            vertex_buffer_data.push_back(v);

            v.pos.Set(0.5, 0.5, 0); 
            v.texCoord.Set(j * width + width, i * height + height);
            vertex_buffer_data.push_back(v);

            v.pos.Set(-0.5, 0.5, 0);
            v.texCoord.Set(j * width, i * height + height);
            vertex_buffer_data.push_back(v);

            //Task: Add 6 indices into index_buffer_data
            index_buffer_data.push_back(offset + 1);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 0);
            index_buffer_data.push_back(offset + 0);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 3);

            offset += 4;
		}
	}

    MeshLoader *LockAndLoad = new MeshLoader();

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);
}

Mesh_RawModel* MeshBuilder::GenerateSpriteAnimation(unsigned numRow, unsigned numCol)
{
    float width = 1.0f / numCol;
	float height = 1.0f / numRow;
    Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

    int offset = 0;

	for(int i = numRow - 1; i >= 0; --i)
	{
		for(unsigned int j = 0; j < numCol; ++j)
		{
            v.pos.Set(-0.5, -0.5, 0);
            v.texCoord.Set(j * width, i * height);
            vertex_buffer_data.push_back(v);

            v.pos.Set(0.5, -0.5, 0);
            v.texCoord.Set(j * width + width, i * height);
            vertex_buffer_data.push_back(v);

            v.pos.Set(0.5, 0.5, 0); 
            v.texCoord.Set(j * width + width, i * height + height);
            vertex_buffer_data.push_back(v);

            v.pos.Set(-0.5, 0.5, 0);
            v.texCoord.Set(j * width, i * height + height);
            vertex_buffer_data.push_back(v);

            //Task: Add 6 indices into index_buffer_data
            index_buffer_data.push_back(offset + 1);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 0);
            index_buffer_data.push_back(offset + 0);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 3);

            offset += 4;
		}
	}

    MeshLoader *LockAndLoad = new MeshLoader();

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);
}


/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object
\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad
\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/



/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object
\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube
\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/


/******************************************************************************/
/*!
\brief
Generate the vertices of a line for 2D; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object
\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad
\param centerX - centerX of the quad
\param centerY - centerY of the quad
\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/


/******************************************************************************/
/*!
\brief
Generate the vertices of a line for 2D; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object
\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad
\param centerX - centerX of the quad
\param centerY - centerY of the quad
\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/


/******************************************************************************/
/*!
\brief
Generate the vertices of a line for 2D; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object
\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad
\param centerX - centerX of the quad
\param centerY - centerY of the quad
\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/


// testing for new engine code
Mesh_RawModel* MeshBuilder::GenerateCube(void)
{
	// An array of 3 vectors which represents 3 vertices
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

    float lengthX = 1;
    float lengthY = 1;
    float lengthZ = 1;

    Color color(0, 1, 1);

	v.pos.Set(-lengthX,-lengthY,-lengthZ);//back bottom left
	v.color = color;
	v.normal.Set(0, 0, 1);
    v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX,-lengthY,-lengthZ); //back bottom right
	v.color = color;
	v.normal.Set(0, 0, 1);
    v.texCoord.Set (1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX, lengthY,-lengthZ); //back top right
	v.color = color;
	v.normal.Set(0, 0, 1);
    v.texCoord.Set (1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-lengthX, lengthY,-lengthZ); //back top left
	v.color = color;
	v.normal.Set(0, 0, 1);
    v.texCoord.Set (0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-lengthX,-lengthY, lengthZ);// front bottom left
	v.color = color;
	v.normal.Set(0, 0, 1);
    v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX,-lengthY, lengthZ); //front bottom right
	v.color = color;
	v.normal.Set(0, 0, 1);
    v.texCoord.Set (1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX, lengthY, lengthZ); //front top right
	v.color = color;
	v.normal.Set(0, 0, 1);
    v.texCoord.Set (1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-lengthX, lengthY, lengthZ); //front top left
	v.color = color;
	v.normal.Set(0, 0, 1);
    v.texCoord.Set (0, 0);
	vertex_buffer_data.push_back(v);
    
	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(7); //front
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5); //front
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6); //right
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1); //right
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(3); //top
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(6); //top
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2); //back
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0); //back
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3); //left
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(4); //left
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1); //bottom
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(4); //bottom
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(5);

    MeshLoader *LockAndLoad = new MeshLoader();
    

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);
}

Mesh_RawModel* MeshBuilder::GenerateQuad(float tex)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

    float length = 1.f;
    Color color = (1.f, 0.f, 0.f);

	v.pos.Set(-1.0f * length, 1.0f * length, 0.0f * length);		//top left
    v.color = color;
	v.normal.Set (0, 0, 1);
	v.texCoord.Set (0, tex);
	vertex_buffer_data.push_back(v);

	v.pos.Set(1.0f * length, 1.0f * length, 0.0f * length);		//top right
	v.color = color;
	v.normal.Set (0, 0, 1);
	v.texCoord.Set (tex, tex);
	vertex_buffer_data.push_back(v);

	v.pos.Set(1.0f * length, -1.0f * length, 0.0f * length);			//bottom right
	v.color = color;
	v.normal.Set (0, 0, 1);
	v.texCoord.Set (tex, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-1.0f * length, -1.0f * length, 0.0f * length);		//bottom left
	v.color = color;
	v.normal.Set (0, 0, 1);
	v.texCoord.Set (0, 0);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(2);

	MeshLoader *LockAndLoad = new MeshLoader();

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);
}

Mesh_RawModel*  MeshBuilder::GenerateSkyPlane(const std::string &meshName, Color color, int slices, float PlanetRadius, float AtmosphereRadius, float hTile, float vTile)
{
    (slices < 1)?(slices = 1) : (slices > 256) ? (slices = 256) : (slices);

    // Calculate some values we will need
    float planeSize = 2.0f * (float)sqrtf((AtmosphereRadius*AtmosphereRadius)-
        (PlanetRadius*PlanetRadius));
    float delta = planeSize / (float)slices;
    float texDelta = 2.0f / (float)slices; 

    
	std::vector<Vertex> vertex_buffer_data;
    // Calculate the vertex
    for ( int z = 0; z <= slices; ++z )
    {
        for ( int x = 0; x <= slices; ++x )
        {
            float xDist = (-0.5f * planeSize) + ( (float)x * delta );
            float zDist = (-0.5f * planeSize) + ( (float)z * delta );
            float xHeight = ( xDist * xDist ) / AtmosphereRadius;
            float zHeight = ( zDist * zDist ) / AtmosphereRadius;
            float height = xHeight + zHeight;

            Vertex tv; // temporary vertex
            tv.pos.x = xDist;
            tv.pos.y = 0.0f - height;
            tv.pos.z = zDist;
            // Calculate the texture coordinates
            tv.texCoord.u = hTile * ((float)x * texDelta * 0.5f);
            tv.texCoord.v = vTile * (1.0f - (float)z * texDelta * 0.5f);
            tv.color = color;
            vertex_buffer_data.push_back(tv);
        }
    } 

    std::vector<GLuint> index_buffer_data;
    // Calculate the indices
    int index = 0; // Indices
    for (int i=0; i < slices; ++i)
    {
        for (int j=0; j < slices; ++j)
        {
            int startvert = (i * (slices+1) + j);
            index_buffer_data.push_back(startvert);// tri 1
            index_buffer_data.push_back(startvert + 1);
            index_buffer_data.push_back(startvert + slices + 1);
            index_buffer_data.push_back(startvert + 1); // tri 2
            index_buffer_data.push_back(startvert + slices + 2);
            index_buffer_data.push_back(startvert + slices + 1);
        }
    }

    MeshLoader *LockAndLoad = new MeshLoader();

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);
}

Mesh_RawModel* MeshBuilder::GenerateTerrain(const std::string &meshName, const std::string &file_path, std::vector<unsigned char> &heightMap)
{
    const float SCALE_FACTOR = 256.0f;    

    std::vector<Vertex> vertex_buffer_data;

    Vertex v;  
    unsigned terrainSize = (unsigned)sqrt((double)heightMap.size());  

    for(unsigned z = 0; z < terrainSize; ++z)  
    {   
        for(unsigned x = 0; x < terrainSize; ++x)   
        { 
            float scaledHeight = (float)heightMap[z * terrainSize + x] /  SCALE_FACTOR;  
            v.pos.Set(static_cast<float>(x) / terrainSize - 0.5f, scaledHeight, static_cast<float>(z) / terrainSize - 0.5f);  
            v.color.Set(scaledHeight, scaledHeight, scaledHeight); //for rendering  height map without texture  
            v.normal.Set(0, 1.f, 0);
            v.texCoord.Set((float)x / terrainSize*10 , 1.f - (float)z / terrainSize*10);    
            vertex_buffer_data.push_back(v);   
        }  
    }  

    std::vector<GLuint> index_buffer_data;

    for(unsigned z = 0; z < terrainSize - 1; ++z)  
    {   
        for(unsigned x = 0; x < terrainSize - 1; ++x)   
        {    
            index_buffer_data.push_back(terrainSize * z + x + 0);  //Tri 1    
            index_buffer_data.push_back(terrainSize * (z + 1) + x + 0);    
            index_buffer_data.push_back(terrainSize * z + x + 1);  
            index_buffer_data.push_back(terrainSize * (z + 1) + x + 1); //Tri 2    
            index_buffer_data.push_back(terrainSize * z + x + 1);   
            index_buffer_data.push_back(terrainSize * (z + 1) + x + 0);   
        }  
    }  

    MeshLoader *LockAndLoad = new MeshLoader();

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);



    /*int count = VERTEX_COUNT * VERTEX_COUNT;
    float[] vertices = new float[count * 3];
    float[] normals = new float[count * 3];
    float[] textureCoords = new float[count*2];
    int[] indices = new int[6*(VERTEX_COUNT-1)*(VERTEX_COUNT*1)];
    int vertexPointer = 0;
    for(int i=0;i<VERTEX_COUNT;i++){
        for(int j=0;j<VERTEX_COUNT;j++){
            vertices[vertexPointer*3] = (float)j/((float)VERTEX_COUNT - 1) * SIZE;
            vertices[vertexPointer*3+1] = 0;
            vertices[vertexPointer*3+2] = (float)i/((float)VERTEX_COUNT - 1) * SIZE;
            normals[vertexPointer*3] = 0;
            normals[vertexPointer*3+1] = 1;
            normals[vertexPointer*3+2] = 0;
            textureCoords[vertexPointer*2] = (float)j/((float)VERTEX_COUNT - 1);
            textureCoords[vertexPointer*2+1] = (float)i/((float)VERTEX_COUNT - 1);
            vertexPointer++;
        }
    }
    int pointer = 0;
    for(int gz=0;gz<VERTEX_COUNT-1;gz++){
        for(int gx=0;gx<VERTEX_COUNT-1;gx++){
            int topLeft = (gz*VERTEX_COUNT)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }
    return loader.loadToVAO(vertices, textureCoords, normals, indices);*/
}
 
//SpriteAnimation* MeshBuilder::GenerateSpriteAnimation(const std::string
//    &meshName, unsigned numRow, unsigned numCol)
//{
//    Vertex v;
//    std::vector<Vertex> vertex_buffer_data;
//    std::vector<GLuint> index_buffer_data;
//
//    // Insert codes to render a quad.
//    // Get new tex coord for each frame.
//    // Hint: Same as GenerateText()
//
//    return *SpriteAnimation();
//} 


Mesh_RawModel* GenerateMinimap(Color color, float length)
{
    Vertex v;
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;

    // Draw the quad which contains the minimap's texture
    v.pos.Set(-0.5f * length,-0.5f * length,0);
    v.color = color;
    v.normal.Set(0, 0, 1);
    v.texCoord.Set(0, 0);
    vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f * length,-0.5f * length,0);
    v.color = color;
    v.normal.Set(0, 0, 1);
    v.texCoord.Set(1.0f, 0);
    vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f * length, 0.5f * length,0);
    v.color = color;
    v.normal.Set(0, 0, 1);
    v.texCoord.Set(1.0f, 1.0f);
    vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f * length, 0.5f * length,0);
    v.color = color;
    v.normal.Set(0, 0, 1);
    v.texCoord.Set(0, 1.0f);
    vertex_buffer_data.push_back(v);


    index_buffer_data.push_back(3);
    index_buffer_data.push_back(0);
    index_buffer_data.push_back(2);
    index_buffer_data.push_back(1);
    index_buffer_data.push_back(2);
    index_buffer_data.push_back(0);

    MeshLoader *LockAndLoad = new MeshLoader();

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);
}

Mesh_RawModel* GenerateMinimapBorder(Color color, float length)
{
    Vertex v;
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    // Draw the border of the minimap
    // Draw the quad which contains the minimap's texture
    v.pos.Set(-0.5f * length,-0.5f * length,0);
    v.color = color;
    vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f * length, 0.5f * length,0);
    v.color = color;
    vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f * length, 0.5f * length,0);
    v.color = color;
    vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f * length,-0.5f * length,0);
    v.color = color;
    vertex_buffer_data.push_back(v);
    index_buffer_data.push_back(0);
    index_buffer_data.push_back(1);
    index_buffer_data.push_back(1);
    index_buffer_data.push_back(2);
    index_buffer_data.push_back(2);
    index_buffer_data.push_back(3);
    index_buffer_data.push_back(3);
    index_buffer_data.push_back(0);

    MeshLoader *LockAndLoad = new MeshLoader();

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);
}

Mesh_RawModel* GenerateMinimapAvatar(Color color, float length)
{
    Vertex v;
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    // Draw the quad which contains the minimap's texture
    v.pos.Set(-0.05f * length,-0.10f * length,0);
    v.color = color;
    v.normal.Set(0, 0, 1);
    v.texCoord.Set(0, 0);
    vertex_buffer_data.push_back(v);
    v.pos.Set(0.05f * length,-0.10f * length,0);
    v.color = color;
    v.normal.Set(0, 0, 1);
    v.texCoord.Set(1.0f, 0);
    vertex_buffer_data.push_back(v);
    v.pos.Set(0, 0.15f * length,0);
    v.color = color;
    v.normal.Set(0, 0, 1);
    v.texCoord.Set(1.0f, 1.0f);
    vertex_buffer_data.push_back(v);
    index_buffer_data.push_back(0);
    index_buffer_data.push_back(1);
    index_buffer_data.push_back(2);
    MeshLoader *LockAndLoad = new MeshLoader();

    return LockAndLoad->loadToVAO(vertex_buffer_data, index_buffer_data);
}