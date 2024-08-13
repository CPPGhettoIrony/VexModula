//
// Created by blenk on 13/08/24.
//

#include <iostream>
#include "ScriptWrapper.h"

using std::cout, std::cerr, std::endl, std::string;

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

        engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
        RegisterStdString(engine);

        engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
        engine->RegisterGlobalFunction("void flush()", asFUNCTION(flush), asCALL_CDECL);

    }



}