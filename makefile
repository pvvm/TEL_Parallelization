GRAMMAR_DIR = grammar
BUILD_DIR = build
SRC_DIR = src
HEADER_DIR = include
ANTLR_RUNTIME = /usr/local/include/antlr4-runtime
C_FLAGS =  -I $(ANTLR_RUNTIME) -lantlr4-runtime

OBJECTS = \
		$(BUILD_DIR)/lexer.o		\
		$(BUILD_DIR)/parser.o		\
		$(BUILD_DIR)/compiler.o

all: $(BUILD_DIR) compiler

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

compiler: main.cpp $(OBJECTS)
	g++ main.cpp $(OBJECTS) $(C_FLAGS) -o compiler

$(BUILD_DIR)/parser.o: $(GRAMMAR_DIR)/TELParser.cpp $(GRAMMAR_DIR)/TELParser.h
	g++ -c $(GRAMMAR_DIR)/TELParser.cpp  $(C_FLAGS) -o $(BUILD_DIR)/parser.o

$(BUILD_DIR)/lexer.o: $(GRAMMAR_DIR)/TELLexer.cpp $(GRAMMAR_DIR)/TELLexer.h
	g++ -c $(GRAMMAR_DIR)/TELLexer.cpp  $(C_FLAGS) -o $(BUILD_DIR)/lexer.o

$(BUILD_DIR)/compiler.o: $(SRC_DIR)/Compiler.cpp $(HEADER_DIR)/Compiler.h $(GRAMMAR_DIR)/TELLexer.h $(GRAMMAR_DIR)/TELParser.h $(HEADER_DIR)/TELTreeVisitor.h
	g++ -c $(SRC_DIR)/Compiler.cpp  $(C_FLAGS) -o $(BUILD_DIR)/compiler.o

$(GRAMMAR_DIR)/TELLexer.cpp: TEL.g4
	java -jar antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o $(GRAMMAR_DIR) TEL.g4

$(GRAMMAR_DIR)/TELParser.cpp: TEL.g4
	java -jar antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor -o $(GRAMMAR_DIR) TEL.g4