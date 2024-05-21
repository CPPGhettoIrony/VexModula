//
// Created by blenk on 21/02/24.
//

#ifndef NOWHEREFIGHTERS_SPRITE_H
#define NOWHEREFIGHTERS_SPRITE_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <raylib.h>

#include "AnimatedSet.h"
#include "Vectors.h"

using std::unordered_map, std::unordered_set, std::pair, std::string, std::vector, std::make_pair;

namespace Engine {

    class Animation: public vector<Vec2> {
        Vec2 dim;
    public:
        explicit Animation(const Vec2& d={}): vector(), dim(d) {}

        void setDimensions(const Vec2& vec) { dim = vec;}
        [[nodiscard]] const Vec2& getDimensions() const {return dim;}
    };

    class Sprite : public AnimatedSet<Animation,Vec2> {
        Texture2D texture;
        string path;
        bool is_loaded;
    public:
        explicit Sprite(const string& p): path(p), AnimatedSet(), is_loaded(false) {}

        void Load() {
            if(is_loaded) return;
            texture = LoadTexture(path.c_str());
            is_loaded = true;
        }

        void Free() {
            if(!is_loaded) return;
            UnloadTexture(texture);
            is_loaded = false;
        }

        bool isLoaded() const {return is_loaded;}

        void playAnimation(const string&, const Vec2&, size_t, size_t&, size_t&) const;
        void playAnimationFrame(const string&, const Vec2&, size_t) const;
    };

    typedef AnimatedSet<Animation,Vec2> HitboxSet;

    class SpriteContainer {
        static unordered_map<string, Sprite*> sprites;
        static unordered_set<Sprite*> loadedSprites;
    public:

        static void addSprite(const string& name, Sprite* spr) {
            sprites.insert(make_pair(name,spr));
        }

        static void loadSprites(const unordered_set<Sprite*>& );

        static Sprite* getSprite(const string& name) {
            return sprites.at(name);
        }

        static void freeSprites();

    };

    struct layeredSprite {
        pair<Sprite*,float> elements;
        layeredSprite(Sprite* s, float d): elements(s,d) {}
    };

    bool operator<(const layeredSprite& a, const layeredSprite& b);

}

#endif //NOWHEREFIGHTERS_SPRITE_H
