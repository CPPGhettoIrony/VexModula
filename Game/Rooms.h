//
// Created by blenk on 20/03/24.
//

#ifndef NOWHEREFIGHTERS_ROOMS_H
#define NOWHEREFIGHTERS_ROOMS_H

#include "../Engine/Room.h"
#include "Rooms.h"

using Engine::Room, Engine::Rect;

namespace Game {

    class TestRoom : public Engine::Room  {
    public:
        explicit TestRoom(const Engine::Rect& r): Engine::Room(r) {}

        void draw() override;
        void update() override;

    };

    void buildRoom1(Room* r);
    void buildRoom2(Room* r);

} // Game

#endif //NOWHEREFIGHTERS_ROOMS_H
