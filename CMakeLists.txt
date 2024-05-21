cmake_minimum_required(VERSION 3.27)
project(nowherefighters)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_VERSION 4.5)
find_package(raylib ${RAYLIB_VERSION} REQUIRED) # QUIET or REQUIRED

add_executable(${PROJECT_NAME} main.cpp
        Engine/Entity.cpp
        Engine/Entity.h
        Engine/Vectors.cpp
        Engine/Vectors.h
        Engine/Sprite.cpp
        Engine/Sprite.h
        Engine/AnimatedSet.cpp
        Engine/AnimatedSet.h
        Engine/Room.cpp
        Engine/Room.h
        Game/Player.cpp
        Game/Player.h
        Game/Rooms.cpp
        Game/Rooms.h
        Engine/App.cpp
        Engine/App.h
        Game/Sprites.cpp
        Game/Sprites.h
        Game/NPC.cpp
        Game/NPC.h
        Engine/TileMap.cpp
        Engine/TileMap.h
        Game/TileMaps.cpp
        Game/TileMaps.h
        Engine/Mail.cpp
        Engine/Mail.h)
target_link_libraries(${PROJECT_NAME} raylib)