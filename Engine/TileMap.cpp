//
// Created by blenk on 28/03/24.
//

#include <fstream>

#include "TileMap.h"
#include "App.h"

using std::ifstream;

namespace Engine {

    bool operator<(const tile& a, const tile& b) {
        return a.depth<b.depth;
    }

    void TileMap::Load() {
        ifstream stream;
        stream.open(path);
        while(!stream.eof()) {
            tile t;
            stream >> t.n >> t.pos.at(0) >> t.pos.at(1) >> t.depth;
            if(yordered) t.depth = (t.pos.at(1)+1)*tiledim[1] + t.depth*App::getWindowDimensions()[1];
            tiles.insert(t);
        }
    }

    void TileMap::Free() {
        tiles.clear();
    }

    void TileMap::update(const Rect & view) {

        for(const auto& t:tiles) {
            Rect tilerect{t.pos[0]*tiledim[0],t.pos[1]*tiledim[1],tiledim[0],tiledim[1]};
            if(tilerect.isColliding(view)) tiles2draw.insert(t);
        }

    }

    unordered_map<string, TileMap*> TileMapContainer::tilemaps{};

    void TileMapContainer::freeTileMaps() {
        for(const auto& t: tilemaps) delete t.second;
    }
} // engine