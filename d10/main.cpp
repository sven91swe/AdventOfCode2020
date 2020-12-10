#include <iostream>
#include <algorithm>
#include <limits.h>
#include "support/support.h"

void solution(int argc, char *argv[], std::string inputFile);
int possibleCombination(const std::vector<int> &data, int index, int toIndex, int previousValue);

int main(int argc, char *argv[])
{
  solution(argc, argv, "input_example.txt");
  solution(argc, argv, "input_example2.txt");
  solution(argc, argv, "input.txt");


  return 0;
}

void solution(int argc, char *argv[], std::string inputFile)
{
  std::cout << "File: " << inputFile << std::endl;
  std::string fileName = findFileLocation(argc, argv, inputFile);
  std::vector<int> data = readFileIntegers(fileName);
  data.emplace_back(0); //Add starting point

  std::sort(data.begin(), data.end());
  int changeBy1 = 0;
  int changeBy3 = 1; //Built into device

  std::vector<int> mustHave;
  mustHave.emplace_back(0);

  
  for (int i = 1; i < data.size(); i++)
  {
    if ((data.at(i) - data.at(i - 1)) == 1)
    {
      changeBy1++;
    }
    else if ((data.at(i) - data.at(i - 1)) == 3)
    {
      changeBy3++;

      if(std::find(mustHave.begin(), mustHave.end(), i - 1) == mustHave.end()){
        mustHave.emplace_back(i-1);
      }
      mustHave.emplace_back(i);
    }
  }
  
  if((data.size() - 1) != mustHave.at(mustHave.size() - 1)){
    mustHave.emplace_back(data.size() - 1);
  }

  std::cout << changeBy3 << " - " << changeBy1 << " - " << changeBy3 * changeBy1 << std::endl;
  long long int numberOfCombinations = 1;
  
  for(int i=1; i < mustHave.size(); i++){
    int lowerIndex = mustHave.at(i-1);
    int upperIndex = mustHave.at(i);
    int combinations = possibleCombination(data, lowerIndex + 1, upperIndex, data.at(lowerIndex));
    //std::cout << lowerIndex << "(" << data.at(lowerIndex) << ") " << upperIndex << "(" << data.at(upperIndex) << ") " << combinations << " - " << std::flush;
    numberOfCombinations *= combinations;
  }
  std::cout << std::endl << numberOfCombinations << std::endl;  
}

int possibleCombination(const std::vector<int> &data, int index, int toIndex, int previousValue){
  if((data.at(index) - previousValue) <= 3){
    if(toIndex == index){
      return 1;
    }else{
      return possibleCombination(data, index + 1, toIndex, previousValue) +
      possibleCombination(data, index + 1, toIndex, data.at(index));
    }
  }
  return 0;
}