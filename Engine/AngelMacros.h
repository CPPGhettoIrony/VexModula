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
            void release() { if (--refCount == 0) delete this; }


#define SETREFCOUNT() refCount(1)

#define REGISTERCREF(engine, obj) \
        engine->RegisterObjectBehaviour(obj, asBEHAVE_ADDREF, "void f()", asMETHOD(Vec2, addRef), asCALL_THISCALL); \
        engine->RegisterObjectBehaviour(obj, asBEHAVE_RELEASE, "void f()", asMETHOD(Vec2, release), asCALL_THISCALL);

#endif //SCRIPTOBJECTS_H
