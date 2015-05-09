/******************************************************************************/
/*!
\file	MeshLoader.cpp
\author Chuk Yih Jou
\brief
To store VBOs and IBO (index buffer) and bind both under VAO
*/
/******************************************************************************/
#include <iostream>
#include <fstream>
#include "MeshLoader.h"

std::vector<unsigned int> MeshLoader::vaos;
std::vector<unsigned int> MeshLoader::vbos;
std::vector<unsigned int> MeshLoader::textures;

MeshLoader::MeshLoader(void)
{
}

MeshLoader::~MeshLoader(void)
{
}

Mesh_RawModel* MeshLoader::loadToVAO(std::vector<Vertex> vertex_buffer_data, std::vector<GLuint> index_buffer_data)
{
    
    unsigned int vaoID = createVAO();

    StoreDataInAttributeList(vertex_buffer_data);
    bindIndicesBuffer(index_buffer_data);

    unbindVAO();     // unbind the vao 

    return new Mesh_RawModel(vaoID, index_buffer_data.size());
}

Mesh_TexturedModel* MeshLoader::loadTexture(const char *file_path)
{
    std::ifstream fileStream(file_path, std::ios::binary);
	if(!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return 0;
	}

	GLubyte		header[ 18 ];									// first 6 useful header bytes
	GLuint		bytesPerPixel;								    // number of bytes per pixel in TGA gile
	GLuint		imageSize;									    // for setting memory
	GLubyte *	data;
	GLuint		texture = 0;
	unsigned	width, height;

	fileStream.read((char*)header, 18);
	width = header[12] + header[13] * 256;
	height = header[14] + header[15] * 256;

 	if(	width <= 0 ||								// is width <= 0
		height <= 0 ||								// is height <=0
		(header[16] != 24 && header[16] != 32))		// is TGA 24 or 32 Bit
	{
		fileStream.close();							// close file on failure
		std::cout << "File header error.\n";
		return 0;										
	}

	bytesPerPixel	= header[16] / 8;						//divide by 8 to get bytes per pixel
	imageSize		= width * height * bytesPerPixel;	// calculate memory required for TGA data
	
	data = new GLubyte[ imageSize ];
	fileStream.seekg(18, std::ios::beg);
	fileStream.read((char *)data, imageSize);
	fileStream.close();	

	glGenTextures(1, &texture);
    textures.push_back(texture);        // store the id

	glBindTexture(GL_TEXTURE_2D, texture);
	if(bytesPerPixel == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	else //bytesPerPixel == 4
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);// try change the BGRA to RGBA     // data is the buffer that thin matrix is talking about

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	float maxAnisotropy = 1.f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint)maxAnisotropy );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // try change to GL_CLAMP or GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       
	
	glGenerateMipmap( GL_TEXTURE_2D );
	
	delete []data;

    glBindTexture(GL_TEXTURE_2D, 0);

	return new Mesh_TexturedModel(texture);		
}

unsigned int MeshLoader::loadCubeMap(const char *file_path[6])
{
    unsigned int textureID = 0;
    glGenTextures(1, &textureID);
    textures.push_back(textureID);        // store the id

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (int i = 0; i < 6; i++)
    {
        TextureData data = decodeTextureFile(file_path[i]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, 
            data.getWidth(), data.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.getBuffer());// try change the BGRA to RGBA     // data is the buffer that thin matrix is talking about
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return textureID;
}

TextureData MeshLoader::decodeTextureFile(const char *file_path)
{
    std::ifstream fileStream(file_path, std::ios::binary);
	if(!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
	}

	GLubyte		header[ 18 ];									// first 6 useful header bytes
	GLuint		bytesPerPixel;								    // number of bytes per pixel in TGA gile
	GLuint		imageSize;									    // for setting memory
	GLubyte *	data;
	GLuint		texture = 0;
	unsigned	width, height;

	fileStream.read((char*)header, 18);
	width = header[12] + header[13] * 256;
	height = header[14] + header[15] * 256;

 	if(	width <= 0 ||								// is width <= 0
		height <= 0 ||								// is height <=0
		(header[16] != 24 && header[16] != 32))		// is TGA 24 or 32 Bit
	{
		fileStream.close();							// close file on failure
		std::cout << "File header error.\n";
	}

	bytesPerPixel	= header[16] / 8;						//divide by 8 to get bytes per pixel
	imageSize		= width * height * bytesPerPixel;	// calculate memory required for TGA data
	
	data = new GLubyte[ imageSize ];
	fileStream.seekg(18, std::ios::beg);
	fileStream.read((char *)data, imageSize);
	fileStream.close();	

    return TextureData(data, width, height);
}

unsigned int MeshLoader::createVAO(void)
{
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);       // generate vao
    vaos.push_back(vaoID);              // store the vao id
    glBindVertexArray(vaoID);   // bind the vao and set it the current vao
    return vaoID;
}

void MeshLoader::unbindVAO(void)
{
    glBindVertexArray(0);   // bind the vao and set it the current vao
}

void MeshLoader::StoreDataInAttributeList(std::vector<Vertex> vertex_buffer_data)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);        // generate buffers
    vbos.push_back(vboID);          // store the vbo id

	glBindBuffer(GL_ARRAY_BUFFER, vboID);   // Set the current active buffer
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW); // Transfer vertices to OpenGL

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // unbind the current vbo
}

void MeshLoader::bindIndicesBuffer(std::vector<GLuint> index_buffer_data)
{
    unsigned int indexID;
    glGenBuffers(1, &indexID);      // generate index buffer
    vbos.push_back(indexID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
}

void MeshLoader::CleanUpBufferObjects(void)
{
    glDeleteVertexArrays(vaos.size(), &vaos[0]);
    glDeleteBuffers(vbos.size(), &vbos[0]);
    glDeleteTextures(textures.size(), &textures[0]);
}
