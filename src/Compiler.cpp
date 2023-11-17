#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "../grammar/TELLexer.h"
#include "../grammar/TELParser.h"
#include "../include/Compiler.h"
#include "../include/TELTreeVisitor.h"

using namespace antlrcpp;
using namespace antlr4;
using namespace std;

Compiler::Compiler(string filename)
{
    ifstream ins;
    // Create the input stream.
    ins.open(filename);
    ANTLRInputStream input(ins);
    // Create a lexer which scans the input stream
    // to create a token stream.
    TELLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    // Print the token stream.
    TELParser parser(&tokens);
    TELTreeVisitor visitor;
    // Creates the new file to write code on
    filename = filename.substr(0, filename.find(".") + 1) + "ir";
    cout << filename;
    ofstream out;
    out.open(filename);
    visitor.visit(parser.initial());
}

Compiler::~Compiler()
{
}
