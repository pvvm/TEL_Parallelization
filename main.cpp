#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "grammar/TELLexer.h"
#include "grammar/TELParser.h"
#include "include/Compiler.h"

using namespace std;
using namespace antlr4;

using namespace antlrcpp;
using namespace antlr4;
using namespace std;
int main(int argc, const char *args[])
{
    Compiler compiler(args[1]);

return 0;
}