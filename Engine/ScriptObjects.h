//
// Created by blenk on 8/15/24.
//

#ifndef SCRIPTOBJECTS_H
#define SCRIPTOBJECTS_H

#define SETCREF() \
            friend ScriptWrapper;                                   \
                                                                \
            unsigned long refCount;                                 \
                                                                \
            void addRef() { ++refCount; }                           \
            void release() { if (--refCount == 0) delete this; }    \


#define SETREFCOUNT() refCount(1)

#endif //SCRIPTOBJECTS_H
