//
// Created by blenk on 20/02/24.
//

#include "Entity.h"
#include "App.h"

namespace Engine {

    void Entity::setDimensions(const Vec2 &d) {
        collisionRect.at(0) = pos[0]-d[0]/2;
        collisionRect.at(1) = pos[1];
        collisionRect.at(2) = d[0];
        collisionRect.at(3) = d[1];
    }

    void Entity::orderByY(int layer) {
        setDepth(getPos()[1]+getSprite()->getMap()[currentAnim].getDimensions()[1]+(float)layer*App::getWindowDimensions()[1]);
    }

    void Entity::draw(Rect& view) {
        Animation anim = spr->getMap().at(currentAnim);

        float width = anim.getDimensions()[0];
        Vec2 p{pos[0] - width / 2, pos[1]}; p -= view;
        spr->playAnimation(currentAnim,p,5,frame,counter, drawSize);
    }

    bool operator<(const layeredEntity& a, const layeredEntity& b) {
        return a.elements.second<b.elements.second;
    }

} // Engine