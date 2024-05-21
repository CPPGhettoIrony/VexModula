//
// Created by blenk on 21/02/24.
//

#include "Sprite.h"

namespace Engine {

    unordered_map<string, Sprite*> SpriteContainer::sprites{};
    unordered_set<Sprite*> SpriteContainer::loadedSprites{};

    void SpriteContainer::loadSprites(const unordered_set<Sprite*>& spritelist) {

        if(loadedSprites.empty()){
            for(auto s: spritelist) {
                s->Load();
                loadedSprites.insert(s);
            }
            return;
        }

        vector<Sprite*> del;

        for(auto s: loadedSprites) {
            if(spritelist.find(s) == spritelist.end()) {
                s->Free();
                del.push_back(s);
            }
        }

        for(auto s: del) loadedSprites.erase(s);

        for(auto s: spritelist) {
            if(loadedSprites.find(s) == loadedSprites.end()) {
                s->Load();
                loadedSprites.insert(s);
            }
        }
        
    }

    void SpriteContainer::freeSprites() {
        for(const auto& s: sprites) delete s.second;
    }

    void Sprite::playAnimation(const string& name, const Vec2& pos, size_t duration, size_t& frame, size_t& counter) const {

        auto animation = frameMap.at(name);

        Vec2 vec{operator()(name, duration, frame, counter)};

        Rectangle rec;
        rec.width = animation.getDimensions()[0]; rec.height = animation.getDimensions()[1];
        rec.x = vec[0]; rec.y = vec[1];

        DrawTextureRec(texture,rec,pos.toRaylibVector(),WHITE);
    }

    void Sprite::playAnimationFrame(const string & name, const Vec2 & pos, size_t frame) const {

        auto animation = frameMap.at(name);

        Vec2 vec{operator[](name)[frame]};

        Rectangle rec;
        rec.width = animation.getDimensions()[0]; rec.height = animation.getDimensions()[1];
        rec.x = vec[0]; rec.y = vec[1];

        DrawTextureRec(texture,rec,pos.toRaylibVector(),WHITE);

    }

    bool operator<(const layeredSprite a, const layeredSprite& b) {
        return a.elements.second<b.elements.second;
    }

}