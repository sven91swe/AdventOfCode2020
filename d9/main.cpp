#include <iostream>
#include <limits.h>
#include "support/support.h"

int firstError(std::vector<long long int> &data, int offset){
  for(unsigned int i = offset; i<data.size(); i++){
    bool foundSumInPreviousSet = false;
    for (unsigned int j = i-offset; j < i; j++)
    {
      for (unsigned int k = j; k < i; k++)
      {
        foundSumInPreviousSet |= (data.at(j) + data.at(k)) == data.at(i);
      }
    }

    if(!foundSumInPreviousSet){
      return data.at(i);
    }
  }

  return -1;
}

long long int breakEncryption(std::vector<long long int> &data, long long int targetSum){
  int i = 0;
  int j = 0;

  long long int sum = data.at(0);

  while(sum != targetSum){
    if(sum < targetSum){
      j++;
      sum += data.at(j);
    }else{
      sum -= data.at(i);
      i++;
    }
  }

  long long int min = LLONG_MAX;
  long long int max = 0;

  for(int k = i; k<=j; k++){
    if(data.at(k) < min){
      min = data.at(k);
    }
    if(data.at(k) > max){
      max = data.at(k);
    }
  }

  return min + max;
}

int main(int argc, char *argv[])
{
  std::string fileName = findFileLocation(argc, argv, "input.txt");
  std::vector<long long int> data = readFileLargeIntegers(fileName);

  long long firstE = firstError(data, 25);
  std::cout << "Part 1:" << std::endl;
  std::cout << "First error: " << firstE << std::endl;

  std::cout << "Part 2:" << std::endl;
  std::cout << "Sum of lowest and highest in sequence: " << breakEncryption(data, firstE) << std::endl;

  return 0;
}