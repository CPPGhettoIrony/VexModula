//
// Created by blenk on 20/02/24.
//

#ifndef NOWHEREFIGHTERS_ENTITY_H
#define NOWHEREFIGHTERS_ENTITY_H

#include <string>
#include <sstream>

#include "Sprite.h"

using std::string, std::stringstream;

namespace Engine {

    class Entity {
        Sprite* spr;
        float depth;
        Rect collisionRect;
        Vec2 initpos,pos,delta;
        bool solid;

        size_t frame, counter;

        string name;

        SETCREF()

    protected:

        string currentAnim;
        Vec2 drawSize;

    public:

        explicit Entity(const string& n, Sprite* s, const Vec2& d, const Vec2& p, float dp=.0):
            name(n), initpos(p), spr(s), pos(p), frame(0), counter(0), solid(false), depth(dp), drawSize{1,1}, SETREFCOUNT() {
            collisionRect = Rect{pos[0]-d[0]/2,pos[1],d[0],d[1]};
        }

        void setSolid() {solid = true;}
        [[nodiscard]] bool isSolid() const {return solid;}
        //this function will be called once on the constructors of children entities to permanently set themselves as solid

        void move(const Vec2&);
        void setPos(const Vec2&);

        void setCurrentAnim(const string& n) {currentAnim = n;}

        [[nodiscard]] const Vec2& getPos() const {return pos;}
        [[nodiscard]] const Vec2& getDelta() const {return delta;}
        [[nodiscard]] const Vec2& getInitPos() const {return initpos;}
        [[nodiscard]] const Rect& getCollisionRect() const {return collisionRect;}

        [[nodiscard]] Sprite* getSprite() const {return spr;}

        [[nodiscard]] const string& getName() const {return name;}

        [[nodiscard]] float getDepth() const {return depth;}
        void setDepth(float f) {depth = f;}
        void orderByY(int layer=0);

        virtual void draw(Rect& view);
        virtual void update() {}
        virtual void init() {}
        virtual void collision(Entity&) {}
        virtual void wallcollision(Rect&);
        virtual void exitView() {}
        virtual void enterView() {}
        virtual void receive(Entity*, string&, stringstream&) {}

        [[nodiscard]] bool isColliding(const Rect& R) const {return collisionRect.isColliding(R);}

        virtual ~Entity() = default;

    };

    inline void Entity::move(const Vec2& vec) {
        delta = vec;
        pos += vec;
        collisionRect += vec;
    }

    inline void Entity::setPos(const Vec2 & p) {
        delta = Vec2(p - pos);
        pos = p;
        collisionRect += delta;
    }

    struct layeredEntity {
        pair<Entity*,float> elements;
        layeredEntity(Entity* e, float d): elements(e,d) {}
    };

    bool operator<(const layeredEntity& a, const layeredEntity& b);

} // Engine

#endif //NOWHEREFIGHTERS_ENTITY_H
