
// Generated from TEL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "../grammar/TELVisitor.h"


/**
 * This class provides an empty implementation of TELVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  TELGeneratorVisitor : public TELVisitor {
private:
	int indentationCounter = 0;
	bool inDispatch = false;
	int tokenCounter = 0;
	bool previousTokenElse = false;
	bool inProcess = false;
	int inLoopCounter = 0;
	int inCondCounter = 0;
	bool checkForLock = false;
	bool firstStatementEP = false;
	std::string currentEPName = "";
	std::vector<std::string> unlockVars;

	// Writes the symbols and indentation to the file
	std::string writeAndIndentation(std::string token, std::string nextToken, std::string indentation) {
		std::string symbols = ".()[]";

		// Adds spacing if the current symbol isn't one of the above
		if(nextToken != "" && (symbols.find(nextToken) < symbols.length()) || (symbols.find(token) < symbols.length()))
			outputFile << token;
		else
			outputFile << token + " ";

		// Increases and decreases indentation counter when we enter a new block
		if(token == "{") {
			indentationCounter++;
			indentation += "\t";
		} else if(token == "}") {
			indentationCounter--;
			if (!indentation.empty())
				indentation.erase(indentation.end() - 1);
		}

		// Writes a new line including the indentation space
		if(!inDispatch && token == "{" || token == "}" || token == ";") {
			outputFile << "\n" + indentation;
		}
		return indentation;
	}

	// Each child of a node of the parse tree calls this function to get its symbol written
	template <class T> void writeChild(T *ctx) {
		std::string token;
		std::string nextToken;
		std::string indentation;
		for(int i = 0; i < indentationCounter; i++)
			indentation += "\t";

		for(int i = 0; i < ctx->children.size(); i++) {
			token = ctx->children[i]->getText();
			nextToken = "";
			// Saves the next token if it is a symbol
			if (i+1 < ctx->children.size() && ctx->children[i+1]->children.size() == 0)
				nextToken = ctx->children[i+1]->getText();

			// Visits its children if it has a child
			if (ctx->children[i]->children.size() > 0)
				visit(ctx->children[i]);
			else
				indentation = writeAndIndentation(token, nextToken, indentation);
		}
	}

public:
	std::ofstream outputFile;
	std::map<std::string, std::map<std::string, std::vector<int>>> EPUnlockLocations;

	TELGeneratorVisitor():TELVisitor() {
		tokenCounter = 0;
	}

	virtual std::any visitInitial(TELParser::InitialContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		
		return 0;
	}

	virtual std::any visitDispatcher(TELParser::DispatcherContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitDispEPs(TELParser::DispEPsContext *ctx) override {
		inDispatch = true;
		tokenCounter++;
		writeChild(ctx);
		inDispatch = false;
		return 0;
	}

	virtual std::any visitStructLike(TELParser::StructLikeContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitOnlyVarDecl(TELParser::OnlyVarDeclContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitEventProc(TELParser::EventProcContext *ctx) override {
		currentEPName = ctx->ID(0)->toString();
		inProcess = true;
		firstStatementEP = true;
		tokenCounter++;
		writeChild(ctx);
		inProcess = false;
		currentEPName = "";
		return 0;
	}

	virtual std::any visitStatement(TELParser::StatementContext *ctx) override {
		tokenCounter++;
		// Writes all locks
		if(firstStatementEP) {
			std::string indentation;
			for(int i = 0; i < indentationCounter; i++)
				indentation += "\t";
			for(auto EPName: EPUnlockLocations[currentEPName]) {
				outputFile << "lock(ctx." << EPName.first << ");\n" << indentation;
			}
		}
		firstStatementEP = false;
		writeChild(ctx);

		std::string indentation;
		for(int i = 0; i < indentationCounter; i++)
			indentation += "\t";
		// If it is in a loop, the write of unlock is postponed until it leaves the loop's block
		if(inLoopCounter == 0) {
			// Writes the unlocks we have for that node
			while(unlockVars.size() > 0) {
				outputFile << "unlock(ctx." << unlockVars.back() << ");\n" << indentation;
				unlockVars.pop_back();
			}
		}
		return 0;
	}

	virtual std::any visitCondition(TELParser::ConditionContext *ctx) override {
		tokenCounter++;
		inCondCounter++;
		writeChild(ctx);
		inCondCounter--;
		return 0;
	}

	virtual std::any visitForCommon(TELParser::ForCommonContext *ctx) override {
		inLoopCounter++;
		tokenCounter++;
		writeChild(ctx);
		inLoopCounter--;
		return 0;
	}

	virtual std::any visitForArg(TELParser::ForArgContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitForEach(TELParser::ForEachContext *ctx) override {
		inLoopCounter++;
		tokenCounter++;
		writeChild(ctx);
		inLoopCounter--;
		return 0;
	}

	virtual std::any visitCurlyBrack(TELParser::CurlyBrackContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitReturnTEL(TELParser::ReturnTELContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitVarDecl(TELParser::VarDeclContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitType(TELParser::TypeContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitAssign(TELParser::AssignContext *ctx) override {
		if(inProcess && ctx->children.size()>1){
      		checkForLock = true;
    	}
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitOrTEL(TELParser::OrTELContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitAndTEL(TELParser::AndTELContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitComparison(TELParser::ComparisonContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitRelational(TELParser::RelationalContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitMathLow(TELParser::MathLowContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitMathHigh(TELParser::MathHighContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitUnary(TELParser::UnaryContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitSymbol(TELParser::SymbolContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitIdentifier(TELParser::IdentifierContext *ctx) override {
		// If it is in a process and it is accessing the context
		if(inProcess && checkForLock){
			if(ctx->ID(0)->toString() == "ctx") {
				// The counter of tokens is varying, so we keep a range of token numbers we should look for
				for(int i = tokenCounter; i >= tokenCounter - 5; i--) {
					std::string ctxVar = ctx->ID(1)->toString();
					std::vector tokenNum = EPUnlockLocations[currentEPName][ctxVar];
					// Checks if the i is one of the token numbers that should be unlocked
					if(currentEPName != "" && std::count(tokenNum.begin(), tokenNum.end(), i)) {
						// Checks whether the variable is already in the unlock list
						if(!std::count(unlockVars.begin(), unlockVars.end(), ctxVar))
							unlockVars.push_back(ctxVar);
						break;
					}
				}
			}
			checkForLock = false;
		}
		tokenCounter++;
		writeChild(ctx);
		//writeunlock()
		return 0;
	}

	virtual std::any visitBuiltFunc(TELParser::BuiltFuncContext *ctx) override {
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

};

