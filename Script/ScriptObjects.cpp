//
// Created by blenk on 19/08/24.
//

#include "ScriptObjects.h"

namespace Engine {

    ScriptObject::ScriptObject(ScriptWrapper* w, const char* name):
        wrapper(w),
        module(w->getEngine()->GetModule(name)),
        engine(w->getEngine()),
        type(module->GetTypeInfoByDecl(name)) {

            string decl = name;
            decl += " @" + decl + "()";

            auto *factory = type->GetFactoryByDecl(decl.c_str());
            auto ctx = w->getContext();

            ctx->Prepare(factory);
            ctx->Execute();

            obj = *(asIScriptObject**)ctx->GetAddressOfReturnValue();

            obj->AddRef();

    }

    void ScriptObject::runFunction(const char* decl) const {
        wrapper->runFunctionWithArgs(type->GetMethodByDecl(decl), [&](asIScriptContext* ctx) {
            ctx->SetObject(obj);
        });
    }

    void ScriptEntity::construct() {
        runFunctionWithArgs("void construct(Entity& ent)", [&](asIScriptContext* ctx) {
             ctx->SetArgObject(0, this);
        });
    }

    void ScriptEntity::draw(Rect& view) {
        Entity::draw(view);
        runFunctionWithArgs("void draw(const Rect& in)", [&](asIScriptContext* ctx){
            ctx->SetArgObject(0, &view);
        });
    }

    void ScriptEntity::collision(Entity& ent) {
        runFunctionWithArgs("void collision(Entity& ent)", [&](asIScriptContext* ctx){
            ctx->SetArgObject(0, &ent);
        });
    }

    void ScriptEntity::wallcollision(Rect &rect) {
        Entity::wallcollision(rect);
        runFunctionWithArgs("void wallcollision(const Rect& in)", [&](asIScriptContext* ctx){
            ctx->SetArgObject(0, &rect);
        });
    }

}