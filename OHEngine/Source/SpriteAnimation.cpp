#include "SpriteAnimation.h"
#include "MyGL.h"
#include "MyMath.h"

SpriteAnimation::SpriteAnimation(TexturedModel mesh, Vector3 position, float w, Vector3 v, float scaleX, float scaleY, float scaleZ, int row, int col) : Entity(mesh, position, w, v, scaleX, scaleY, scaleZ)
    , m_row(row)
    , m_col(col)
    , m_currentTime(0)
    , m_playCount(0)
{
    m_anim = NULL;
   
} 

SpriteAnimation::SpriteAnimation(void)
{

}

SpriteAnimation::~SpriteAnimation()
{
    if(m_anim)
        delete m_anim;
} 

void SpriteAnimation::Update(double dt)
{
    if(m_anim) // If animation happens
    {
        // Animation current time, m_currentTime increments by delta time, dt
        m_currentTime += static_cast<float>(dt);

        // Variable int numFrame is set to maximum value between (1, (endFrame – startFrame + 1))
        int numFrame = Math::Max(1, (m_anim->endFrame - m_anim->startFrame +1));
        
        


        // Variable float frameTime = animTime / numFrame
        float frameTime = m_anim->animTime / numFrame;


        // Animation current frame, m_currentFrame is set to the minimum value between (endFrame, (startFrame + (m_currentTime/frameTime))) 
        m_currentFrame =  Math::Min(m_anim->endFrame, (m_anim->startFrame + static_cast<int>((m_currentTime / frameTime))));

        // If the m_currentTime is greater than animTime Set animation end flag, ended to true
        if(m_currentTime > m_anim->animTime)
        {
            m_anim->ended = true;

            if(m_playCount + 1 < m_anim->repeatCount || m_anim->repeatCount == 0)
            {
                m_playCount += dt;
                m_currentTime = 0;
                m_currentFrame = m_anim->startFrame;
            }
        }
        
    }
}
