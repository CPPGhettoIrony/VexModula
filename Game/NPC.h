//
// Created by blenk on 21/03/24.
//

#ifndef NOWHEREFIGHTERS_NPC_H
#define NOWHEREFIGHTERS_NPC_H

#include "../Engine/Entity.h"
#include "../Engine/Sprite.h"

using Engine::Entity, Engine::Sprite, Engine::Rect, Engine::Vec2, Engine::SpriteContainer;

namespace Game {

    class NPC : public Entity{
    public:

        explicit NPC(const Vec2& pos): Entity("NPC",SpriteContainer::getSprite("NPC"),Vec2{22,22},pos) {
            setSolid();
            currentAnim = "idle";
        }

        void update() override;

        void receive(Entity* sender, const string& header, stringstream& data) override;

    };

} // Game

#endif //NOWHEREFIGHTERS_NPC_H
