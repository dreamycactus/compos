#ifndef CSUCKYCAM_H
#define CSUCKYCAM_H

#include <SDL2/SDL_opengl.h>
#include "MATH_Math.hpp"

using namespace MATH;

class cSuckyCam
{
public:
    cSuckyCam()
    : pos(Vec2f(0.0f, 0.0f))
    , vel(Vec2f(0.0f, 0.0f))
    , orient(0)
    , scale(1.0f)
    , width(640)
    , height(480) {}
    virtual ~cSuckyCam() {}

    void Update();
    void SetMatricies();


    Vec2f pos;
    Vec2f vel;
    float orient;
    float scale;

    float width;
    float height;
private:

};

inline void cSuckyCam::Update()
{
    pos += vel;
}

inline void cSuckyCam::SetMatricies()
{
    glMatrixMode(GL_MODELVIEW);
    glScalef(scale, scale, 1.0f);
    glTranslatef(pos.x, pos.y, 0.0f);
    glRotatef(orient, 0.0f, 0.0f, 1.0f);
}

#endif // CSUCKYCAM_H
