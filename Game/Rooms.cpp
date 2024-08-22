//
// Created by blenk on 20/03/24.
//

#include "Player.h"
#include "NPC.h"
#include "Rooms.h"

#include "../Engine/TileMap.h"
#include "../Script/ScriptObjects.h"
#include "../Script/ScriptWrapper.h"

using Engine::Vec2;

Engine::ScriptWrapper* SW;

namespace Game {

    void initScriptWrapper() {
        SW = new Engine::ScriptWrapper();
        SW->createModule("Player", {"../res/sample/Player.as"});
        SW->createModule("NPC", {"../res/sample/NPC.as"});
    }

    void deleteScriptWrapper() {
        delete SW;
    }

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

        auto* player = new Engine::ScriptEntity(SW,"Player", Vec2{60, 30});
        auto* goomba0 = new Engine::ScriptEntity(SW, "NPC", Vec2{200, 200});
        auto* goomba1 = new Engine::ScriptEntity(SW, "NPC", Vec2{100, 200});

        testRoom->addEntity(player);
        testRoom->addEntity(goomba0);
        testRoom->addEntity(goomba1);

        testRoom->setTileMap(Engine::TileMapContainer::getTileMap("tilemap0"));
    }

    void buildRoom2(Room* testRoom) {

        auto* player = new Engine::ScriptEntity(SW,"Player", Vec2{100, 300});
        auto* goomba = new Engine::ScriptEntity(SW, "NPC", Vec2{100, 100});

        Engine::Rect* rects[] = {
                new Rect{300,300,20,600},
                new Rect{-100,150,100,50},
                new Rect{-100,500,50,300},
        };

        testRoom->getWalls().insert(rects[0]);
        testRoom->getWalls().insert(rects[1]);
        testRoom->getWalls().insert(rects[2]);

        testRoom->addEntity(player);
        testRoom->addEntity(goomba);
    }

} // Game