using namespace std;

#include <iostream>
#include <fstream>
#include<string>

class Trie{
  class Node{
    public:
    bool isWord;
    Node* next[26];
    Node();
  };
  Node* root;
  public:
  Trie();
  void add(const string& w);
  void addFile(string file);
  bool contains(const string& w);
};