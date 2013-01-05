#ifndef STARTSTATE_H
#define STARTSTATE_H

#include "STATE_iGameState.hpp"
#include "GFX_GfxHelper.hpp"
#include "GFX_cTextureRegistry.hpp"
//
/*temp*/#include <iostream>

namespace CORE
{
    class cGame;
    class Input;
}

//static STATE::iGameState* CreateInstance() {}

class StartState : public STATE::iGameState
{
    public:
        StartState() {}
        virtual ~StartState() {}

        static STATE::iGameState* CreateInstance() { return new StartState; }
        virtual STATE::iGameState* Clone(){ return new StartState; } // Ideally this function should return a copy, not a blank instance

        bool OnEnter() {}
        bool OnExit() {}
        void Pause() {}
        void Resume() {}

        void HandleInput(CORE::cGame* game)
        {
            if (game->GetInput().GetKeyState(HAR_SPACE)) {
                game->GetStateManager().PushState(game->state_factory.CreateObject("play"));
            } else if (game->GetInput().GetKeyState(HAR_ESCAPE)) {
                game->EndGame();
            }
        }
        void Update(CORE::cGame* game, float delta)
        {
            HandleInput(game);
        }

        void Render(CORE::cGame* game, float percent_tick) {
            glLoadIdentity();

            cTextureWrapper& c = Art("start");
            GFX::ImmediateRenderTexturePos2Dim2(Art("start"), -250.0f, -250.0f, 500.0f, 500.0f);
        }

        void HandleInput() {}
    private:
};

#endif // STARTSTATE_H
