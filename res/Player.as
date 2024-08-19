
// The script is unprepared, some functions need to be added/implemented
// The public entity attributes "currentanim" and "drawsize" need to be accessible

void _construct(Entity& self) {
    self.setSolid();
    self.currentanim = "idled";
}

void _draw(Entity& self) {
    //Implement raylib drawRectangle function
}

void _update(Entity& self) {

    Vec2 vel(0, 0);
    const float speed = 5;

    //Raylib key functions and parameters need to be registered too

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

    // Somehow add this idk
    drawSize.at(0) = IsKeyDown(KEY_A)?-1:1;
    drawSize.at(1) = IsKeyDown(KEY_S)?-1:1;

    self.move(vel);
    self.orderByY();

}

void _init(Entity& self) {
    send2any(self,"NPC","Sample Message", self.getDelta());
}