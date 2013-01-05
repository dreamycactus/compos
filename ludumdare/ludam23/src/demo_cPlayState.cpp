#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_mixer.h>
#include "demo_cPlayState.hpp"
#include "CORE_cGame.hpp"
#include "MATH_Random.hpp"
#include "GFX_cImage.hpp"
#include "GFX_cTexture.hpp"
#include "GFX_G2D_cTextureRegion.hpp"
#include "GFX_G2D_cSpriteBatch.hpp"
#include "GFX_G2D_cAnimation.hpp"
#include "GFX_cTextureRegistry.hpp"
#include "SoundRegistry.hpp"
#include "GFX_GfxHelper.hpp"

#include "cEntFlea.hpp"
#include "cEntNommy.hpp"
#include "cBubble.hpp"
#include "cEntBignom.hpp"


    #include <iostream>
    using namespace std;

#define PLAYER m_entity_manager.GetEntity(0)

using namespace GFX;
using namespace GFX::G2D;
using namespace MATH;

cPlayState::cPlayState()
{

}
cPlayState::~cPlayState() {}

STATE::iGameState* cPlayState::CreateInstance()
{
    return new cPlayState;
}
STATE::iGameState* cPlayState::Clone()
{
    return new cPlayState;
}

bool cPlayState::OnEnter()
{
    m_cam.scale= 2.0f;



    std::shared_ptr<cEntFlea> p(new cEntFlea());
    p->Init();
    m_entity_manager.PushEntity(p);

    std::shared_ptr<cEntBignom> b(new cEntBignom());
    b->Init();
    m_entity_manager.PushEntity(b);

    cEntity::SetEntityManager(&m_entity_manager);

    unsigned int i;

    InitRandSeed();
    for (i=0; i<1000; ++i){
        m_entity_manager.PushEntity(std::shared_ptr<cEntity>(new cEntNommy(RandFloat(-5000.0f, 5000.0f), RandFloat(-5000.0f, 5000.0f))));
    }
    for (i=0; i<1000; ++i){
        m_entity_manager.PushEntity(std::shared_ptr<cEntity>(new cBubble(RandFloat(-5000.0f, 5000.0f), RandFloat(-5000.0f, 5000.0f))));
    }

//    static cImage img("art/pixelmap.png");
//    std::cout << "starting\n";
//    for (int j=0; j<img.GetHeight(); ++j) {
//        for (int i=0; i<img.GetWidth(); ++i) {
//            std::cout << std::hex << ((img.GetPixel(i, j)& 0xffffff00) >> 8) << ", ";
//        }
//        std::cout << "\n";
//    }

//    snd = Mix_LoadWAV( "sounds/explo1.wav" );
//    if (snd == 0) std::cout << "BADDDD";
//    Mix_PlayChannelTimed( -1, snd, 1, 400);

    return true;
}
bool cPlayState::OnExit()
{
//    Mix_FreeChunk(snd);
}
void cPlayState::Pause() {}
void cPlayState::Resume() {}


void cPlayState::HandleInput(CORE::cGame* game)
{
    if (game->GetInput().GetKeyState(HAR_LEFT)) {
        PLAYER.ang_vel -= 0.1f;
    }
    if (game->GetInput().GetKeyState(HAR_RIGHT)) {
        PLAYER.ang_vel += 0.1f;
    }
    if (game->GetInput().OnKeyDown(HAR_SPACE)) {
        static_cast<cEntFlea&>(PLAYER).Thrust();
    }
    if (game->GetInput().GetKeyState(HAR_DOWN)) {
        glTranslatef(0.0f, PLAYER.pos.y, 0.0f);
    }

    if (game->GetInput().GetKeyState(HAR_ESCAPE)) game->EndGame();
}


void cPlayState::Update(CORE::cGame* game, float delta)
{
    m_cam.width = game->GetSDLState()->window_w;
    m_cam.height = game->GetSDLState()->window_h;
    HandleInput(game);
    m_entity_manager.Update();
    if (!PLAYER.is_alive) {
        Mix_PlayChannel(-1, SoundRegistry::gameover, 0);
        game->GetStateManager().PopState();
    }
}


void cPlayState::Render(CORE::cGame* game, float percent_tick)
{
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 0.0);

    m_cam.pos = -PLAYER.pos-PLAYER.dim/2.0f;
    m_cam.SetMatricies();
//    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glEnable(GL_ALPHA_TEST) ;
    glAlphaFunc(GL_GREATER, 0.1f);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const float half_w = 200.0f + (m_cam.width / m_cam.scale) / 2.0f;
    const float half_h = 200.0f + (m_cam.height / m_cam.scale) / 2.0f;

//    cTextureRegion r(Art("sea"), PLAYER.pos.x-half_w, PLAYER.pos.y-half_h, PLAYER.pos.x+half_w, PLAYER.pos.y+half_h);
    ImmediateRenderTexturePos2Dim2(Art("sea"), -25000.0f, -25000.0f, 50000, 50000);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    m_batch.Begin();
        m_entity_manager.Render(m_cam, m_batch);
    m_batch.End();



//    glTranslatef(0.0f, -0.01f, 0.0f);
//    glRotatef(0.1, 1.0, 1.0, 1.0);
}
