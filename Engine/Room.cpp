//
// Created by blenk on 2/03/24.
//

#include "Room.h"
#include "Mail.h"

#include <algorithm>
#include <sstream>
using std::stringstream;

namespace Engine {

    struct drawitem {

        Entity *e;
        const tile* s;
        enum type{NONE,ENTITY,TILE};
        type t;
        float depth;

        explicit drawitem(float d, Entity* a= nullptr, const tile* b=nullptr): depth(d), e(a), s(b) {
            if(!e && !s) t = NONE;
            else if(e) t = ENTITY;
            else if(s) t = TILE;
        }

    };

    bool operator<(const drawitem& a, const drawitem& b) {
        return a.depth < b.depth;
    }

    void Room::processView() {


        for(auto i : walls) {
            if (activeWalls.find(i) != activeWalls.end()) continue;
            if (i->isColliding(view)) activeWalls.insert(i);
        }

        {
            vector<Rect *> del;
            for (auto i: activeWalls)
                if (!i->isColliding(view)) del.push_back(i);
            for (auto i:del)
                activeWalls.erase(activeWalls.find(i));
        }

        for(auto i : entities) {
            if (activeEntities.find(i.second) != activeEntities.end()) continue;
            if (i.second->isColliding(view)) {
                activeEntities.insert(i.second);
                i.second->enterView();
            }
        }

        {
            vector<Entity *> del;
            for (auto i: activeEntities)
                if (!i->isColliding(view)) del.push_back(i);
            for (auto i:del) {
                i->exitView();
                activeEntities.erase(activeEntities.find(i));
            }
        }

    }

    void Room::update() {

        processView();

        for(auto i : activeEntities) {

            i->update();

            for(auto j : activeEntities) {
                if (i == j) continue;
                if (i->isColliding(j->getCollisionRect()))
                    i->collision(*j);
            }

            for(auto r : activeWalls) {
                if(i->isColliding(*r) && i->isSolid())
                   i->wallcollision(*r);
            }

        }

        Mail::process();

    }

    void Room::init() {

        Mail::setRoom(this);

        if(!activeEntities.empty()) activeEntities.clear();
        if(!activeWalls.empty())    activeWalls.clear();

        for(auto i : entities) {
            i.second->setPos(i.second->getInitPos());
            i.second->init();
        }

    }

    void Room::draw() {

        if(tilemap) tilemap->update(view);

        for(auto i : activeEntities) layeredEntities.insert(layeredEntity(i,i->getDepth()));

        if(tilemap) {

            multiset<drawitem> container;

            for(const auto& i: layeredEntities) container.insert(drawitem(i.elements.first->getDepth(),i.elements.first));
            for(const auto& i: tilemap->getDrawableTiles()) container.insert(drawitem(i.depth,nullptr,&i));

            for(const auto& i : container) {

                switch (i.t) {
                    case drawitem::NONE:
                        break;
                    case drawitem::ENTITY:
                        i.e->draw(view);
                        break;
                    case drawitem::TILE:
                        Vec2 pos;
                        pos.at(0) = i.s->pos[0]*tilemap->getDimensions()[0]-view[0];
                        pos.at(1) = i.s->pos[1]*tilemap->getDimensions()[1]-view[1];
                        tilemap->getTileSet()->playAnimationFrame("tileset",pos,i.s->n);
                        break;
                }

            }

        } else for(auto& i: layeredEntities) i.elements.first->draw(view);

        layeredEntities.clear();

        if(tilemap) tilemap->postupdate();

    }

    void Room::removeEntity(Entity *e) {

        for(auto i = entities.begin(); i != entities.end(); ++i)
            if(i->second == e) {
                entities.erase(i);
                sprites.erase(e->getSprite());
                //e->getSprite()->Free();
                delete e;
        }

    }

    unordered_set<Entity *> Room::getEntitiesByName(const string& n) {
        unordered_set<Entity *> ret;
        for(const auto& e:getEntities()) if(e.first == n) ret.insert(e.second);
        return ret;
    }

    void Room::viewFollow(Entity * e) {
        view.at(0) = e->getPos()[0] - view[2]/2;
        view.at(1) = e->getPos()[1] - view[3]/2 + e->getCollisionRect()[3]/2;
    }

    void Room::Free() {

        for(auto & e : entities) delete e.second;

        entities.clear();
        activeEntities.clear();
        sprites.clear();

        for(auto & w : walls) delete w;
        walls.clear();
        activeWalls.clear();

        if(tilemap) {
            tilemap->Free();
            tilemap = nullptr;
        }

        loaded = false;

        Mail::empty();

    }


}