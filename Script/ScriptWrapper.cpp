//
// Created by blenk on 13/08/24.
//

#include <iostream>
#include "../Engine/Exception.h"
#include "ScriptWrapper.h"

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

void flush() {cout << endl;}



namespace Engine {

    ScriptWrapper::ScriptWrapper(): engine(asCreateScriptEngine()) {

        ctx = engine->CreateContext();

        engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

        RegisterStdString(engine);

        engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(printString), asCALL_CDECL);
        engine->RegisterGlobalFunction("void print(float)", asFUNCTION(printFloat), asCALL_CDECL);
        engine->RegisterGlobalFunction("void flush()", asFUNCTION(flush), asCALL_CDECL);

        {
            // Register Vector objects

            engine->RegisterObjectType("Vec2", 0, asOBJ_REF);
            engine->RegisterObjectBehaviour("Vec2", asBEHAVE_FACTORY, "Vec2@ f()", asFUNCTION(Vec2Factory_Default), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Vec2", asBEHAVE_FACTORY, "Vec2@ f(float a, float b)", asFUNCTION(Vec2Factory_Init), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Vec2", asBEHAVE_FACTORY, "Vec2@ f(const Vec2& in)", asFUNCTION(Vec2Factory_Copy), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Vec2", asBEHAVE_ADDREF, "void f()", asMETHOD(Vec2, addRef), asCALL_THISCALL);
            engine->RegisterObjectBehaviour("Vec2", asBEHAVE_RELEASE, "void f()", asMETHOD(Vec2, release), asCALL_THISCALL);

            engine->RegisterObjectType("Rect", 0, asOBJ_REF);
            engine->RegisterObjectBehaviour("Rect", asBEHAVE_FACTORY, "Rect@ f()", asFUNCTION(RectFactory_Default), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Rect", asBEHAVE_FACTORY, "Rect@ f(float, float, float, float)", asFUNCTION(RectFactory_Init), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Rect", asBEHAVE_FACTORY, "Rect@ f(const Rect& in)", asFUNCTION(RectFactory_Copy), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Rect", asBEHAVE_ADDREF, "void f()", asMETHOD(Rect, addRef), asCALL_THISCALL);
            engine->RegisterObjectBehaviour("Rect", asBEHAVE_RELEASE, "void f()", asMETHOD(Rect, release), asCALL_THISCALL);

            engine->RegisterObjectBehaviour("Rect", asBEHAVE_FACTORY, "Rect@ f(const Vec2& in)", asFUNCTION(RectFactory_CopyVec2), asCALL_CDECL);
            engine->RegisterObjectBehaviour("Vec2", asBEHAVE_FACTORY, "Vec2@ f(const Rect& in)", asFUNCTION(Vec2Factory_CopyRect), asCALL_CDECL);

            engine->RegisterObjectMethod("Rect", "Vec2& Collide(const Rect& in) const", asMETHODPR(Rect, Collide, (const Rect&) const, Vec2), asCALL_THISCALL);

            engine->RegisterObjectMethod("Vec2", "float& at(uint32)", asMETHOD(Vec2, at), asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "float& opIndex(uint32) const", asMETHOD(Vec2, operator[]) , asCALL_THISCALL);
            engine->RegisterObjectMethod("Vec2", "Vec2& opAssign(const Vec2& in)", asMETHODPR(Vec2, operator=, (const Vec2&), Vec2&), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "float& at(uint32)", asMETHOD(Rect, at), asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "float& opIndex(uint32) const", asMETHOD(Rect, operator[]) , asCALL_THISCALL);
            engine->RegisterObjectMethod("Rect", "Rect& opAssign(const Rect& in)",   asMETHODPR(Rect, operator=, (const Rect&), Rect&), asCALL_THISCALL);

            engine->RegisterGlobalFunction("void print(const Vec2 &in)",   asFUNCTION(printVector), asCALL_CDECL);
            engine->RegisterGlobalFunction("void print(const Rect &in)",   asFUNCTION(printVector), asCALL_CDECL);
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