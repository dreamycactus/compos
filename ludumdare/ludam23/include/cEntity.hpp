#ifndef CENTITY_H
#define CENTITY_H

#include "MATH_Math.hpp"
#include "Circlef.hpp"
#include "GFX_G2D_cSpriteBatch.hpp"

using namespace MATH;
using namespace GFX;
using namespace GFX::G2D;

class cEntityManager;

class cEntity
{
public:
    enum EType { PLAYER, NOMMY, BIGNOM };

    cEntity();
    virtual ~cEntity();

    virtual void Update();
    virtual void Render(cSpriteBatch& batch) {};

    virtual void Collided(cEntity& e) {}
    virtual Circlef GetCollisionCircle() { return Circlef(bounding_circle.r, bounding_circle.x+pos.x+dim.x/2.0f, bounding_circle.y+pos.y+dim.y/2.0f); }
    static void SetEntityManager(cEntityManager* m) { mp_entity_manager = m; }
    static cEntityManager* GetEntityManager() { return mp_entity_manager; }
    Vec2f pos;
    Vec2f vel;
    Vec2f dim;

    float orient;
    float ang_vel;

    Circlef bounding_circle;
    bool is_collidable;
    bool is_alive;
    EType type;

protected:
    static cEntityManager* mp_entity_manager;

};

#endif // CENTITY_H
