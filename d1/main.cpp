#include <iostream>
#include "support/support.h"

int main(int argc, char *argv[])
{
  std::string fileName = findFileLocation(argc, argv, "input.txt");
  std::vector<int> data = readFileIntegers(fileName);

  std::cout << "Part 1:" << std::endl;

  for (unsigned int i = 0; i < data.size(); i++)
  {
    for (unsigned int j = i; j < data.size(); j++)
    {
      if ((data.at(i) + data.at(j)) == 2020)
      {
        std::cout << data.at(i) * data.at(j) << std::endl;
      }
    }
  }

  std::cout << "Part 2:" << std::endl;

  for (unsigned int i = 0; i < data.size(); i++)
  {
    for (unsigned int j = i; j < data.size(); j++)
    {
      for (unsigned int k = j; k < data.size(); k++)
      {
        if ((data.at(i) + data.at(j) + data.at(k)) == 2020)
        {
          std::cout << data.at(i) * data.at(j) * data.at(k) << std::endl;
        }
      }
    }
  }

  return 0;
}