//
// Created by blenk on 13/08/24.
//

#ifndef NOWHEREFIGHTERS_SCRIPTWRAPPER_H
#define NOWHEREFIGHTERS_SCRIPTWRAPPER_H

#include <vector>
#include <string>

#include "../Engine/Entity.h"
#include "../Engine/Room.h"
#include "../Engine/Sprite.h"
#include "../Engine/Exception.h"

#include "angelscript/include/angelscript.h"


using std::vector, std::string;

namespace Engine {

    class ScriptWrapper {
        asIScriptEngine* engine;
        asIScriptContext* ctx;
    public:

        ScriptWrapper();

        [[nodiscard]] asIScriptEngine* getEngine() const {return engine;}
        [[nodiscard]] asIScriptContext* getContext() const {return ctx;}

        void createModule(const char* name, const vector<string>& files) const;
        void runFunction(asIScriptFunction* func) const;

        template<typename F>
        void runFunctionWithArgs(asIScriptFunction* func, F processArgs) const;

        ~ScriptWrapper() {
            ctx->Release();
            engine->ShutDownAndRelease();
        }

    };

    template<typename F>
    void ScriptWrapper::runFunctionWithArgs(asIScriptFunction* func, F processArgs) const {

        if(!func) return;

        ctx->Prepare(func);
        processArgs(ctx);

        auto r = ctx->Execute();
        if (r < 0) throw Engine::Exception("Failed function execution");

    }

}

#endif //NOWHEREFIGHTERS_SCRIPTWRAPPER_H
