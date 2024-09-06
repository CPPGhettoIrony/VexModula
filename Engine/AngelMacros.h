//
// Created by blenk on 8/15/24.
//

#ifndef SCRIPTOBJECTS_H
#define SCRIPTOBJECTS_H

#define SETCREF() \
            friend ScriptWrapper;                                               \
            unsigned long refCount;                                             \
            bool isReference;                                                   \
            void addRef() { ++refCount; }                                       \
            void release() { if (--refCount == 0 && isReference) delete this; } \
        public:                                                                 \
            void setReferenced() {isReference = true;}                          \
        private:

#define SETREFCOUNT() refCount(1), isReference(false)

#define RETURNFACTORY(x) {auto ret = new x; ret->setReferenced(); return ret;}

#define REGISTERCREF(engine, obj) \
        engine->RegisterObjectBehaviour(obj, asBEHAVE_ADDREF, "void f()", asMETHOD(Vec2, addRef), asCALL_THISCALL); \
        engine->RegisterObjectBehaviour(obj, asBEHAVE_RELEASE, "void f()", asMETHOD(Vec2, release), asCALL_THISCALL);

#endif //SCRIPTOBJECTS_H
