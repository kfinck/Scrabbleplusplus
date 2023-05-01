using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include "wordChecker.h"



Trie::Node::Node(){
  isWord = false;
  for (int i = 0; i < 26; i++) {
    next[i] = nullptr;
  }
}

Trie::Trie(){
  root = new Node;
  //idk
}
void Trie::add(const string& w){
  Node* p;
  p = root;
  /*
  int len = w.length();
  char c;*/
  int ic;
  
  for(char c : w){
    ic = c - 'a';
    if (p->next[ic] == nullptr){
      p->next[ic] = new Node;
    }
    p = p->next[ic];
  }
  p->isWord = true;

}

void Trie::addFile(string file){
  ifstream dictionary;
  dictionary.open(file);
  string line;
  
  if (dictionary.is_open()){
    
    cout << "File is open and ready" << '\n';
    cout << " " << '\n';
    
    while( !dictionary.eof()){
      dictionary >> line;
      //cout << line << endl;
      add(line);
    }
    cout << "dictionary added" << endl;
  }
  else{
    cout << "Dictionary not found!" << '\n';
    cout << " " << '\n';
  }
  dictionary.close();
}

bool Trie::contains(const string& w){
  Node* p;
  p = root;
  //int len = w.length();
  int ic;

  for(char c : w){
    ic = c - 'A';
    if (p->next[ic] != nullptr){
      p = p->next[ic];
    }
    else{
      return false;
    }
  }
  return p->isWord;
}
