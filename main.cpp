#include <iostream>
#include <raylib.h>

#include "Game/Player.h"
#include "Game/Rooms.h"
#include "Game/Sprites.h"
#include "Game/TileMaps.h"

#include "Engine/App.h"

int screenWidth = 1000;
int screenHeight = 750;

using Game::Player, Game::TestRoom, Engine::App, std::cout, std::endl;

int main()
{

    InitWindow(screenWidth, screenHeight, "Nowhere Fighters");
    SetTargetFPS(60);

    // Sprite creation function

    Game::createSprites();

    // Tilemap creation function

    Game::createTileMaps();

    // We declare a room type, testRoom is a derivative of the base class Room that follows the player and draws the wall hitboxes

    TestRoom testRoom({0,0,(float)screenWidth,(float)screenHeight});

    // We create the overall application class, adding two rooms that use testRoom as a room type and
    // two different functions, these functions create the entities and walls (and add them) to the room when it loads

    App Application({(float)screenWidth,(float)screenHeight});
    Application.addRoom("Room1",&testRoom,Game::buildRoom1);
    Application.addRoom("Room2",&testRoom,Game::buildRoom2);
    Application.changeRoom("Room1");

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        Application.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if(IsKeyPressed(KEY_R))
            Application.changeRoom((Application.getCurrentRoomName() == "Room1")?"Room2":"Room1");
            // Will switch between two rooms when the R key is pressed

        Application.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

