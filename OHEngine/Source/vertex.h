/******************************************************************************/
/*!
\file	vertex.h
\author Chuk Yih Jou
\brief
Provide position, color and vertex variables
*/
/******************************************************************************/

#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"

/******************************************************************************/
/*!
		Struct Position:
\brief	position object variable
*/
/******************************************************************************/
struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) {Set(x, y, z);}
	void Set(float x, float y, float z) {this->x = x; this->y = y; this->z = z;}
};

/******************************************************************************/
/*!
		Struct Color:
\brief	color object variable
*/
/******************************************************************************/

struct Color
{
	float r, g, b;
	Color(float r = 1, float g = 1, float b = 1) {Set(r, g, b);}
	void Set(float r, float g, float b) {this->r = r; this->g = g; this->b = b;}
};

struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0) {Set(u, v);}
	void Set(float u, float v) {this->u = u; this->v = v;}
};

/******************************************************************************/
/*!
		Struct Vertex:
\brief	vertex object variable
*/
/******************************************************************************/

struct Vertex 
{
	Position pos;
	Color color;
	Vector3 normal;
    TexCoord texCoord;
};



#endif