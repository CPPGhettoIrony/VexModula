//
// Created by blenk on 20/03/24.
//

#ifndef NOWHEREFIGHTERS_PLAYER_H
#define NOWHEREFIGHTERS_PLAYER_H

#include "../Engine/Entity.h"
#include "../Engine/Sprite.h"


using Engine::Entity, Engine::Sprite, Engine::Rect, Engine::Vec2, Engine::SpriteContainer;

namespace Game {

    class Player : public Entity {
    public:

        explicit Player(const Vec2& pos) : Entity("Player", SpriteContainer::getSprite("Player"), Vec2{32, 30}, pos) {
            setSolid();
            currentAnim = "idled";
        }

        void draw(const Rect&) override;
        void update() override;

        void init() override;

    };

} // Game

#endif //NOWHEREFIGHTERS_PLAYER_H
