
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

	std::string writeAndIndentation(std::string token, std::string nextToken, std::string indentation) {
		std::string symbols = ".()[]";
		if(nextToken != "" && (symbols.find(nextToken) < symbols.length()) || (symbols.find(token) < symbols.length())) {
			outputFile << token;
			//std::cout << token + " "+ nextToken << std::endl;
		}
		else
			outputFile << token + " ";

		if(token == "{") {
			indentationCounter++;
			indentation += "\t";
		} else if(token == "}") {
			indentationCounter--;
			if (!indentation.empty())
				indentation.erase(indentation.end() - 1);
		}

		if(!inDispatch && token == "{" || token == "}" || token == ";") {
			outputFile << "\n" + indentation;
		}
		return indentation;
	}

	template <class T> void writeChild(T *ctx) {
		std::string token;
		std::string nextToken;
		std::string indentation;
		for(int i = 0; i < indentationCounter; i++)
			indentation += "\t";

		for(int i = 0; i < ctx->children.size(); i++) {
			token = ctx->children[i]->getText();
			nextToken = "";
			if (i+1 < ctx->children.size() && ctx->children[i+1]->children.size() == 0)
				nextToken = ctx->children[i+1]->getText();

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
		//std::cout<<ctx->toStringTree()<<std::endl;
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
		//indentationCounter++;
		tokenCounter++;
		writeChild(ctx);
		//indentationCounter--;
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
		if(inLoopCounter == 0) {
			while(unlockVars.size() > 0) {
				// TODO: change ctx to the id used in the EP for the context
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
		//indentationCounter++;
		tokenCounter++;
		writeChild(ctx);
		//indentationCounter--;
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
		//std::cout<<ctx->children[0]->getText()<<std::endl;
		if(inProcess && checkForLock){
			if(ctx->ID(0)->toString() == "ctx") {
				//std::cout << "generator" << ctx->ID(1)->toString() << tokenCounter << std::endl;
				for(int i = tokenCounter; i >= tokenCounter - 5; i--) {
					//std::cout << currentEPName << std::endl;
					std::string ctxVar = ctx->ID(1)->toString();
					std::vector tokenNum = EPUnlockLocations[currentEPName][ctxVar];
					//for(auto token: tokenNum)
					if(currentEPName != "" && std::count(tokenNum.begin(), tokenNum.end(), i)) {
						//std::cout << "unlock " << ctxVar << std::endl;
						unlockVars.push_back(ctxVar);
						break;
					}
				}
			}
			checkForLock = false;
		}
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitBuiltFunc(TELParser::BuiltFuncContext *ctx) override {
		//for(int i = 0; i < ctx->children.size(); i++) {
		//	outputFile << ctx->children[i]->getText() + "\n";
		//}
		tokenCounter++;
		writeChild(ctx);
		return 0;
	}

};

