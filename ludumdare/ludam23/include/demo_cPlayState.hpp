#ifndef DEMO_CPLAYSTATE_H
#define DEMO_CPLAYSTATE_H

#include "STATE_iGameState.hpp"
#include "GFX_G2D_cSpriteBatch.hpp"
#include "cEntityManager.hpp"
#include "cSuckyCam.hpp"
//
/*temp*/#include <iostream>

namespace CORE
{
    class cGame;
    class Input;
}

//static STATE::iGameState* CreateInstance() {}

class cPlayState : public STATE::iGameState
{
    public:
        cPlayState();
        virtual ~cPlayState();

        static STATE::iGameState* CreateInstance();
        virtual STATE::iGameState* Clone(); // Ideally this function should return a copy, not a blank instance

        bool OnEnter();
        bool OnExit();
        void Pause();
        void Resume();

        void HandleInput(CORE::cGame* game);
        void Update(CORE::cGame* game, float delta);

        void Render(CORE::cGame* game, float percent_tick);

        void HandleInput();
    private:
        GFX::G2D::cSpriteBatch m_batch;
        cEntityManager m_entity_manager;
        cSuckyCam m_cam;
};

#endif // DEMO_CPLAYSTATE_H
