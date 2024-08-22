class NPC {

    Entity@ self;

    void construct(Entity& ent) {

        @self = @ent;

        self.setSprite(getSprite("NPC"));
        self.setDimensions(Vec2(22,22));
        self.setCurrentAnim("idle");
        self.setSolid();

    }

    void collision(Entity& ent) {self.Collide(ent);}

    void update() {self.orderByY(0);}

}