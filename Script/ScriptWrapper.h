//
// Created by blenk on 13/08/24.
//

#ifndef NOWHEREFIGHTERS_SCRIPTWRAPPER_H
#define NOWHEREFIGHTERS_SCRIPTWRAPPER_H

#include "angelscript/angelscript.h"
#include "add_on/scriptstdstring/scriptstdstring.h"
#include "add_on/scriptbuilder/scriptbuilder.h"

namespace Engine {
    class ScriptWrapper {
        asIScriptEngine* engine;
        asIScriptContext *ctx;
        CScriptBuilder* builder;
    public:

        ScriptWrapper();

        void CreateModule() {}

        ~ScriptWrapper() {
            engine->ShutDownAndRelease();
        }

    };
}


#endif //NOWHEREFIGHTERS_SCRIPTWRAPPER_H
