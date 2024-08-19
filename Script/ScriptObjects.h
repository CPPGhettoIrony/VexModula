//
// Created by blenk on 19/08/24.
//

#ifndef NOWHEREFIGHTERS_SCRIPTOBJECTS_H
#define NOWHEREFIGHTERS_SCRIPTOBJECTS_H

#include "ScriptWrapper.h"
#include "../Engine/Entity.h"

namespace Engine {

    class ScriptObject {

    protected:

        ScriptWrapper* wrapper;
        asIScriptModule* module;

        void runFunction(const char* decl);

        template<typename F>
        void runFunctionWithArgs(const char* decl, F processArgs);

    public:

        ScriptObject(ScriptWrapper* w, const char* name):
            wrapper(w), module(w->getEngine()->GetModule(name)) {}

    };

    class ScriptEntity : public Entity, public ScriptObject {

    public:

        ScriptEntity(ScriptWrapper* w, const char* name, const Vec2& pos):
            Entity(name, nullptr, {0,0}, pos), ScriptObject(w, name)  {}

        void construct() {runFunction("void _construct()");}
        void draw(Rect& view) override;
        void update() override {runFunction("void _update()");}
        void init() override {runFunction("void _init()");}
        void collision(Entity& ent) override;
        void wallcollision(Rect& rect) override;
        void exitView() override {runFunction("void _exitview()");}
        void enterView() override {runFunction("void _enterview()");}
        void receive(Entity* e, string& str, stringstream& stream) override;

    };

    template<typename F>
    void ScriptObject::runFunctionWithArgs(const char* decl, F processArgs) {
        wrapper->runFunctionWithArgs(module->GetFunctionByDecl(decl), [&](asIScriptContext* ctx) {
            ctx->SetArgObject(0,this);
            processArgs(ctx);
        });
    }

} // engine

#endif //NOWHEREFIGHTERS_SCRIPTOBJECTS_H
