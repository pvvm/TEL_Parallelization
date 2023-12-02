#include <vector>
#include <string>
#include <iostream>

struct node{
  std::vector<node*> children;
  std::vector<node*> parents;
  int id;
  int val = -1;
};
struct graph
{
  node* start;
  node* curr;
  int id=0;

  void add(int num){
    curr->val = num;
  }

  graph(){
    start = new node();
    start->id=id++;
    curr = start;
  }

  void addChild(node* newNode){
    newNode->id=id++;
    newNode->parents.push_back(curr);
    curr->children.push_back(newNode);
    curr = newNode;
  }
  void addParent(node* newNode){
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
        std::cout<< a->id<<"("<<a->val<<")"<<": is leaf"<<std::endl;
    }
    else{
        for(auto child: a->children){
          std::cout<< a->id<<"("<<a->val<<")"<<" is the parent of: "<<child->id<<std::endl;
            print(child,visited);
        }
    }
  }




  std::vector<int> getLocks(){
        std::vector<bool> visited(id,false);
        std::vector<int> locks;
        getLocks(curr,visited,locks);
        return locks;
    }

  void getLocks(node* a,std::vector<bool> &visited,std::vector<int>&locks){
    if(visited[a->id]){
      return;
    }
    visited[a->id]=true;
    if(a->val!=-1){
      locks.push_back(a->val);
      std::cout<<"unlock added at: "<<a->id<<std::endl;
      return;
    }
    for(auto parent: a->parents){
        getLocks(parent,visited,locks);
      }
    }
};