//
// Created by blenk on 21/03/24.
//

#include "Sprites.h"

using Engine::Sprite, Engine::SpriteContainer, Engine::Vec2;

namespace Game {

    void createSprites() {

        // Player Sprite creation

        auto* sprite = new Sprite("../res/demosheet.png");

        sprite->getMap()["idleu"].setDimensions(Vec2{36, 52});
        sprite->getMap()["idled"].setDimensions(Vec2{36, 52});
        sprite->getMap()["idlel"].setDimensions(Vec2{36, 52});
        sprite->getMap()["idler"].setDimensions(Vec2{36, 52});

        sprite->getMap()["idled"].push_back(Vec2{14, 10});
        sprite->getMap()["idlel"].push_back(Vec2{14, 76});
        sprite->getMap()["idler"].push_back(Vec2{14, 140});
        sprite->getMap()["idleu"].push_back(Vec2{14, 204});

        sprite->getMap()["walkd"].setDimensions(Vec2{36, 52});
        sprite->getMap()["walkl"].setDimensions(Vec2{36, 52});
        sprite->getMap()["walkr"].setDimensions(Vec2{36, 52});
        sprite->getMap()["walku"].setDimensions(Vec2{36, 52});

        sprite->getMap()["walkd"].push_back(Vec2{14, 10});
        sprite->getMap()["walkd"].push_back(Vec2{78, 10});
        sprite->getMap()["walkd"].push_back(Vec2{142, 10});
        sprite->getMap()["walkd"].push_back(Vec2{206, 10});

        sprite->getMap()["walkl"].push_back(Vec2{14, 76});
        sprite->getMap()["walkl"].push_back(Vec2{78, 76});
        sprite->getMap()["walkl"].push_back(Vec2{142, 76});
        sprite->getMap()["walkl"].push_back(Vec2{206, 76});

        sprite->getMap()["walkr"].push_back(Vec2{14, 140});
        sprite->getMap()["walkr"].push_back(Vec2{78, 140});
        sprite->getMap()["walkr"].push_back(Vec2{142, 140});
        sprite->getMap()["walkr"].push_back(Vec2{206, 140});

        sprite->getMap()["walku"].push_back(Vec2{14, 204});
        sprite->getMap()["walku"].push_back(Vec2{78, 204});
        sprite->getMap()["walku"].push_back(Vec2{142, 204});
        sprite->getMap()["walku"].push_back(Vec2{206, 204});

        // Goomba sprite creation

        auto* goomba = new Sprite("../res/goomba.png");

        goomba->getMap()["idle"].setDimensions(Vec2{22,22});

        goomba->getMap()["idle"].push_back(Vec2{0,0});
        goomba->getMap()["idle"].push_back(Vec2{22,0});
        goomba->getMap()["idle"].push_back(Vec2{44,0});
        goomba->getMap()["idle"].push_back(Vec2{88,0});


        // Tileset sprite creation

        auto* tileset = new Sprite("../res/tileset.png");

        tileset->getMap()["tileset"].setDimensions(Vec2{34,34});

        for(size_t j=0; j<34*6; j+=34)
            for(size_t i=0; i<340; i+=34)
                tileset->getMap()["tileset"].push_back(Vec2{(float)i,(float)j});


        // We add the sprites to the container, so entities can access to it, this way they get loaded and freed from GPU

        SpriteContainer::addSprite("Player",sprite);
        SpriteContainer::addSprite("NPC",goomba);
        SpriteContainer::addSprite("tileset0",tileset);
    }

} // Game