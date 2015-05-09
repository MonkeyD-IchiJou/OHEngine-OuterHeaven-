/******************************************************************************/
/*!
\file	TextureData.h
\author Chuk Yih Jou
\brief

*/
/******************************************************************************/

#ifndef TEXTURE_DATA_H 
#define TEXTURE_DATA_H

class TextureData
{
private:
    unsigned int width, height;
    unsigned char *data;

public:
    TextureData(void);
    TextureData(unsigned char *data, unsigned int width, unsigned int height);
    ~TextureData(void);

    unsigned int getWidth(void);
    unsigned int getHeight(void);
    unsigned char* getBuffer();
};

#endif