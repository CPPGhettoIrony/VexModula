//
// Created by blenk on 19/08/24.
//

#include "ScriptObjects.h"

namespace Engine {

    void ScriptObject::runFunction(const char* decl) {
        wrapper->runFunctionWithArgs(module->GetFunctionByDecl(decl), [&](asIScriptContext* ctx) {
            ctx->SetArgObject(0,this);
        });
    }

    void ScriptEntity::draw(Rect& view) {
        Entity::draw(view);
        runFunctionWithArgs("void _draw(const Rect& in)", [&](asIScriptContext* ctx){
            ctx->SetArgObject(1, &view);
        });
    }

    void ScriptEntity::collision(Entity& ent) {
        runFunctionWithArgs("void _collision(const Entity& in)", [&](asIScriptContext* ctx){
            ctx->SetArgObject(1, &ent);
        });
    }

    void ScriptEntity::wallcollision(Rect &rect) {
        runFunctionWithArgs("void _wallcollision(const Rect& in)", [&](asIScriptContext* ctx){
            ctx->SetArgObject(1, &rect);
        });
    }

    void ScriptEntity::receive(Entity* e, string& str, stringstream& stream) {
        runFunctionWithArgs("void _receive(const string& in)", [&](asIScriptContext* ctx) {
            ctx->SetArgObject(1, e);
            ctx->SetArgObject(2, &str);
        });
    }

}