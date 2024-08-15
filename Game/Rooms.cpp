//
// Created by blenk on 20/03/24.
//

#include "Player.h"
#include "NPC.h"
#include "Rooms.h"

#include "../Engine/TileMap.h"

using Engine::Vec2;

namespace Game {

    void TestRoom::draw() {

        Room::draw();

        for(auto& i : getWallsWithinView())
            DrawRectangleLines((*i)[0]-view[0],(*i)[1]-view[1],(*i)[2],(*i)[3],GREEN);
    }

    void TestRoom::update() {

        Room::update();

        if(getEntities().find("Player") != getEntities().end())
            viewFollow(getEntityByName("Player"));
    }

    void buildRoom1(Room* testRoom) {

        Engine::Rect* rects[] = {
                new Rect{200,300,600,20},
                new Rect{500,150,10,500},
                new Rect{200,500,500,30},
                new Rect{0,17,34*3,34*2.5+17}
        };

        testRoom->getWalls().insert(rects[0]);
        testRoom->getWalls().insert(rects[1]);
        testRoom->getWalls().insert(rects[2]);
        testRoom->getWalls().insert(rects[3]);

        auto* player = new Player(Vec2{60, 30});
        testRoom->addEntity(player);

        auto* goomba = new NPC(Vec2{200,200});
        testRoom->addEntity(goomba);

        testRoom->setTileMap(Engine::TileMapContainer::getTileMap("tilemap0"));
    }

    void buildRoom2(Room* testRoom) {
        auto* player = new Player(Vec2{100, 300});

        Engine::Rect* rects[] = {
                new Rect{300,300,20,600},
                new Rect{-100,150,100,50},
                new Rect{-100,500,50,300},
        };

        testRoom->getWalls().insert(rects[0]);
        testRoom->getWalls().insert(rects[1]);
        testRoom->getWalls().insert(rects[2]);
        testRoom->addEntity(player);
    }

} // Game