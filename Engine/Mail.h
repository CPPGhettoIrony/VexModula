//
// Created by blenk on 30/03/24.
//

#ifndef NOWHEREFIGHTERS_MAIL_H
#define NOWHEREFIGHTERS_MAIL_H

#include <sstream>
#include <queue>
#include "Room.h"

using std::stringstream, std::queue;

namespace Engine {

    struct Message{

    private:

        stringstream* data;

    public:

        Entity *sender, *receiver;
        string receiverName;
        bool multicast;
        string header;

        Message(Entity* s, Entity* r, const string& h, const string& rn, bool m):
            sender(s), receiver(r), header(h), receiverName(rn), multicast(m), data(new stringstream{}) {}

        Message(const Message& M):
            sender(M.sender), receiver(M.receiver), header(M.header), receiverName(M.receiverName), multicast(M.multicast), data(new stringstream{}) {
            (*data) << M.data->str();
        }

        ~Message() {delete data;}

        stringstream& getData() {return *data;}


    };

    class Mail {
        static queue<Message> messages;
        static Room* room;
    public:

        static void setRoom(Room* r) {room = r;}

        template <typename T>
        static void send(Entity *s, Entity *r, const string& h, const T& content);

        template <typename T>
        static void send2any(Entity* s, const string& r, const string& h, const T& content);

        template <typename T>
        static void send2type(Entity* s, const string& r, const string& h, const T& content);

        template <typename T>
        static void send2all(Entity* s, const string& h, const T& content);

        static void process();

        static void empty() {
            while(!messages.empty()) messages.pop();
        }

    };

    template<typename T>
    void Mail::send(Entity *s, Entity *r, const string &h, const T &content) {
        Message m(s,r,h,"",false);
        m.getData() << content;
        messages.push(m);
    }

    template <typename T>
    void Mail::send2any(Entity* s, const string& r, const string& h, const T& content) {
        Message m(s,nullptr,h,r,false);
        m.getData() << content;
        messages.push(m);
    }

    template <typename T>
    void Mail::send2type(Entity* s, const string& r, const string& h, const T& content) {
        Message m(s,nullptr,h,r,true);
        m.getData() << content;
        messages.push(m);
    }

    template <typename T>
    void Mail::send2all(Entity* s, const string& h, const T& content) {
        Message m(s,nullptr,h,string{},true);
        m.getData() << content;
        messages.push(m);
    }

} // Engine

#endif //NOWHEREFIGHTERS_MAIL_H
