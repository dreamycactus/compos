#ifndef CENTFLEA_H
#define CENTFLEA_H

#include "GFX_cTextureRegistry.hpp"
#include "GFX_G2D_cSpriteBatch.hpp"
#include "cEntity.hpp"
#include "GFX_G2D_cAnimation.hpp"
#include "SoundRegistry.hpp"


using namespace GFX::G2D;

class cEntFlea : public cEntity
{
public:
    cEntFlea();
    virtual ~cEntFlea();

    void Init()
    {
        m_anim.PushFrame(Art("flea1"));
        m_anim.PushFrame(Art("flea0"));
        m_anim.PushFrame(Art("flea1"));
        m_anim.PushFrame(Art("flea2"));

        m_anim_s.PushFrame(Art("flea_s0"));
        m_anim_s.PushFrame(Art("flea2"));
        m_anim_s.PushFrame(Art("flea_s1"));
        m_anim_s.PushFrame(Art("flea2"));

    }
    virtual void Update();
    virtual void Render(cSpriteBatch& batch);

    void Collided(cEntity& e)
    {
        switch (e.type)
        {
            case BIGNOM:
                is_alive = false;
                break;
            case NOMMY:
                mk_thrust_rate += 1.0f;
                m_cooldown = 0.0f;
                Mix_PlayChannel(-1, SoundRegistry::nom, 0);
                break;
            default:
                break;
        }
    }

    void Thrust();
private:
    float mk_thrust_rate;
    float mk_max_thrust;
    float mk_normal_thrust;
    float mk_turn_rate;
    float mk_max_turn;
    cAnimation m_anim;
    cAnimation m_anim_s;

    bool m_can_thrust;
    float m_energy;
    float m_cooldown;
    float m_statetime;
    float m_is_struggle;

};

inline void cEntFlea::Update()
{
    vel *= 0.99f;
    ang_vel *= 0.95f;

    if (vel.LengthSquared() > mk_max_thrust*mk_max_thrust) {
        vel.Normalize();
        vel *= mk_max_thrust;
    }
    clampf(ang_vel, -mk_max_turn, mk_max_turn);

    pos += vel;
    orient += ang_vel;
    orient = fmod(orient, 360.0f);
    m_cooldown -= 1.0f;
    if (m_cooldown <= 0.0f) {
        m_is_struggle = false;
    }

}
inline void cEntFlea::Render(cSpriteBatch& batch)
{
//    batch.DrawTexture(Art("tiles_e"), 0.0, 0.0f, 1.0f, 1.0f);
    if (m_is_struggle) {
        batch.DrawTexturePos2Dim2Origin2Scale2Rot(m_anim_s.GetKeyFrame(m_statetime, false), pos.x, pos.y, dim.x, dim.y, dim.x/2.0f, dim.y/2.0f, 1.0f, 1.0f, orient+90.0f);
    } else {
        batch.DrawTexturePos2Dim2Origin2Scale2Rot(m_anim.GetKeyFrame(m_statetime, false), pos.x, pos.y, dim.x, dim.y, dim.x/2.0f, dim.y/2.0f, 1.0f, 1.0f, orient+90.0f);
    }


    m_statetime += 10.0f;
}

inline void cEntFlea::Thrust()
{
    if (m_cooldown > 0){
        if (!m_is_struggle) {
            m_statetime = 0.0f;
            m_is_struggle = true;
            vel += Vec2f(mk_thrust_rate/10.0f, 0.0f).Rotated(orient);
        }
        return;
    }
    Mix_PlayChannel(2, SoundRegistry::swim, 0);
    vel += Vec2f(mk_thrust_rate, 0.0f).Rotated(orient);
    mk_thrust_rate = mk_normal_thrust;
    m_cooldown = 50.0f;
    m_statetime = 0.0f;

}

#endif // CENTFLEA_H
