#include "Value.h"
#include <map>
#include <string>

#ifndef ENV_H
#define ENV_H

using std::string;

class Env {
public:
  void store_binding(const string &name, Value *val);

private:
  std::map<string, Value *> bindings_;
};

#endif
