//
// Created by blenk on 28/03/24.
//

#include "TileMaps.h"
#include "../Engine/TileMap.h"

using Engine::TileMap, Engine::TileMapContainer;

namespace Game {

    void createTileMaps() {

        auto* tilemap0 = new TileMap("tileset0", "../res/tilemap0.txt", {34, 34}, true);

        TileMapContainer::addTileMap("tilemap0", tilemap0);

    }

} // Game