//
// Created by blenk on 8/15/24.
//

#ifndef SCRIPTOBJECTS_H
#define SCRIPTOBJECTS_H

namespace Engine {

    class CRef {
        unsigned long refCount;
    public:
        CRef() : refCount(1) {}
        void addRef() { ++refCount; }
        void release() { if (--refCount == 0) delete this; }
    };

}



#endif //SCRIPTOBJECTS_H
