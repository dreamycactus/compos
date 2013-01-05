#ifndef CENTBIGNOM_H
#define CENTBIGNOM_H

#include "GFX_G2D_cSpriteBatch.hpp"
#include "GFX_G2D_cAnimation.hpp"
#include "cEntity.hpp"
#include "MATH_MathHelper.hpp"

using namespace GFX::G2D;

class cEntBignom : public cEntity
{
public:
    cEntBignom() : cEntity()
    {
        dim.x = dim.y = 250.0f;
        orient = 90.0f;
        pos = Vec2f(10.0f, 10.0f);
        bounding_circle = Circlef(70.0f, 0.0f, 0.0f);

        m_anim.SetTicksPerFrame(100.0f);
        is_alive = false;
        is_collidable = true;
        type = BIGNOM;
    }
    virtual ~cEntBignom() {}

    void Collided(cEntity& e)
    {
    }

    void Init()
    {
        const cTextureWrapper& c = Art("big0");
        m_anim.PushFrame(Art("big0"));
        m_anim.PushFrame(Art("big1"));
        m_anim.PushFrame(Art("big2"));
    }

    void Update()
    {
        const cEntity& player = cEntity::GetEntityManager()->GetEntity(0);
        const Vec2f playerpos = player.pos+player.dim/2.0f;
        const Vec2f target_offset = playerpos - (pos+dim/2.0f);
        if (MATH::CloseTof(target_offset.LengthSquared(), 0.0f)) {
            return;
        }
        const Vec2f target_relative = target_offset.Rotated(-orient).Normalized();
        const Vec2f x_axis = Vec2f(1.0f, 0.0f);

        float angle_offset = x_axis.GetAngle(target_relative);

        if (fabs(angle_offset) > 5.0f)
        { orient += signf(target_relative.y)*1.0f; }

        Thrust();
        vel *= 0.9f;
        pos += vel;


    }

    void Render(cSpriteBatch& batch)
    {
        batch.DrawTexturePos2Dim2Origin2Scale2Rot(m_anim.GetKeyFrame(m_statetime, true), pos.x, pos.y, dim.x, dim.y, dim.x/2.0f, dim.y/2.0f, 1.0f, 1.0f, orient+90.0f);
        DrawCircle(GetCollisionCircle());
        m_statetime += 10.0f;
    }

    void Thrust()
    {
        vel += Vec2f(0.55f, 0.0f).Rotated(orient);
    }
private:
    cAnimation m_anim;
    float m_statetime;
};

#endif // CENTBIGNOM_H
