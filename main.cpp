#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <string>
#include "tokens/Variable.h"
#include "state-machine/Parser.h"

int main() {
    Parser parser;
    parser.parse_string("mat x = [[1]];"
                        "x = null;"
    );
    return 0;
}
