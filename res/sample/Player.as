
// The script is unprepared, some functions need to be added/implemented

class Player {

    Entity@ self;

    void construct(Entity& ent) {

        @self = @ent;

        self.setSprite(getSprite("Player"));
        self.setDimensions(Vec2(32,30));
        self.setCurrentAnim("idled");
        self.setSolid();

    }

    void update() {

        Vec2 vel(0, 0);
        const float speed = 5;

        //Raylib keys must be registered

        if (IsKeyDown(262)) {
            vel.at(0) = speed;
            self.setCurrentAnim("walkr");
        }

        if (IsKeyDown(263)) {
            vel.at(0) = -speed;
            self.setCurrentAnim("walkl");
        }

        if (IsKeyDown(265)) {
            vel.at(1) = -speed;
            self.setCurrentAnim("walku");
        }

        if (IsKeyDown(264)) {
            vel.at(1) = speed;
            self.setCurrentAnim("walkd");
        }

        if (IsKeyReleased(262)) self.setCurrentAnim("idler");
        if (IsKeyReleased(263)) self.setCurrentAnim("idlel");
        if (IsKeyReleased(265)) self.setCurrentAnim("idleu");
        if (IsKeyReleased(264)) self.setCurrentAnim("idled");

        self.setDrawSize(Vec2(IsKeyDown(65)?-1:1, IsKeyDown(83)?-1:1));

        self.move(vel);
        self.orderByY(0);

    }

    //TODO : IMPLEMENT Message system

}