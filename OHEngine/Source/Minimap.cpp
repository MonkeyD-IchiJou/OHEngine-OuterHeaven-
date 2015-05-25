#include "Minimap.h"


Minimap::Minimap(void)
{

}


Minimap::~Minimap(void)
{

}

bool Minimap::SetBackground(TexturedModel m_MiniMap_background)
{
    this->m_MiniMap_background = m_MiniMap_background;
    return true;
}


TexturedModel Minimap::getBackground(void)
{
    return m_MiniMap_background;
}

bool Minimap::setBorder(TexturedModel m_MiniMap_Border)
{
    this->m_MiniMap_Border = m_MiniMap_Border;
    return true;
}


TexturedModel Minimap::getBorder(void)
{
    return m_MiniMap_Border;
}

bool Minimap::setAvatar(TexturedModel m_MiniMap_Avatar)
{
    this->m_MiniMap_Avatar = m_MiniMap_Avatar;
    return true;
}

TexturedModel Minimap::getAvatar(void)
{
    return m_MiniMap_Avatar;
}

bool Minimap::setAngle(const float angle)
{
    this->angle = angle;
    return true;
}


float Minimap::getAngle(void)
{
    return angle;
}

bool Minimap::setPosition(const float x, const float y)
{
    this->offset.Set(x, y);
    return true;
}


float Minimap::getPosition_x(void)
{
    return this->offset.x;
}


float Minimap::getPosition_y(void)
{
    return this->offset.y;
}


Vector2 Minimap::getPosition(void)
{
    return this->offset;
}



bool Minimap::setSize(const float size_x, const float size_y)
{
    this->size.Set(size_x, size_y);
    return true;
}


float Minimap::getSize_x(void)
{
    return this->size.x;
}


float Minimap::getSize_y(void)
{

    return this->size.y;
}


Vector2 Minimap::getSize(void)
{

    return this->size;
}