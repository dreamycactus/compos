#ifndef CTEXTUREREGISTRY_H
#define CTEXTUREREGISTRY_H

#include <unordered_map>
#include <string>
#include "GFX_cTexture.hpp"
#include "GFX_G2D_cTextureRegion.hpp"

namespace GFX
{
    using namespace GFX::G2D;

    class cTextureRegistry
    {
    public:
        cTextureRegistry() {}
        virtual ~cTextureRegistry() {}

        static void Init();
        static void RegisterTexture(std::string str_key, const cTextureWrapper& tex);
        static cTextureWrapper& GetTexture(std::string str_key);

        static std::unordered_map<std::string, cTextureWrapper> textures_map;

    };
    inline void cTextureRegistry::RegisterTexture(std::string str_key, const cTextureWrapper& tex)
    { textures_map.insert(std::pair<std::string, cTextureWrapper>(str_key, tex)); }

    inline cTextureWrapper& cTextureRegistry::GetTexture(std::string str_key)
    { return textures_map[str_key]; }

    inline void cTextureRegistry::Init()
    {
        cTexture tiles_e = cTexture("art/tiles_e.png"); tiles_e.RegisterGL();
        RegisterTexture("flea0", cTextureRegion(tiles_e, 0, 0, 128, 128));
        RegisterTexture("flea1", cTextureRegion(tiles_e, 128, 0, 128, 128));
        RegisterTexture("flea2", cTextureRegion(tiles_e, 256, 0, 128, 128));
        RegisterTexture("flea_s0", cTextureRegion(tiles_e, 384, 0, 128, 128));
        RegisterTexture("flea_s1", cTextureRegion(tiles_e, 512, 0, 128, 128));
        RegisterTexture("big0", cTextureRegion(tiles_e, 0, 196, 128, 128));
        RegisterTexture("big1", cTextureRegion(tiles_e, 128, 196, 128, 128));
        RegisterTexture("big2", cTextureRegion(tiles_e, 256, 196, 128, 128));
        RegisterTexture("nommy", cTextureRegion(tiles_e, 0, 128, 64, 64));
        RegisterTexture("bubble", cTextureRegion(tiles_e, 0, 320, 64, 64));

        cTexture sea = cTexture("art/sea.png"); sea.RegisterGL();
        RegisterTexture("sea", cTextureRegion(sea));

        cTexture start = cTexture("art/start.png"); start.RegisterGL();
        RegisterTexture("start", cTextureRegion(start));
    }
}

#define Art(key) GFX::cTextureRegistry::GetTexture(key)

#endif // CTEXTUREREGISTRY_H
