/**
 *
 */

#include "cEntFlea.hpp"


using namespace GFX;

cEntFlea::cEntFlea()
: cEntity()
{
    dim.x = dim.y = 128.0f;
    orient = 90.0f;
    mk_thrust_rate = 2.0f;
    mk_max_thrust = 8.0f;
    mk_normal_thrust = 2.0f;
    mk_turn_rate = 0.01f;
    mk_max_turn= 1.0f;

    bounding_circle = Circlef(50.0f, 0.0f, 0.0f);

    m_anim.SetTicksPerFrame(100.0f);
    m_anim_s.SetTicksPerFrame(100.0f);
    type = PLAYER;
}

cEntFlea::~cEntFlea()
{
    //dtor
}
