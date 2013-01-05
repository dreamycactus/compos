/**
 *
 */
#include <cmath>
#include "cEntity.hpp"

cEntityManager* cEntity::mp_entity_manager = 0;

cEntity::cEntity()
: pos(Vec2f(0.0f,0.0f))
, vel(Vec2f(0.0f,0.0f))
, dim(Vec2f(1.0f,1.0f))
, orient(0.0f)
, ang_vel(0.0f)
, is_collidable(false)
, is_alive(true)
{

}

cEntity::~cEntity()
{
    //dtor
}


void cEntity::Update()
{
    pos += vel;
    orient += ang_vel;
    orient = fmod(orient, 360.0f);
}
