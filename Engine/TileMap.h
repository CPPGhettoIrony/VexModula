//
// Created by blenk on 28/03/24.
//

#ifndef NOWHEREFIGHTERS_TILEMAP_H
#define NOWHEREFIGHTERS_TILEMAP_H


#include <set>
#include "Sprite.h"

using std::unordered_multiset, std::multiset;

namespace Engine {

    struct tile {
        size_t n;
        float depth;
        Vec2 pos;
        explicit tile(const Vec2& p = Vec2{}, size_t i=0, float d=0): n(i), depth(d), pos(p) {}
    };

    bool operator<(const tile& a, const tile& b);

    class TileMap {

        Vec2 tiledim;
        Sprite* tileset;
        multiset<tile> tiles;
        multiset<tile> tiles2draw;
        string path;
        bool yordered;

    public:

        explicit TileMap(const string& spr, const string& map, const Vec2& d, bool y = false):
            tileset(SpriteContainer::getSprite(spr)), path(map), tiledim(d), yordered(y) {}

        ~TileMap() {if(!isLoaded()) tileset->Free();}

        [[nodiscard]] const Vec2& getDimensions() const {return tiledim;}

        void Load();
        void Free();
        [[nodiscard]] bool isLoaded() const {return tileset->isLoaded();}

        void update(const Rect& view);
        void postupdate() {tiles2draw.clear();}

        [[nodiscard]] const multiset<tile>& getDrawableTiles() const {return tiles2draw;}
        Sprite* getTileSet() const {return tileset;}

    };

    class TileMapContainer {
        static unordered_map<string, TileMap*> tilemaps;
    public:

        static void addTileMap(const string& name, TileMap* tlm) {
            tilemaps.insert(make_pair(name,tlm));
        }

        static TileMap* getTileMap(const string& name) {
            return tilemaps.at(name);
        }

        static void freeTileMaps();

    };

} // engine

#endif //NOWHEREFIGHTERS_TILEMAP_H
