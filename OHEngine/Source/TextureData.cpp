/******************************************************************************/
/*!
\file	TextureData.cpp
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#include "TextureData.h"

TextureData::TextureData(void)
{

}

TextureData::TextureData(unsigned char *data, unsigned int width, unsigned int height)
{
    this->data = data;
    this->width = width;
    this->height = height;
}

unsigned int TextureData::getWidth(void)
{
    return width;
}

unsigned int TextureData::getHeight(void)
{
    return height;
}

unsigned char* TextureData::getBuffer(void)
{
    return data;
}

TextureData::~TextureData(void)
{

}

