#include <iostream>
#include <algorithm>
#include <map>
#include <functional>
#include <regex>
#include "support/support.h"

enum class Operation
{
  nop,
  acc,
  jmp
};

struct ProgramLine
{
  Operation op;
  int value;
};

ProgramLine interpretProgramLine(std::string line)
{
  ProgramLine output;
  std::smatch match;
  regex re("^(\\w+) ([+-]\\d+)$");
  regex_search(line, match, re);

  std::string key = match.str(1);
  output.value = stoi(match.str(2));

  if (key == "acc")
  {
    output.op = Operation::acc;
  }
  else if (key == "jmp")
  {
    output.op = Operation::jmp;
  }
  else
  {
    output.op = Operation::nop;
  }

  return output;
}

int main(int argc, char *argv[])
{
  std::string fileName = findFileLocation(argc, argv, "input.txt");
  std::vector<std::string> data = readFileStrings(fileName);
  std::vector<ProgramLine> programInstructions;
  for(std::string line: data){
    programInstructions.emplace_back(interpretProgramLine(line));
  }

  std::vector<int> visitedLocations;
  int programIndex = 0;
  int accumelator = 0;
  while (find(visitedLocations.begin(), visitedLocations.end(), programIndex) == visitedLocations.end())
  {
    visitedLocations.emplace_back(programIndex);
    ProgramLine pl = programInstructions.at(programIndex);

    switch (pl.op)
    {
    case Operation::nop:
      programIndex++;
      break;
    case Operation::acc:
      programIndex++;
      accumelator += pl.value;
      break;
    case Operation::jmp:
      programIndex += pl.value;
      break;
    }
  }
  std::cout << "Accumelator value: " << accumelator << std::endl;

  return 0;
}
