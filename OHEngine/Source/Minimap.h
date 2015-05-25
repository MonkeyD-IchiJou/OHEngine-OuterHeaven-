#ifndef MINIMAP_H
#define MINIMAP_H

#include "Vector2.h"
#include "TexturedModel.h"

class Minimap
{
public:
    Minimap(void);
    ~Minimap(void);

    bool SetBackground(TexturedModel m_MiniMap_background);
    TexturedModel getBackground(void);

    bool setBorder(TexturedModel m_MiniMap_Border);
    TexturedModel getBorder(void);

    bool setAvatar(TexturedModel m_MiniMap_Avatar);
    TexturedModel getAvatar(void);

    bool setAngle(const float angle);
    float getAngle(void);

    bool setPosition(const float x, const float y);
    float getPosition_x(void);
    float getPosition_y(void);
    Vector2 getPosition(void);

    bool setSize(const float size_x, const float size_y);
    float getSize_x(void);
    float getSize_y(void);
    Vector2 getSize(void);


private:
    TexturedModel m_MiniMap_background;
    TexturedModel m_MiniMap_Border;
    TexturedModel m_MiniMap_Avatar;

    // Rotation from first angle
    float angle;
    // offset in the minimap
    Vector2 offset;
    // Minimap size
    Vector2 size;
};

#endif