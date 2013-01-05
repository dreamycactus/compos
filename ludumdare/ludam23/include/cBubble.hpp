#ifndef CBUBBLE_H
#define CBUBBLE_H

#include "cEntity.hpp"
#include "GFX_G2D_cSpriteBatch.hpp"

class cBubble : public cEntity
{
    public:
        cBubble() {}
        cBubble(float x, float y)
        {
            pos.x = x;
            pos.y = y;
            is_collidable = false;
            dim.x = dim.y = 5.0f;
            is_alive = true;
        }
        virtual ~cBubble() {}

        void Render(cSpriteBatch& batch)
        {
            batch.DrawTexturePos2Dim2Origin2Scale2Rot(Art("bubble"), pos.x, pos.y, dim.x, dim.y, dim.x/2.0f, dim.y/2.0f, 1.0f, 1.0f, 0.0f);
        }
    private:
};

#endif // CBUBBLE_H
