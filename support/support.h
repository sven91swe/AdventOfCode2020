#ifndef SUPPORT_H
#define SUPPORT_H

// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

std::vector<int> readFile (std::string fileName) {
  
  std::vector<int> data;

  string line;
  ifstream myfile (fileName);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      data.push_back(stoi(line));
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  
  return data;
}





#endif // SUPPORT_H
