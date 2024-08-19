//
// Created by blenk on 13/08/24.
//

#include <iostream>

#include "../Engine/Exception.h"
#include "ScriptWrapper.h"

#include "../Engine/AngelMacros.h"

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


void printVector(const Engine::Vector& in) {cout << in;}
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
            engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(printString), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(bool)", asFUNCTION(printBool), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(float)", asFUNCTION(printFloat), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(int16)", asFUNCTION(printInt), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(uint32)", asFUNCTION(printPtr), asCALL_CDECL);
            engine->RegisterGlobalFunction("void flush()", asFUNCTION(flush), asCALL_CDECL);
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

            engine->RegisterObjectMethod("Rect", "Rect& opAdd(const Rect& in) const", asMETHODPR(Rect, opAdd, (const Rect&) const, Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opSub(const Rect& in) const", asMETHODPR(Rect, opSub, (const Rect&) const, Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opMul(const Rect& in) const", asMETHODPR(Rect, opMul, (const Rect&) const, Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opDiv(const Rect& in) const", asMETHODPR(Rect, opDiv, (const Rect&) const, Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opAddAssign(const Rect& in)", asMETHODPR(Rect, opAddAssign, (const Rect&), Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opSubAssign(const Rect& in)", asMETHODPR(Rect, opSubAssign, (const Rect&), Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opMulAssign(const Rect& in)", asMETHODPR(Rect, opMulAssign, (const Rect&), Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opDivAssign(const Rect& in)", asMETHODPR(Rect, opDivAssign, (const Rect&), Rect&), asCALL_THISCALL);

            engine->RegisterObjectMethod("Rect", "Rect& opAdd(float) const", asMETHODPR(Rect, opAdd, (float) const, Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opSub(float) const", asMETHODPR(Rect, opSub, (float) const, Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opMul(float) const", asMETHODPR(Rect, opMul, (float) const, Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opDiv(float) const", asMETHODPR(Rect, opDiv, (float) const, Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opAddAssign(float)", asMETHODPR(Rect, opAddAssign, (float), Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opSubAssign(float)", asMETHODPR(Rect, opSubAssign, (float), Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opMulAssign(float)", asMETHODPR(Rect, opMulAssign, (float), Rect&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opDivAssign(float)", asMETHODPR(Rect, opDivAssign, (float), Rect&), asCALL_THISCALL);

            engine->RegisterObjectMethod("Rect", "Vec2& getPos() const", asMETHOD(Rect, opGetPos), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Vec2& getDim() const", asMETHOD(Rect, opGetDim), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Vec2& getMidPoint() const", asMETHOD(Rect, opGetMidPoint), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Vec2& Collide(const Rect &in) const", asMETHODPR(Rect, opCollide, (const Rect&) const, Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "bool isColliding(const Rect& in) const", asMETHODPR(Rect, isColliding, (const Rect&) const, bool), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "float getTriAngle() const", asMETHOD(Rect, getTriAngle), asCALL_THISCALL);

            engine->RegisterObjectMethod("Vec2", "Vec2& opAdd(const Vec2& in) const", asMETHODPR(Vec2, opAdd, (const Vec2&) const, Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opSub(const Vec2& in) const", asMETHODPR(Vec2, opSub, (const Vec2&) const, Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opMul(const Vec2& in) const", asMETHODPR(Vec2, opMul, (const Vec2&) const, Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opDiv(const Vec2& in) const", asMETHODPR(Vec2, opDiv, (const Vec2&) const, Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opAddAssign(const Vec2& in)", asMETHODPR(Vec2, opAddAssign, (const Vec2&), Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opSubAssign(const Vec2& in)", asMETHODPR(Vec2, opSubAssign, (const Vec2&), Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opMulAssign(const Vec2& in)", asMETHODPR(Vec2, opMulAssign, (const Vec2&), Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opDivAssign(const Vec2& in)", asMETHODPR(Vec2, opDivAssign, (const Vec2&), Vec2&), asCALL_THISCALL);

            engine->RegisterObjectMethod("Vec2", "Vec2& opAdd(float) const", asMETHODPR(Vec2, opAdd, (float) const, Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opSub(float) const", asMETHODPR(Vec2, opSub, (float) const, Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opMul(float) const", asMETHODPR(Vec2, opMul, (float) const, Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opDiv(float) const", asMETHODPR(Vec2, opDiv, (float) const, Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opAddAssign(float)", asMETHODPR(Vec2, opAddAssign, (float), Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opSubAssign(float)", asMETHODPR(Vec2, opSubAssign, (float), Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opMulAssign(float)", asMETHODPR(Vec2, opMulAssign, (float), Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opDivAssign(float)", asMETHODPR(Vec2, opDivAssign, (float), Vec2&), asCALL_THISCALL);

            engine->RegisterObjectMethod("Vec2", "float getDegrees() const", asMETHOD(Vec2, getDegrees), asCALL_THISCALL);

            engine->RegisterObjectMethod("Vec2", "float& at(uint32)", asMETHOD(Vec2, at), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "float& opIndex(uint32) const", asMETHOD(Vec2, operator[]) , asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opAssign(const Vec2& in)", asMETHODPR(Vec2, operator=, (const Vec2&), Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "float& at(uint32)", asMETHOD(Rect, at), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "float& opIndex(uint32) const", asMETHOD(Rect, operator[]) , asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opAssign(const Rect& in)",   asMETHODPR(Rect, operator=, (const Rect&), Rect&), asCALL_THISCALL);

            engine->RegisterGlobalFunction("void print(const Vec2 &in)",   asFUNCTION(printVector), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(const Rect &in)",   asFUNCTION(printVector), asCALL_CDECL);
        }

        // Register Sprite stuff
        {
            engine->RegisterObjectType("Sprite", sizeof(Sprite*), asOBJ_VALUE | asOBJ_POD);
            engine->RegisterGlobalFunction("Sprite& getSprite(const string &in)", asFUNCTION(SpriteContainer::getSprite), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(const Sprite& in)", asFUNCTION(printPtr), asCALL_CDECL);
        }

        // Register Entity stuff
        {
            engine->RegisterObjectType("Entity", 0, asOBJ_REF);

            REGISTERCREF(engine,"Entity")

            engine->RegisterObjectMethod("Entity", "void setSolid()", asMETHOD(Entity, setSolid), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "bool isSolid() const", asMETHOD(Entity, isSolid), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void move(const Vec2& in)", asMETHOD(Entity, move), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void setPos(const Vec2& in)", asMETHOD(Entity, setPos), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "const Vec2& getPos() const", asMETHOD(Entity, getPos), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "const Vec2& getDelta() const", asMETHOD(Entity, getDelta), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "const Vec2& getInitPos() const", asMETHOD(Entity, getInitPos), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "const Rect& getCollisionRect() const", asMETHOD(Entity, getPos), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "Sprite& getSprite() const", asMETHOD(Entity, getSprite), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "const string& getName() const", asMETHOD(Entity, getName), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "float getDepth() const", asMETHOD(Entity, getDepth), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void setDepth(float)", asMETHOD(Entity, setDepth), asCALL_THISCALL);
            engine->RegisterObjectMethod("Entity", "void orderByY(int16)", asMETHOD(Entity, orderByY), asCALL_THISCALL);

        }

    }

    void ScriptWrapper::createModule(const char* name, const vector<string>& files) {

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

    void ScriptWrapper::runFunction(asIScriptFunction *func) {
        ctx->Prepare(func);
        auto r = ctx->Execute();
        if (r < 0) throw Engine::Exception("Failed function execution");
    }

    //void ScriptWrapper::

}