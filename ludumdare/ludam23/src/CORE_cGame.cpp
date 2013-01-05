#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "CORE_cGame.hpp"
#include "STATE_iGameState.hpp"
#include "demo_cPlayState.hpp"
#include "StartState.hpp"


/*temp*/ #include <iostream>
         #include <cassert>
         #include "GFX_cTextureRegistry.hpp"
        using namespace std;

using namespace CORE;
using namespace STATE;

cGame::cGame()
: m_running(true)
, m_sdl_state(0)
{
}

cGame::~cGame()
{
    //dtor
}
#include <stdlib.h>
bool cGame::Initialise()
{
    if (!SDL_Init( SDL_INIT_EVERYTHING )){
        cout << "SOMETHING BAD HAPPENED IN SDL_INIT\n";
        return false;
    }

    m_running = true;
    // Setup SDL Window and Render
    m_sdl_state = new cSDLState(800, 720);
    m_sdl_state->SetGL();
    m_sdl_state->window = SDL_CreateWindow(m_sdl_state->window_title,
        m_sdl_state->window_x,
        m_sdl_state->window_y,
        m_sdl_state->window_w , m_sdl_state->window_h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    // Fullscreen?
    SDL_SetWindowFullscreen(m_sdl_state->window, m_sdl_state->is_fullscreen);
    // Renderer
    m_sdl_state->renderer = SDL_CreateRenderer(m_sdl_state->window,
                                    0, m_sdl_state->render_flags);
    // GL Context
    m_sdl_state->glctx = SDL_GL_CreateContext(m_sdl_state->window);
    cout <<"WHAT" << m_sdl_state->glctx << "WHAT";
    SDL_GL_MakeCurrent(m_sdl_state->window, m_sdl_state->glctx);

    SDL_GL_SetSwapInterval(1); // 1 for Vsync?

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    const float half_w = static_cast<float>(m_sdl_state->window_w) / 2.0f;
    const float half_h = static_cast<float>(m_sdl_state->window_h) / 2.0f;

    glOrtho(-half_w, half_w, half_h, -half_h, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective


    m_input.Initialise();

    if (!IMG_Init( IMG_INIT_PNG )){
        printf("IMG_Init: %s\n", IMG_GetError());
        return false;
    }

    if( Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, 2, 4096 ) == -1 ) {
        fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
        return false;
    }
//    if (!Mix_Init()){
//        printf("Mix_Init: %s\n", Mix_GetError());
//        return false;
//    }

    state_factory.RegisterClass("play", cPlayState::CreateInstance);
    state_factory.RegisterClass("start", StartState::CreateInstance);
    m_state_manager.PushState(state_factory.CreateObject("start"));

    cTextureRegistry::Init();
    SoundRegistry::Init();
    return true;
}

bool cGame::Terminate()
{
    if (m_sdl_state) {

        if (m_sdl_state->renderer) {
            SDL_DestroyRenderer(m_sdl_state->renderer);
        }
        if (m_sdl_state->glctx)    {
            SDL_GL_DeleteContext(m_sdl_state->glctx);
        }
        if (m_sdl_state->window)   {
            SDL_DestroyWindow(m_sdl_state->window);
        }
        SDL_free(m_sdl_state);
    }
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    return true;
}

void cGame::MainLoop()
{
    iGameState* state = 0;
    float delta = 0.0f, percent_tick = 0.0f; // Dummy vars for now; substitute timer values in later

    while (m_running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                EndGame();
            }
        }
        // Update Input-- set old keystates and current ones
        m_input.Update();

        // Game Loop
        state = m_state_manager.GetCurrent();
        /*DEBUG*/assert(state!=0);
        state->Update(this, delta);

        state = m_state_manager.GetCurrent();
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_MakeCurrent(m_sdl_state->window, m_sdl_state->glctx);
        state->Render(this, percent_tick);

        SDL_GL_SwapWindow(m_sdl_state->window);
        //SDL_RenderPresent(m_sdl_state->renderer); // Gets overwritten somehow by SwapWindow
    }
    m_state_manager.ClearAll();
}

void cGame::EndGame()
{
    m_running = false;
}

Input& cGame::GetInput()
{
    return m_input;
}
cGameStateManager& cGame::GetStateManager()
{
    return m_state_manager;
}


