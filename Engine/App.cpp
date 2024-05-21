//
// Created by blenk on 20/03/24.
//

#include "App.h"

namespace Engine {

    Vec2 App::wdim{};

    void App::loadRoom() {
        Room* room = rooms.at(currentRoom).first;
        rooms.at(currentRoom).second(room);

        room->Load();
        room->init();
    }

    void App::freeRoom() {

        Room *room = rooms.at(currentRoom).first;

        room->Free();
    }

    void App::changeRoom(const string &s) {
        if(currentRoom == s) return;
        if(!currentRoom.empty())
            freeRoom();
        currentRoom = s;
        if(!currentRoom.empty())
            loadRoom();
    }
} // Engine