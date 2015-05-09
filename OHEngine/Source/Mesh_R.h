/******************************************************************************/
/*!
\file	Mesh_R.h
\author Chuk Yih Jou
\brief
To store VAO info here, for raw model which is not textured
*/
/******************************************************************************/

#ifndef MESH_R_H
#define MESH_R_H

class Mesh_RawModel
{
private:
    unsigned int vaoID, indexSize;

public:
    Mesh_RawModel(void);
    Mesh_RawModel(unsigned int vaoID, unsigned int indexSize);
    ~Mesh_RawModel(void);

    unsigned int getVaoID(void);
    unsigned int getIndexSize(void);
};

#endif 