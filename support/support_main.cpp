#include <iostream>
#include "support.h"

int main () {
  std::vector<int> data = readFile("example.txt");

  for(int n : data){
    std::cout << n << std::endl;
  }
  return 0;
}