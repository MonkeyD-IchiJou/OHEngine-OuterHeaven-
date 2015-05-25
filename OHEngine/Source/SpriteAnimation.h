#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <string>
#include "Entity.h"

struct Animation
{
    Animation() {}
    void Set(int startFrame, int endFrame, int repeat, float time) 
    {
        this->startFrame = startFrame; 
        this->endFrame = endFrame; 
        this->repeatCount = repeat; 
        this->animTime = time;
        ended = false;
    }

    int startFrame;
    int endFrame;
    int repeatCount;
    float animTime;
    bool ended;
}; 


class SpriteAnimation : public Entity
{
public:
    SpriteAnimation(void);
    SpriteAnimation(TexturedModel mesh, Vector3 position, float w, Vector3 v, float scaleX, float scaleY, float scaleZ, int row, int col);
    ~SpriteAnimation();
    void Update(double dt);

    int m_row;
    int m_col;

    float m_currentTime;
    int m_playCount;
    Animation *m_anim;
};
#endif