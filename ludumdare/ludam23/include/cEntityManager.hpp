#ifndef CENTITYMANAGER_H
#define CENTITYMANAGER_H

#include <vector>
#include <memory>
#include "CORE_cGame.hpp"
#include "GFX_G2D_cSpriteBatch.hpp"
#include "cEntity.hpp"
#include "cSuckyCam.hpp"
#include "SoundRegistry.hpp"

    #include <cassert>
    #include <iostream>
    using namespace std;

using namespace MATH;

namespace
{
    inline bool IsPointInRect(const Vec2f& p, const Vec2f& tl, const Vec2f& br)
    {
        if (p.x < tl.x || p.x > br.x || p.y < br.y || p.y > tl.y)
        { return false; }
        return true;
    }
}

#define COLS 4
class cEntityManager
{
    public:
        cEntityManager();
        virtual ~cEntityManager();

        void Update()
        {
            if (mn_collisions > COLS ) {
                if (!has_played) {
                    Mix_PlayChannel(-1, SoundRegistry::beast, 0);
                    UnleashTheBeast();
                    has_played = true;
                }
            }
            cEntity& player = *m_entities[0].get();
            player.Update();
            for (unsigned int i=1; i<m_entities.size(); ++i) {
                if (!m_entities[i]->is_alive) {
                    continue;
                }
                m_entities[i]->Update();
                if (m_entities[i]->GetCollisionCircle().IsCollided(player.GetCollisionCircle())&& m_entities[i]->is_collidable) {
                    m_entities[i]->Collided(player);
                    player.Collided(*m_entities[i].get());
                    ++mn_collisions;
                }
            }
            cout << m_entities[1]->is_alive;
        }

        void Render(cSuckyCam& cam, cSpriteBatch& batch)
        {
            assert(!m_entities.empty());

            if (mn_collisions > COLS ) {
                static float zoom_state_time = 0.0f;
                const static float first_zoom = cam.scale;
                cam.scale = lerpf(first_zoom, 0.5f, zoom_state_time);
                zoom_state_time += 0.005f;
                zoom_state_time = minf(zoom_state_time, 1.0f);
            }
            const float half_w = 200.0f + (cam.width / cam.scale) / 2.0f;
            const float half_h = 200.0f + (cam.height / cam.scale) / 2.0f;

            const Vec2f player_pos = m_entities[0]->pos;
            const Vec2f topleft(player_pos.x-half_w, player_pos.y+half_h);
            const Vec2f bottomright(player_pos.x+half_w, player_pos.y-half_h);

            int count = 0;


            for (unsigned int i=2; i<m_entities.size(); ++i) {
                if (!m_entities[i]->is_alive) {
                    continue;
                }
                if (IsPointInRect(m_entities[i]->pos, topleft, bottomright)){
                    ++count;

                    m_entities[i]->Render(batch);
                }
            }
            m_entities[0]->Render(batch);
            if (m_entities[1]->is_alive) {
                m_entities[1]->Render(batch);
            }
        }

        void UnleashTheBeast()
        {
            m_entities[1]->is_alive = true;
            Vec2f player_direction = Vec2f(1.0f, 0.0f);
            player_direction =  player_direction.Rotated(m_entities[0]->orient).Normalized() * (- 700.0f);
            m_entities[1]->pos = player_direction + m_entities[0]->pos;
        }
        void PushEntity(std::shared_ptr<cEntity> p_e)
        { m_entities.push_back(p_e); }

        cEntity& GetEntity(int i)
        { return *m_entities[i]; }
    private:
        std::vector<std::shared_ptr<cEntity> > m_entities;
        int mn_collisions;
        bool has_played;
};

#endif // CENTITYMANAGER_H
