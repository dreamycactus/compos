#ifndef CENTNOMMY_H
#define CENTNOMMY_H

#include "GFX_G2D_cSpriteBatch.hpp"
#include "cEntity.hpp"

class cEntNommy : public cEntity
{
    public:
//        cEntNommy() { dim.x = dim.y = 16.0f; }
        cEntNommy(float x, float y) : cEntity()
        {
            pos.x = x;
            pos.y = y;
            dim.x = dim.y = 16.0f;
            is_alive = true;
            is_collidable = true;
            bounding_circle = Circlef(8.0f, 0.0f, 0.0f);
            type = NOMMY;
        }
        virtual ~cEntNommy() {}

        void Collided(cEntity& e)
        {
//            is_alive = false;
            pos.x = RandFloat(-5000.0f, 5000.0f);
            pos.y = RandFloat(-5000.0f, 5000.0f);
        }
        void Update()
        {
            static float state_time = 0.0f;

//            pos.x += sin_deg(state_time/50.0f) * 5.0f;
//            pos.y -= cos_deg(state_time/50.0f) * 5.0f;

            orient += sin_deg(state_time*50.0f) * 10.0f;
            state_time += 10.0f;
        }
        virtual void Render(cSpriteBatch& batch)
        {
            batch.DrawTexturePos2Dim2Origin2Scale2Rot(Art("nommy"), pos.x, pos.y, dim.x, dim.y, dim.x/2.0f, dim.y/2.0f, 1.0f, 1.0f, orient);
        }
    private:

};

#endif // CENTNOMMY_H
