#ifndef CIRCLEF_H
#define CIRCLEF_H

#include <SDL2/SDL_opengl.h>
#include "MATH_Vec2.hpp"


using namespace MATH;

class Circlef
{
public:
    Circlef() : r(0), x(0), y(0) {}
    Circlef(float vr, float vx, float vy) : r(vr), x(vx), y(vy) {}
    virtual ~Circlef() {}

    inline float IsCollided(const Circlef& c)
    {
        const float dx = c.x-x;
        const float dy = c.y-y;

        return (dx*dx+dy*dy < c.r*c.r+r*r);
    }
    float r, x, y;

};

inline void DrawCircle(const Circlef& c)
{
    const float step = 0.2f;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(c.x, c.y);
        for (float i=0.f; i<2.f*PI+step; i=i+step)
        {
            glVertex2f(c.x + sin(i) * c.r, c.y + cos(i) * c.r);
        }
    glEnd();
}

inline void DrawQuad(const Vec2f& p1, const Vec2f& p2, const Vec2f& p3,
              const Vec2f& p4, const Vec3f& c=Vec3f(0.f, 1.f, 1.f))
{
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p3.x, p3.y);
        glVertex2f(p4.x, p4.y);
        glColor4f(1.0,1.0f,1.0f,1.0f);
    glEnd();
}

inline void DrawRectangle(const Vec2f& p1, const Vec2f& p2)
{
    const Vec2f delta = p2-p1;
    DrawQuad(p1, Vec2f(p1.x, p1.y+delta.y), p2, Vec2f(p1.x+delta.x, p1.y));
}

#endif // CIRCLEF_H
