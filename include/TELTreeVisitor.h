
// Generated from TEL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "../grammar/TELVisitor.h"
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include "utils.h"




class  TELTreeVisitor : public TELVisitor {
private:
  std::map<std::string,std::set<std::string>> lockMap;
  std::map<std::string,std::map<std::string,graph*> >usageTree;
  std::map<std::string, graph*>EPTree;
  std::string currProcess;
  bool inProcess = false;
  bool checkForLock = false;
  int counter = 0;
public:

  TELTreeVisitor():TELVisitor(){
    counter=0;
  }

  std::map<std::string,std::map<std::string,graph*> > getUsageTree(){
    return usageTree;
  }
  void printTree(){
    for(auto processTree: EPTree){
      std::cout << "*************************" <<processTree.first<< std::endl;
      processTree.second->print();
    }
  }

  std::map<std::string, std::map<std::string, std::vector<int>>> getLocks(){
    std::map<std::string, std::map<std::string, std::vector<int>>> nodesLock;
    for(auto processTree: EPTree){
      std::cout << "*************************" <<processTree.first<< std::endl;
      processTree.second->getLocks(lockMap[processTree.first], nodesLock[processTree.first]);
    }
    return nodesLock;
  }

  virtual std::any visitInitial(TELParser::InitialContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitDispatcher(TELParser::DispatcherContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitDispEPs(TELParser::DispEPsContext *ctx) override {
    if(ctx->ID().size()>0)
      std::cout<<ctx->ID(0)->toString()<<std::endl;
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitStructLike(TELParser::StructLikeContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitOnlyVarDecl(TELParser::OnlyVarDeclContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitEventProc(TELParser::EventProcContext *ctx) override {
    inProcess = true;
    currProcess = ctx->ID(0)->toString();
    EPTree[currProcess] = new graph();
    std::any out = visitChildren(ctx);
    inProcess = false;
    counter++;
    return out;
  }

  virtual std::any visitStatement(TELParser::StatementContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(TELParser::ConditionContext *ctx) override {
    std::any out = visit(ctx->children[2]);
    node* branchStart;
    node* branchEnd;

    branchStart = EPTree[currProcess]->curr;
    EPTree[currProcess]->addChild(new node);

    visit(ctx->children[4]);

    branchEnd = new node;
    EPTree[currProcess]->addChild(branchEnd);
    EPTree[currProcess]->curr=branchStart;
    
    if(ctx->children.size()==7){
      EPTree[currProcess]->addChild(new node);
      visit(ctx->children[6]);
    }
    EPTree[currProcess]->addChild(branchEnd);
    counter++;
    return out;
  }

  virtual std::any visitForCommon(TELParser::ForCommonContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitForArg(TELParser::ForArgContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitForEach(TELParser::ForEachContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitCurlyBrack(TELParser::CurlyBrackContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitReturnTEL(TELParser::ReturnTELContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(TELParser::VarDeclContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitType(TELParser::TypeContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitAssign(TELParser::AssignContext *ctx) override {
    if(inProcess && ctx->children.size()>1){
      checkForLock = true;
    }
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitOrTEL(TELParser::OrTELContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitAndTEL(TELParser::AndTELContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitComparison(TELParser::ComparisonContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitRelational(TELParser::RelationalContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitMathLow(TELParser::MathLowContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitMathHigh(TELParser::MathHighContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitUnary(TELParser::UnaryContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitSymbol(TELParser::SymbolContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(TELParser::IdentifierContext *ctx) override {
    if(inProcess && checkForLock){
      if(ctx->ID(0)->toString()=="ctx"){
        EPTree[currProcess]->add(ctx->ID(1)->toString(),counter);
        lockMap[currProcess].insert(ctx->ID(1)->toString());
      }
      checkForLock =false;
    }
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitBuiltFunc(TELParser::BuiltFuncContext *ctx) override {
    counter++;
    return visitChildren(ctx);
  }


};

