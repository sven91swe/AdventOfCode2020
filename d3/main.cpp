#include <iostream>
#include <algorithm>
#include "support/support.h"

unsigned long int slopeCheck(std::vector<std::string> data, int rightMove, int downMove);

int main(int argc, char *argv[])
{
  std::string fileName = findFileLocation(argc, argv, "input.txt");
  std::vector<std::string> data = readFileStrings(fileName);

  std::cout << "Number of trees (1, 1): " << slopeCheck(data, 1, 1) << std::endl;
  std::cout << "Number of trees (3, 1): " << slopeCheck(data, 3, 1) << std::endl;
  std::cout << "Number of trees (5, 1): " << slopeCheck(data, 5, 1) << std::endl;
  std::cout << "Number of trees (7, 1): " << slopeCheck(data, 7, 1) << std::endl;
  std::cout << "Number of trees (1, 2): " << slopeCheck(data, 1, 2) << std::endl;

  std::cout << "Multiplication: " << slopeCheck(data, 1, 1) * slopeCheck(data, 3, 1) * slopeCheck(data, 5, 1) * slopeCheck(data, 7, 1) * slopeCheck(data, 1, 2) << std::endl;

  return 0;
}

unsigned long int slopeCheck(std::vector<std::string> data, int rightMove, int downMove)
{

  unsigned long int treeCounter = 0;
  unsigned int currentPosition = 0;
  unsigned int currentRow = 0;

  while (currentRow < data.size())
  {
    if (data.at(currentRow).at(currentPosition) == *"#")
    {
      treeCounter++;
    }
    currentPosition = (currentPosition + rightMove) % data.at(currentRow).size();
    currentRow += downMove;
  }

  return treeCounter;
}
