//
// Created by blenk on 21/03/24.
//

#include "NPC.h"

#include <iostream>
using std::cout;

namespace Game {

    void NPC::update() {
        orderByY();
    }

    void NPC::receive(Entity *sender, string &header, stringstream &data) {
        cout << "Header: " << header << " | Data: " << data.str() << " | Playerpos: " << sender->getPos() << '\n';
    }

} // Game