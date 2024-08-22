//
// Created by blenk on 19/08/24.
//

#ifndef NOWHEREFIGHTERS_SCRIPTOBJECTS_H
#define NOWHEREFIGHTERS_SCRIPTOBJECTS_H

#include "angelscript/include/angelscript.h"
#include "angelscript/source/as_objecttype.h"
#include "ScriptWrapper.h"
#include "../Engine/Entity.h"

namespace Engine {

    class ScriptObject {

    protected:

        ScriptWrapper* wrapper;

        asIScriptEngine* engine;
        asIScriptModule* module;
        asITypeInfo* type;
        asIScriptObject* obj;

        void runFunction(const char* decl) const;

        template<typename F>
        void runFunctionWithArgs(const char* decl, F processArgs);

    public:

        ScriptObject(ScriptWrapper* w, const char* name);

    };

    class ScriptEntity : public Entity, public ScriptObject {

        void construct();

    public:

        ScriptEntity(ScriptWrapper* w, const char* name, const Vec2& pos):
            Entity(name, nullptr, {0,0}, pos), ScriptObject(w, name)  {construct();}

        void draw(Rect& view) override;
        void update() override {runFunction("void update()");}
        void init() override {Entity::init(); runFunction("void init()");}
        void collision(Entity& ent) override;
        void wallcollision(Rect& rect) override;
        void exitView() override {runFunction("void exitview()");}
        void enterView() override {runFunction("void enterview()");}

    };

    template<typename F>
    void ScriptObject::runFunctionWithArgs(const char* decl, F processArgs) {
        wrapper->runFunctionWithArgs(type->GetMethodByDecl(decl), [&](asIScriptContext* ctx) {
            ctx->SetObject(obj);
            processArgs(ctx);
        });
    }

} // engine

#endif //NOWHEREFIGHTERS_SCRIPTOBJECTS_H
