
// Generated from TEL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "../grammar/TELVisitor.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>


/**
 * This class provides an empty implementation of TELVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  TELTreeVisitor : public TELVisitor {
private:
  std::map<std::string,std::vector<std::string>> lockMap;
  std::string currProcess;
  bool inProcess = false;
  bool checkForLock = false;
public:

  virtual std::any visitInitial(TELParser::InitialContext *ctx) override {
    //std::cout<< "initial"<<std::endl;
    return visitChildren(ctx);
  }

  virtual std::any visitDispatcher(TELParser::DispatcherContext *ctx) override {
    //std::cout<< "Dispatcher"<<std::endl;
    return visitChildren(ctx);
  }

  virtual std::any visitDispEPs(TELParser::DispEPsContext *ctx) override {
    if(ctx->ID().size()>0)
      std::cout<<ctx->ID(0)->toString()<<std::endl;
    return visitChildren(ctx);
  }

  virtual std::any visitStructLike(TELParser::StructLikeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOnlyVarDecl(TELParser::OnlyVarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEventProc(TELParser::EventProcContext *ctx) override {
    inProcess = true;
    currProcess = ctx->ID(0)->toString();
    std::any out = visitChildren(ctx);
    inProcess = false;
    return out;
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
    if(inProcess && ctx->children.size()>1){
      checkForLock = true;
    }
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
    return visitChildren(ctx);
  }

  virtual std::any visitMathHigh(TELParser::MathHighContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary(TELParser::UnaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSymbol(TELParser::SymbolContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(TELParser::IdentifierContext *ctx) override {
    if(inProcess && checkForLock){
      if(ctx->ID(0)->toString()=="ctx"){
        lockMap[currProcess].push_back(ctx->ID(1)->toString());
        std::cout<<currProcess<<": "<<ctx->ID(1)->toString()<<std::endl;
      }
      checkForLock =false;
    }
    return visitChildren(ctx);
  }

  virtual std::any visitBuiltFunc(TELParser::BuiltFuncContext *ctx) override {
    return visitChildren(ctx);
  }


};

