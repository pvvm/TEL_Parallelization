
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
		return visitChildren(ctx);
	}

	virtual std::any visitDispatcher(TELParser::DispatcherContext *ctx) override {
		//std::cout<<ctx->toString();
		return visitChildren(ctx);
	}

	virtual std::any visitDispEPs(TELParser::DispEPsContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitStructLike(TELParser::StructLikeContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitOnlyVarDecl(TELParser::OnlyVarDeclContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitEventProc(TELParser::EventProcContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitStatement(TELParser::StatementContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitCondition(TELParser::ConditionContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitForCommon(TELParser::ForCommonContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitForArg(TELParser::ForArgContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitForEach(TELParser::ForEachContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitCurlyBrack(TELParser::CurlyBrackContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitReturnTEL(TELParser::ReturnTELContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitVarDecl(TELParser::VarDeclContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitType(TELParser::TypeContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitAssign(TELParser::AssignContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitOrTEL(TELParser::OrTELContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitAndTEL(TELParser::AndTELContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitComparison(TELParser::ComparisonContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitRelational(TELParser::RelationalContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual std::any visitMathLow(TELParser::MathLowContext *ctx) override {
		writeChild(ctx);
		return visitChildren(ctx);
	}

	virtual std::any visitMathHigh(TELParser::MathHighContext *ctx) override {
		writeChild(ctx);
		return visitChildren(ctx);
	}

	virtual std::any visitUnary(TELParser::UnaryContext *ctx) override {
		writeChild(ctx);
		return visitChildren(ctx);
	}

	virtual std::any visitSymbol(TELParser::SymbolContext *ctx) override {
		writeChild(ctx);
		return visitChildren(ctx);
	}

	virtual std::any visitIdentifier(TELParser::IdentifierContext *ctx) override {
		//std::cout<<ctx->children[0]->getText()<<std::endl;
		writeChild(ctx);
		return visitChildren(ctx);
	}

	virtual std::any visitBuiltFunc(TELParser::BuiltFuncContext *ctx) override {
		//for(int i = 0; i < ctx->children.size(); i++) {
		//	std::cout<<ctx->children[i]->getText()<<std::endl;
		//}
		writeChild(ctx);
		return visitChildren(ctx);
	}

	template <class T> void writeChild(T *ctx) {
		bool wrote = false;
		for(int i = 0; i < ctx->children.size(); i++) {
			if (ctx->children[i]->children.size() == 0) {
				outputFile << ctx->children[i]->getText();
				wrote = true;
			}
		}
		if(wrote)
			outputFile << "\n";
	}

};

