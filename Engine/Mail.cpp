//
// Created by blenk on 30/03/24.
//

#include "Mail.h"

namespace Engine {

    queue<Message> Mail::messages{};
    Room* Mail::room = nullptr;

    void Mail::process() {

        while(!messages.empty()) {

            auto& message = messages.front();

            if(message.receiver)
                message.receiver->receive(message.sender,message.header,message.getData());
            else if(message.multicast && !message.receiverName.empty())
                for(auto e: room->getEntitiesByName(message.receiverName))
                    e->receive(message.sender,message.header,message.getData());
            else if(message.multicast && message.receiverName.empty())
                for(const auto& e: room->getEntities())
                    e.second->receive(message.sender,message.header,message.getData());
            else {
                auto receiver = room->getEntityByName(message.receiverName);
                if(receiver)
                    room->getEntityByName(message.receiverName)->receive(message.sender, message.header, message.getData());
            }

            messages.pop();
        }

    }

} // Engine