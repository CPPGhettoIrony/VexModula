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

void print(const string& in) {
    cout << in;
}

void flush() {
    cout << endl;
}


namespace Engine {

    ScriptWrapper::ScriptWrapper(): engine(asCreateScriptEngine()) {

        ctx = engine->CreateContext();

        engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

        RegisterStdString(engine);

        engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
        engine->RegisterGlobalFunction("void flush()", asFUNCTION(flush), asCALL_CDECL);

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