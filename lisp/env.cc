#include "env.h"
#include <string>

void Env::store_binding(const string& name, Value* val) {
        bindings_[name] = val;
}