
// Generated from TEL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "../grammar/TELVisitor.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "utils.h"




class  TELTreeVisitor : public TELVisitor {
private:
  std::map<std::string,std::vector<std::string>> lockMap;
  std::map<std::string,std::map<std::string,graph*> >usageTree;
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
    for(auto processTree: usageTree){
      std::cout << "*************************" <<processTree.first<< std::endl;
    for(auto tree: processTree.second){
      std::cout << "**********" <<tree.first<< std::endl;
      tree.second->print();
    }
    }
  }
  void getLocks(){
    for(auto processTree: usageTree){
      std::cout << "*************************" <<processTree.first<< std::endl;
    for(auto tree: processTree.second){
      std::cout << "**********" <<tree.first<< std::endl;
      tree.second->getLocks();
    }
  }
  }
  // virtual std::any visitChildren(TELParser::InitialContext *ctx){

  // }

  virtual std::any visitInitial(TELParser::InitialContext *ctx) override {
    //std::cout<< "initial"<<std::endl;
    counter++;
    return visitChildren(ctx);
  }

  virtual std::any visitDispatcher(TELParser::DispatcherContext *ctx) override {
    //std::cout<< "Dispatcher"<<std::endl;
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
    std::cout<<ctx->children.size()<<std::endl;
    std::any out = visit(ctx->children[2]);
    std::map<std::string,node*> start;
    std::map<std::string,node*> end;
    node* temp;

    for(std::string var: lockMap[currProcess]){
      start[var] = usageTree[currProcess][var]->curr;
      usageTree[currProcess][var]->addChild(new node);
    }
    visit(ctx->children[4]);
    for(std::string var: lockMap[currProcess]){
        end[var] = new node;
        temp = usageTree[currProcess][var]->curr;
        usageTree[currProcess][var]->addChild(end[var]);
        if(start.count(var)>0){
          usageTree[currProcess][var]->curr=start[var];
        }
        else{
          usageTree[currProcess][var]->curr = usageTree[currProcess][var]->start;
          usageTree[currProcess][var]->addParent(new node);
        }
    }
    if(ctx->children.size()==7){
      for(std::string var: lockMap[currProcess]){
          usageTree[currProcess][var]->addChild(new node);
      }
      visit(ctx->children[6]);
    }
    for(std::string var: lockMap[currProcess]){
      if(end.count(var)>0)
        usageTree[currProcess][var]->addChild(end[var]);
    }
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
        if(usageTree[currProcess].count(ctx->ID(1)->toString())==0){
          lockMap[currProcess].push_back(ctx->ID(1)->toString());
          usageTree[currProcess][ctx->ID(1)->toString()] = new graph();
        }
        usageTree[currProcess][ctx->ID(1)->toString()]->add(counter);
        std::cout<<currProcess<<": "<<ctx->ID(1)->toString()<<std::endl;
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

