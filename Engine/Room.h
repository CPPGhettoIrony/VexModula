//
// Created by blenk on 2/03/24.
//

#ifndef NOWHEREFIGHTERS_ROOM_H
#define NOWHEREFIGHTERS_ROOM_H

#include <unordered_set>
#include <set>

#include "Entity.h"
#include "TileMap.h"

using std::unordered_set, std::multiset, std::pair,std::unordered_multimap;

// TODO:
//      Add pause states and GUI

namespace Engine {

    class Room {

        unordered_multimap<string , Entity *> entities;
        unordered_set<Rect *> walls;

        unordered_set<Sprite*> sprites;

        unordered_set<Entity *> activeEntities;
        unordered_set<Rect *> activeWalls;
        multiset<layeredEntity> layeredEntities;

        TileMap* tilemap;

        bool loaded;

        void processView();

    protected:
        Rect view;

    public:

        explicit Room(const Rect &v) : view(v), tilemap(nullptr), loaded(false) {}
        ~Room() {if(loaded) Free();}

        void setTileMap(TileMap* t) {tilemap = t; sprites.insert(t->getTileSet());}

        void Load() {
            SpriteContainer::loadSprites(sprites);
            if(tilemap) tilemap->Load();
            loaded = true;
        }

        void Free();

        void addEntity(Entity* e)    {entities.insert(make_pair(e->getName(),e)); sprites.insert(e->getSprite());}
        void removeEntity(Entity* e);

        const Rect& getView() const {return view;}

        unordered_multimap<string,Entity *> &getEntities() { return entities; }
        [[nodiscard]] const unordered_multimap<string,Entity *> &getEntities() const { return entities; }

        unordered_set<Rect *> &getWalls() { return walls; }
        [[nodiscard]] const unordered_set<Rect *> &getWalls() const { return walls; }

        unordered_set<Entity *> &getEntitiesWithinView() { return activeEntities; }
        [[nodiscard]] const unordered_set<Entity *> &getEntitiesWithinView() const { return activeEntities; }

        unordered_set<Rect *> &getWallsWithinView() { return activeWalls; }
        [[nodiscard]] const unordered_set<Rect *> &getWallsWithinView() const { return activeWalls; }

        unordered_set<Entity *> getEntitiesByName(const string& s);
        Entity* getEntityByName(const string& s) {
            if(entities.find(s) == entities.end()) return nullptr;
            return entities.find(s)->second;
        }

        void viewFollow(Entity*);

        virtual void draw();
        virtual void update();
        virtual void init();

    };

}

#endif //NOWHEREFIGHTERS_ROOM_H
