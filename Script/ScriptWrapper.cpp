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

int throwIfFail(int i, const string& msg) {
    if (i < 0) throw Engine::Exception(msg);
}

namespace Engine {

    ScriptWrapper::ScriptWrapper(): engine(asCreateScriptEngine()) {

        ctx = engine->CreateContext();

        throwIfFail(engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL), "Failed setting MessageCallback Function");
        RegisterStdString(engine);

        throwIfFail(engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL), "Failed setting print Function");
        throwIfFail(engine->RegisterGlobalFunction("void flush()", asFUNCTION(flush), asCALL_CDECL), "Failed setting flush Function");

    }

    void ScriptWrapper::createModule(const char* name, const vector<string>& files) {

        CScriptBuilder builder;
        throwIfFail(builder.StartNewModule(engine, name), string("Failed starting new module: ") + name);

        for(const auto& file: files)
            throwIfFail(builder.AddSectionFromFile(file.c_str()), string("Script ") + file + " contains errors");

        throwIfFail(builder.BuildModule(), "Failed to build module, check scripts for errors");

    }

    void ScriptWrapper::runFunction(asIScriptFunction *func) {
        ctx->Prepare(func);
        throwIfFail(ctx->Execute(), "Failed function execution");
    }

    void ScriptWrapper::

}