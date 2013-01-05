#ifndef SOUNDREGISTRY_H
#define SOUNDREGISTRY_H

#include <SDL2/SDL_mixer.h>

class SoundRegistry
    {
    public:
        static void Init()
        {
            nom = Mix_LoadWAV("sounds/nommy.wav");
            beast = Mix_LoadWAV("sounds/enemy.wav");
            swim = Mix_LoadWAV("sounds/glide.wav");
            gameover = Mix_LoadWAV("sounds/gameover.wav");
        }
        static void Destroy()
        {
            Mix_FreeChunk( nom );
            Mix_FreeChunk( beast );
            Mix_FreeChunk( swim );
            Mix_FreeChunk( gameover );
        }
        static Mix_Chunk* nom;
        static Mix_Chunk* beast;
        static Mix_Chunk* swim;
        static Mix_Chunk* gameover;
    };
#endif // SOUNDREGISTRY_H
