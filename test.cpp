using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include "wordChecker.h"


int main(int argc, char* argv[]){
  Trie a;
  string path = argv[0];
  path.resize(path.length() - 5); //remove exe name from path -- this will have to be changed based on name of executable hehe
  string dPath = path + "ScrabbleDict.txt"; //add dictionary file name
  cout << dPath << endl;
  a.addFile(dPath);
  
  
  cout << "Goodbye" << endl;
}