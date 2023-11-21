
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

	std::string writeAndIndentation(std::string token, std::string nextToken, std::string indentation) {
		std::string symbols = ".()[]";
		if(nextToken != "" && (symbols.find(nextToken) < symbols.length()) || (symbols.find(token) < symbols.length())) {
			outputFile << token;
			std::cout << token + " "+ nextToken << std::endl;
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

	virtual std::any visitInitial(TELParser::InitialContext *ctx) override {
		//std::cout<<ctx->toStringTree()<<std::endl;
		//writeChild(ctx);
		writeChild(ctx);
		
		return 0;
	}

	virtual std::any visitDispatcher(TELParser::DispatcherContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitDispEPs(TELParser::DispEPsContext *ctx) override {
		inDispatch = true;
		writeChild(ctx);
		inDispatch = false;
		return 0;
	}

	virtual std::any visitStructLike(TELParser::StructLikeContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitOnlyVarDecl(TELParser::OnlyVarDeclContext *ctx) override {
		//indentationCounter++;
		writeChild(ctx);
		//indentationCounter--;
		return 0;
	}

	virtual std::any visitEventProc(TELParser::EventProcContext *ctx) override {
		//indentationCounter++;
		writeChild(ctx);
		//indentationCounter--;
		return 0;
	}

	virtual std::any visitStatement(TELParser::StatementContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitCondition(TELParser::ConditionContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitForCommon(TELParser::ForCommonContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitForArg(TELParser::ForArgContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitForEach(TELParser::ForEachContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitCurlyBrack(TELParser::CurlyBrackContext *ctx) override {
		//indentationCounter++;
		writeChild(ctx);
		//indentationCounter--;
		return 0;
	}

	virtual std::any visitReturnTEL(TELParser::ReturnTELContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitVarDecl(TELParser::VarDeclContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitType(TELParser::TypeContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitAssign(TELParser::AssignContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitOrTEL(TELParser::OrTELContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitAndTEL(TELParser::AndTELContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitComparison(TELParser::ComparisonContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitRelational(TELParser::RelationalContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitMathLow(TELParser::MathLowContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitMathHigh(TELParser::MathHighContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitUnary(TELParser::UnaryContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitSymbol(TELParser::SymbolContext *ctx) override {
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitIdentifier(TELParser::IdentifierContext *ctx) override {
		//std::cout<<ctx->children[0]->getText()<<std::endl;
		writeChild(ctx);
		return 0;
	}

	virtual std::any visitBuiltFunc(TELParser::BuiltFuncContext *ctx) override {
		//for(int i = 0; i < ctx->children.size(); i++) {
		//	outputFile << ctx->children[i]->getText() + "\n";
		//}
		writeChild(ctx);
		return 0;
	}

};

