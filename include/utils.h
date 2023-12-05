#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>

struct node{
  std::vector<node*> children;
  std::vector<node*> parents;
  int id=-1;
  std::map<std::string,int> variableLocation;
};
struct graph
{
  node* start;
  node* curr;
  int id=0;

  void add(std::string var,int num){
    curr->variableLocation[var] = num;
  }

  graph(){
    start = new node();
    start->id=id++;
    curr = start;
  }

  void addChild(node* newNode){
    if(newNode->id == -1)
      newNode->id=id++;
    newNode->parents.push_back(curr);
    curr->children.push_back(newNode);
    curr = newNode;
  }
  void addParent(node* newNode){
    if(newNode->id == -1)
      newNode->id=id++;
    newNode->children.push_back(curr);
    curr->parents.push_back(newNode);
    curr = newNode;
    start = newNode;
  }

    void print(){
        std::vector<bool> visited(id,false);
        print(start,visited);
    }

  void print(node* a,std::vector<bool> &visited){
    if(visited[a->id]){
      return;
    }
    visited[a->id]=true;
    if(a->children.size()==0){
        std::cout<< a->id<<": is leaf"<<std::endl;
    }
    else{
        for(auto child: a->children){
          std::cout<< a->id<<" is the parent of: "<<child->id<<std::endl;
            print(child,visited);
        }
    }
  }

  std::map<std::string,std::vector<int>> getLocks(std::set<std::string> vars, std::map<std::string, std::vector<int>>&nodesId){
      std::map<std::string,std::vector<int>> lockMap;
        for(auto var: vars){
          std::cout<<"curr variable: "<<var<<std::endl;
          std::vector<bool> visited(id,false);
          std::vector<int> locks;
          getLocks(curr,visited,locks,var, nodesId[var]);
          std::sort(nodesId[var].begin(), nodesId[var].end());
          lockMap[var]=locks;
        }
        return lockMap;
    }

  void getLocks(node* a,std::vector<bool> &visited,std::vector<int>&locks,std::string var, std::vector<int>&nodesId){
    if(visited[a->id]){
      return;
    }
    visited[a->id]=true;
    if(a->variableLocation.count(var)>0){
      locks.push_back(a->variableLocation[var]);
      nodesId.push_back(a->id);
      std::cout<<"unlock added at: "<<a->id<<std::endl;
      return;
    }
    for(auto parent: a->parents){
        getLocks(parent,visited,locks,var, nodesId);
      }
    }
};