#ifndef SUPPORT_H
#define SUPPORT_H

// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

std::vector<std::string> readFileStrings(std::string fileName)
{

  std::vector<std::string> data;

  string line;
  ifstream myfile(fileName);
  if (myfile.is_open())
  {
    while (getline(myfile, line))
    {
      data.push_back(line);
    }
    myfile.close();
  }

  else
    cout << "Unable to open file";

  return data;
}

std::vector<int> readFileIntegers(std::string fileName)
{

  std::vector<std::string> input = readFileStrings(fileName);
  std::vector<int> data;
  for(std::string line : input){
    data.emplace_back(stoi(line));
  }

  return data;
}

std::vector<long long int> readFileLargeIntegers(std::string fileName)
{

  std::vector<std::string> input = readFileStrings(fileName);
  std::vector<long long int> data;
  for(std::string line : input){
    data.emplace_back(stoll(line));
  }

  return data;
}

std::string findFileLocation(int argc, char *argv[], std::string fileName)
{
  (void)argc;

  std::string filePaths = std::string(argv[0]);
  std::size_t found = filePaths.find_last_of("/");
  std::string fullFileName = filePaths + ".runfiles/__main__/" + filePaths.substr(found + 1) + "/" + fileName;

  return fullFileName;
}

#endif // SUPPORT_H
