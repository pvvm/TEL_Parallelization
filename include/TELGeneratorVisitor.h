
// Generated from TEL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "../grammar/TELVisitor.h"


/**
 * This class provides an empty implementation of TELVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  TELGeneratorVisitor : public TELVisitor {
public:
	std::ofstream outputFile;

	virtual std::any visitInitial(TELParser::InitialContext *ctx) override {
		//std::cout<<ctx->toStringTree()<<std::endl;
		//writeChild(ctx);
		writeChild(ctx, true);
		return 0;
	}

	virtual std::any visitDispatcher(TELParser::DispatcherContext *ctx) override {
		//std::cout<<ctx->toString();
		writeChild(ctx, true);
		return 0;
	}

	virtual std::any visitDispEPs(TELParser::DispEPsContext *ctx) override {
		writeChild(ctx, true);
		return 0;
	}

	virtual std::any visitStructLike(TELParser::StructLikeContext *ctx) override {
		writeChild(ctx, true);
		return 0;
	}

	virtual std::any visitOnlyVarDecl(TELParser::OnlyVarDeclContext *ctx) override {
		writeChild(ctx, true);
		return 0;
	}

	virtual std::any visitEventProc(TELParser::EventProcContext *ctx) override {
		writeChild(ctx, true);
		return 0;
	}

	virtual std::any visitStatement(TELParser::StatementContext *ctx) override {
		writeChild(ctx, true);
		return 0;
	}

	virtual std::any visitCondition(TELParser::ConditionContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitForCommon(TELParser::ForCommonContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitForArg(TELParser::ForArgContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitForEach(TELParser::ForEachContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitCurlyBrack(TELParser::CurlyBrackContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitReturnTEL(TELParser::ReturnTELContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitVarDecl(TELParser::VarDeclContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitType(TELParser::TypeContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitAssign(TELParser::AssignContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitOrTEL(TELParser::OrTELContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitAndTEL(TELParser::AndTELContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitComparison(TELParser::ComparisonContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitRelational(TELParser::RelationalContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitMathLow(TELParser::MathLowContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitMathHigh(TELParser::MathHighContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitUnary(TELParser::UnaryContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitSymbol(TELParser::SymbolContext *ctx) override {
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitIdentifier(TELParser::IdentifierContext *ctx) override {
		//std::cout<<ctx->children[0]->getText()<<std::endl;
		writeChild(ctx, false);
		return 0;
	}

	virtual std::any visitBuiltFunc(TELParser::BuiltFuncContext *ctx) override {
		//for(int i = 0; i < ctx->children.size(); i++) {
		//	outputFile << ctx->children[i]->getText() + "\n";
		//}
		writeChild(ctx, false);
		return 0;
	}

	template <class T> void writeChild(T *ctx, bool newLine) {
		std::string token;
		for(int i = 0; i < ctx->children.size(); i++) {
			token = ctx->children[i]->getText();
			if (ctx->children[i]->children.size() > 0)
				visit(ctx->children[i]);
			else {
				if (token == "{" || token == "}" || token == ";") {
					outputFile << token + "\n";
				}
				else
					outputFile << token + " ";
			}
		}
		//if(newLine)
		//	outputFile << std::endl;
	}

};

