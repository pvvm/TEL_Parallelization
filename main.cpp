#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "TELLexer.h"
#include "TELParser.h"

using namespace std;
using namespace antlr4;

using namespace antlrcpp;
using namespace antlr4;
using namespace std;
int main(int argc, const char *args[])
{
ifstream ins;
// Create the input stream.
ins.open(args[1]);
ANTLRInputStream input(ins);
// Create a lexer which scans the input stream
// to create a token stream.
TELLexer lexer(&input);
CommonTokenStream tokens(&lexer);
// Print the token stream.
cout << "Tokens:" << endl;
tokens.fill();
for (Token *token : tokens.getTokens())
{
std::cout << token->toString() << std::endl;
}
// Create a parser which parses the token stream
// to create a parse tree.
TELParser parser(&tokens);
return 0;
}