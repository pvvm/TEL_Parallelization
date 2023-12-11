#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>

struct node{
  std::vector<node*> children;
  std::vector<node*> parents;
  int id=-1;
  std::map<std::string,int> variableLocation;
  std::map<std::string,bool> lock;
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
          std::vector<bool> visited2(id,false);
          std::vector<bool> visited3(id,false);
          std::vector<int> locks;
          showVariableUses(curr,visited,var);
          getUnlocks(curr,visited2,locks,var, nodesId[var]);
          storeUnlocks(curr,visited3,locks,var, nodesId[var]);
          std::sort(nodesId[var].begin(), nodesId[var].end());
          lockMap[var]=locks;
        }
        return lockMap;
    }

  void showVariableUses(node* a,std::vector<bool> &visited,std::string var){
    if(visited[a->id]){
      return;
    }
    visited[a->id]=true;
    if(a->variableLocation.count(var)>0){
      std::cout<<"variable used at: "<<a->id<<std::endl;
      return;
    }

    for(auto parent: a->parents){
        showVariableUses(parent,visited,var);
      }
    }

    node* moveTo(node* a){
      while(a ->parents.size()==1&& a ->children.size()>0){
        a = a->children[0];
      }
      return a;
    }

  void storeUnlocks(node* a,std::vector<bool> &visited,std::vector<int>&locks,std::string var, std::vector<int>&nodesId){
    if(visited[a->id]){
      return;
    }
    visited[a->id]=true;
    if(a->lock[var]){
      nodesId.push_back(a->variableLocation[var]);
      locks.push_back(a->variableLocation[var]);
      std::cout<<"* variable unlocked at: "<<a->id<<std::endl;
    }

    for(auto parent: a->parents){
        storeUnlocks(parent,visited,locks,var, nodesId);
      }
  }

  void getUnlocks(node* a,std::vector<bool> &visited,std::vector<int>&locks,std::string var, std::vector<int>&nodesId, bool locked = false, node* lock_location = NULL){
    if(a->lock.count(var)==0){
      a->lock[var] = false;
    }
    if((a->variableLocation.count(var)>0) && !locked){
      if(!(visited[a->id]&&!a->lock[var]))
      {
        // locks.push_back(a->variableLocation[var]);
        // nodesId.push_back(a->variableLocation[var]);
        a->lock[var]=true;
        locked = true;
        lock_location =a;
        //std::cout<<"unlock added at: "<<a->id<<std::endl;
        }
    }
    else if(a->variableLocation.count(var)>0 && locked){
      // locks.(a->variableLocation[var]);
      // nodesId.push_back(a->variableLocation[var]);
      a->lock[var]=false;
      node* dest = moveTo(lock_location);
      dest->lock[var] = true;
      //std::cout<<"duplicate lock at: "<<a->id<<std::endl;
      //std::cout<<"unlock moved to: "<<dest->id<<std::endl;
    }
    visited[a->id]=true;
    for(auto parent: a->parents){
        getUnlocks(parent,visited,locks,var, nodesId,locked,lock_location);
    }

  }
};