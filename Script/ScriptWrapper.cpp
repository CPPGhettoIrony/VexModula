//
// Created by blenk on 13/08/24.
//

#include <iostream>
#include "../Engine/Exception.h"
#include "ScriptWrapper.h"

using std::cout, std::cerr, std::endl;

void MessageCallback(const asSMessageInfo *msg, void *param)
{
    const char *type = "ERR ";
    if( msg->type == asMSGTYPE_WARNING )
        type = "WARN";
    else if( msg->type == asMSGTYPE_INFORMATION )
        type = "INFO";
    printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
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

        auto r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
        if (r < 0) throw Engine::Exception("Failed to set MessageCallback function");

        RegisterStdString(engine);

        r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
        if (r < 0) throw Engine::Exception("Failed setting print Function");

    }

    void ScriptWrapper::createModule(const char* name, const vector<string>& files) {

        CScriptBuilder builder;
        builder.StartNewModule(engine, name); //string("Failed starting new module: ") + name);

        for(const auto& file: files)
            builder.AddSectionFromFile(file.c_str()); // string("Script ") + file + " contains errors");

       builder.BuildModule(); //"Failed to build module, check scripts for errors");

    }

    void ScriptWrapper::runFunction(asIScriptFunction *func) {
        ctx->Prepare(func);
        ctx->Execute(); // "Failed function execution");
    }

    //void ScriptWrapper::

}