//
// Created by blenk on 13/08/24.
//

#include <iostream>
#include <raylib.h>

#include "../Engine/Exception.h"
#include "ScriptWrapper.h"
#include "ScriptObjects.h"

#include "../Engine/AngelMacros.h"
#include "angelscript/add_on/scriptbuilder/scriptbuilder.h"
#include "angelscript/add_on/scriptstdstring/scriptstdstring.h"

#include "angelscript/include/angelscript.h"

using std::cout, std::cerr, std::endl;

void MessageCallback(const asSMessageInfo *msg, void *param)
{
    string type = "ERROR";
    std::basic_ostream<char>* ostream = &cerr;

    if( msg->type == asMSGTYPE_WARNING ) {
        type = "WARN";
        ostream = &cout;
    } else if( msg->type == asMSGTYPE_INFORMATION ) {
        type = "INFO";
        ostream = &cout;
    }

    *ostream << '[' << type << "] " << msg->section << " (" << msg->row << ", " << msg->col << ") : " << msg->message << '\n';

}


template <typename T>
void print(T in) {cout << in;}

void printVec2(const Engine::Vec2& in) {cout << in;}
void printString(const string& in) {cout << in;}
void printFloat(float in) {cout << in;}
void printInt(int in) {cout << in;}
void printPtr(size_t in) {cout << in;}

void printBool(bool in) {
    if(in) cout << "true";
    else cout << "false";
}

void flush() {cout << endl;}

namespace Engine {

    ScriptWrapper::ScriptWrapper(): engine(asCreateScriptEngine()) {

        ctx = engine->CreateContext();

        engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

        RegisterStdString(engine);

        // Register Global basic functions
        {
            engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print<const string&>), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(bool)", asFUNCTION(print<bool>), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(float)", asFUNCTION(print<float>), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(int16)", asFUNCTION(print<int>), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(uint32)", asFUNCTION(print<size_t>), asCALL_CDECL);
            engine->RegisterGlobalFunction("void flush()", asFUNCTION(flush), asCALL_CDECL);
        }

        // Register Raylib stuff
        {
            engine->RegisterGlobalFunction("bool IsKeyDown(int16)", asFUNCTION(IsKeyDown), asCALL_CDECL);
            engine->RegisterGlobalFunction("bool IsKeyPressed(int16)", asFUNCTION(IsKeyPressed), asCALL_CDECL);
            engine->RegisterGlobalFunction("bool IsKeyReleased(int16)", asFUNCTION(IsKeyReleased), asCALL_CDECL);
        }

        // Register Vector Classes
        {

            engine->RegisterObjectType("Vec2", 0, asOBJ_REF);

            engine->RegisterObjectBehaviour("Vec2", asBEHAVE_FACTORY, "Vec2@ f()", asFUNCTION(Vec2Factory_Default), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Vec2", asBEHAVE_FACTORY, "Vec2@ f(float a, float b)", asFUNCTION(Vec2Factory_Init), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Vec2", asBEHAVE_FACTORY, "Vec2@ f(const Vec2& in)", asFUNCTION(Vec2Factory_Copy), asCALL_CDECL);
            REGISTERCREF(engine,"Vec2")

            engine->RegisterObjectType("Rect", 0, asOBJ_REF);
            engine->RegisterObjectBehaviour("Rect", asBEHAVE_FACTORY, "Rect@ f()", asFUNCTION(RectFactory_Default), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Rect", asBEHAVE_FACTORY, "Rect@ f(float, float, float, float)", asFUNCTION(RectFactory_Init), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Rect", asBEHAVE_FACTORY, "Rect@ f(const Rect& in)", asFUNCTION(RectFactory_Copy), asCALL_CDECL);
            REGISTERCREF(engine,"Rect")

            engine->RegisterObjectBehaviour("Rect", asBEHAVE_FACTORY, "Rect@ f(const Vec2& in)", asFUNCTION(RectFactory_CopyVec2), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Vec2", asBEHAVE_FACTORY, "Vec2@ f(const Rect& in)", asFUNCTION(Vec2Factory_CopyRect), asCALL_CDECL);

            engine->RegisterObjectMethod("Rect", "Vec2& getPos() const", asMETHOD(Rect, getPos), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Vec2& getDim() const", asMETHOD(Rect,getDim), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Vec2& getMidPoint() const", asMETHOD(Rect, getMidPoint), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Vec2& Collide(const Rect &in) const", asMETHODPR(Rect, Collide, (const Rect&) const, Vec2), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "bool isColliding(const Rect& in) const", asMETHODPR(Rect, isColliding, (const Rect&) const, bool), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "float getTriAngle() const", asMETHOD(Rect, getTriAngle), asCALL_THISCALL);

            engine->RegisterObjectMethod("Vec2", "float getDegrees() const", asMETHOD(Vec2, getDegrees), asCALL_THISCALL);

            engine->RegisterObjectMethod("Vec2", "float& at(uint32)", asMETHOD(Vec2, at), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "float& opIndex(uint32) const", asMETHOD(Vec2, operator[]) , asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opAssign(const Vec2& in)", asMETHODPR(Vec2, operator=, (const Vec2&), Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "float& at(uint32)", asMETHOD(Rect, at), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "float& opIndex(uint32) const", asMETHOD(Rect, operator[]) , asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opAssign(const Rect& in)",   asMETHODPR(Rect, operator=, (const Rect&), Rect&), asCALL_THISCALL);

            engine->RegisterGlobalFunction("void print(const Vec2 &in)",   asFUNCTION(print<const Vec2&>), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(const Rect &in)",   asFUNCTION(print<const Rect&>), asCALL_CDECL);
        }

        // Register Sprite stuff
        {
            engine->RegisterObjectType("Sprite", sizeof(Sprite*), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_PRIMITIVE);
            engine->RegisterGlobalFunction("Sprite getSprite(const string &in)", asFUNCTION(SpriteContainer::getSprite), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(const Sprite& in)", asFUNCTION(printPtr), asCALL_CDECL);
        }

        // Register Entity stuff
        {
            engine->RegisterObjectType("Entity", 0, asOBJ_REF);

            REGISTERCREF(engine,"Entity")

            engine->RegisterObjectMethod("Entity", "void Collide(const Entity& in)", asMETHOD(Entity, Collide), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void setDimensions(const Vec2& in)", asMETHOD(Entity, setDimensions), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void setDrawSize(const Vec2& in)", asMETHOD(Entity, setDrawSize), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void setCurrentAnim(const string& in)", asMETHOD(Entity, setCurrentAnim), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void setSolid()", asMETHOD(Entity, setSolid), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "bool isSolid() const", asMETHOD(Entity, isSolid), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void move(const Vec2& in)", asMETHOD(Entity, move), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void setPos(const Vec2& in)", asMETHOD(Entity, setPos), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "const Vec2& getPos() const", asMETHOD(Entity, getPos), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "const Vec2& getDelta() const", asMETHOD(Entity, getDelta), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "const Vec2& getInitPos() const", asMETHOD(Entity, getInitPos), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "const Rect& getCollisionRect() const", asMETHOD(Entity, getPos), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "Sprite getSprite() const", asMETHOD(Entity, getSprite), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void setSprite(Sprite)", asMETHOD(Entity, setSprite), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "const string& getName() const", asMETHOD(Entity, getName), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "float getDepth() const", asMETHOD(Entity, getDepth), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void setDepth(float)", asMETHOD(Entity, setDepth), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void orderByY(int16)", asMETHOD(Entity, orderByY), asCALL_THISCALL);

        }

    }

    void ScriptWrapper::createModule(const char* name, const vector<string>& files) const {

        CScriptBuilder builder;
        auto r = builder.StartNewModule(engine, name);
        if (r < 0) throw Engine::Exception(string("Failed starting new module: ") + name);

        for(const auto& file: files) {
            r = builder.AddSectionFromFile(file.c_str());
            if (r < 0) throw Engine::Exception(string("Script ") + file + " contains errors");
        }

        r = builder.BuildModule();
        if (r < 0) throw Engine::Exception("Failed to build module, check scripts for errors");

    }

    void ScriptWrapper::runFunction(asIScriptFunction *func) const {

        if(!func) return;
        ctx->Prepare(func);

        auto r = ctx->Execute();
        if (r < 0) throw Engine::Exception("Failed function execution");
    }

    //void ScriptWrapper::

}