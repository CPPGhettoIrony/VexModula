//
// Created by blenk on 21/03/24.
//

#include "Sprites.h"

using Engine::Sprite, Engine::SpriteContainer;

namespace Game {

    void createSprites() {

        // Player Sprite creation

        auto* sprite = new Sprite("res/demosheet.png");

        sprite->getMap()["idleu"].setDimensions({36, 52});
        sprite->getMap()["idled"].setDimensions({36, 52});
        sprite->getMap()["idlel"].setDimensions({36, 52});
        sprite->getMap()["idler"].setDimensions({36, 52});

        sprite->getMap()["idled"].push_back({14, 10});
        sprite->getMap()["idlel"].push_back({14, 76});
        sprite->getMap()["idler"].push_back({14, 140});
        sprite->getMap()["idleu"].push_back({14, 204});

        sprite->getMap()["walkd"].setDimensions({36, 52});
        sprite->getMap()["walkl"].setDimensions({36, 52});
        sprite->getMap()["walkr"].setDimensions({36, 52});
        sprite->getMap()["walku"].setDimensions({36, 52});

        sprite->getMap()["walkd"].push_back({14, 10});
        sprite->getMap()["walkd"].push_back({78, 10});
        sprite->getMap()["walkd"].push_back({142, 10});
        sprite->getMap()["walkd"].push_back({206, 10});

        sprite->getMap()["walkl"].push_back({14, 76});
        sprite->getMap()["walkl"].push_back({78, 76});
        sprite->getMap()["walkl"].push_back({142, 76});
        sprite->getMap()["walkl"].push_back({206, 76});

        sprite->getMap()["walkr"].push_back({14, 140});
        sprite->getMap()["walkr"].push_back({78, 140});
        sprite->getMap()["walkr"].push_back({142, 140});
        sprite->getMap()["walkr"].push_back({206, 140});

        sprite->getMap()["walku"].push_back({14, 204});
        sprite->getMap()["walku"].push_back({78, 204});
        sprite->getMap()["walku"].push_back({142, 204});
        sprite->getMap()["walku"].push_back({206, 204});

        // Goomba sprite creation

        auto* goomba = new Sprite("res/goomba.png");

        goomba->getMap()["idle"].setDimensions({22,22});

        goomba->getMap()["idle"].push_back({0,0});
        goomba->getMap()["idle"].push_back({22,0});
        goomba->getMap()["idle"].push_back({44,0});
        goomba->getMap()["idle"].push_back({88,0});


        // Tileset sprite creation

        auto* tileset = new Sprite("res/tileset.png");

        tileset->getMap()["tileset"].setDimensions({34,34});

        for(size_t j=0; j<34*6; j+=34)
            for(size_t i=0; i<340; i+=34)
                tileset->getMap()["tileset"].push_back({(float)i,(float)j});


        // We add the sprites to the container, so entities can access to it, this way they get loaded and freed from GPU

        SpriteContainer::addSprite("Player",sprite);
        SpriteContainer::addSprite("NPC",goomba);
        SpriteContainer::addSprite("tileset0",tileset);
    }

} // Game