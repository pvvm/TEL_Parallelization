compiler: main.cpp parser.o lexer.o
	g++ main.cpp parser.o lexer.o -I /usr/local/include/antlr4-runtime -lantlr4-runtime -o compiler

parser.o: TELParser.cpp TELParser.h
	g++ -c TELParser.cpp  -I /usr/local/include/antlr4-runtime -lantlr4-runtime -o parser.o

lexer.o: TELLexer.cpp TELLexer.h
	g++ -c TELLexer.cpp  -I /usr/local/include/antlr4-runtime -lantlr4-runtime -o lexer.o