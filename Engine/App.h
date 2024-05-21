//
// Created by blenk on 20/03/24.
//

#ifndef NOWHEREFIGHTERS_APP_H
#define NOWHEREFIGHTERS_APP_H

#include "Room.h"
#include <raylib.h>

namespace Engine {

    typedef void(*roomCreationFunc)(Room*);
    typedef std::pair<Room*,roomCreationFunc> loadableRoom;

    class App {
        unordered_map<string,loadableRoom> rooms;
        string currentRoom;
        static Vec2 wdim;

        void loadRoom();
        void freeRoom();

    public:

        explicit App(const Vec2& wd) {wdim = wd;}
        ~App() {SpriteContainer::freeSprites(); TileMapContainer::freeTileMaps();}

        static const Vec2& getWindowDimensions() {return wdim;}
        const string& getCurrentRoomName() const {return currentRoom;}

        void addRoom(const string& name, Room* roomtype, roomCreationFunc rcf) {
            rooms.insert(make_pair(name,make_pair(roomtype,rcf)));
        }

        void changeRoom(const string& s = string());

        void update() {
            rooms.at(currentRoom).first->update();
        }

        void draw() {
            rooms.at(currentRoom).first->draw();
        }

    };

} // Engine

#endif //NOWHEREFIGHTERS_APP_H
