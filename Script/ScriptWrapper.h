//
// Created by blenk on 13/08/24.
//

#ifndef NOWHEREFIGHTERS_SCRIPTWRAPPER_H
#define NOWHEREFIGHTERS_SCRIPTWRAPPER_H

#include <vector>
#include <string>
#include "angelscript/include/angelscript.h"
#include "angelscript/add_on/scriptstdstring/scriptstdstring.h"
#include "angelscript/add_on/scriptbuilder/scriptbuilder.h"

using std::vector, std::string;

namespace Engine {
    class ScriptWrapper {
        asIScriptEngine* engine;
        asIScriptContext* ctx;
    public:

        ScriptWrapper();

        asIScriptModule* getModule(const char* module) {
            return engine->GetModule(module);
        };

        asIScriptFunction* getFunction(asIScriptModule* module, const char* func) {
            return module->GetFunctionByDecl(func);
        };

        void createModule(const char* name, const vector<string>& files);
        void runFunction(asIScriptFunction* func);

        ~ScriptWrapper() {
            ctx->Release();
            engine->ShutDownAndRelease();
        }

    };
}


#endif //NOWHEREFIGHTERS_SCRIPTWRAPPER_H
