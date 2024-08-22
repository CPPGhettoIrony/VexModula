//
// Created by blenk on 20/03/24.
//

#include "Player.h"
#include "../Engine/Mail.h"

using Engine::Mail;

namespace Game {


    void Player::update() {

        Engine::Vec2 vel{0, 0};
        const static float speed = 5;

        if (IsKeyDown(KEY_RIGHT)) {
            vel.at(0) = speed;
            currentAnim = "walkr";
        }

        if (IsKeyDown(KEY_LEFT)) {
            vel.at(0) = -speed;
            currentAnim = "walkl";
        }

        if (IsKeyDown(KEY_UP)) {
            vel.at(1) = -speed;
            currentAnim = "walku";
        }

        if (IsKeyDown(KEY_DOWN)) {
            vel.at(1) = speed;
            currentAnim = "walkd";
        }

        if (IsKeyReleased(KEY_RIGHT)) currentAnim = "idler";
        if (IsKeyReleased(KEY_LEFT))  currentAnim = "idlel";
        if (IsKeyReleased(KEY_UP))    currentAnim = "idleu";
        if (IsKeyReleased(KEY_DOWN))  currentAnim = "idled";

        drawSize.at(0) = IsKeyDown(KEY_A)?-1:1;
        drawSize.at(1) = IsKeyDown(KEY_S)?-1:1;

        move(vel);

        orderByY(0);
    }

    void Player::draw(Rect & view) {
        Entity::draw(view);
        DrawRectangleLines(getCollisionRect()[0]-view[0],getCollisionRect()[1]-view[1],getCollisionRect()[2],getCollisionRect()[3],BLUE);
    }

    void Player::init() {
        Entity::init();

        Mail::send2any(*this,"NPC","Sample Message", getDelta());

    }

} // Game