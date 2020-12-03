#include <iostream>
#include <algorithm>
#include <map>
#include <functional>
#include "support/support.h"

std::vector<std::string> seperatePersons(std::vector<std::string> data);
bool validPassport(std::string onePerson);

int main(int argc, char *argv[])
{
  std::string fileName = findFileLocation(argc, argv, "input.txt");
  std::vector<std::string> data = readFileStrings(fileName);

  std::vector<std::string> seperatedData = seperatePersons(data);
  unsigned int numberOfValidPassports = 0;
  for (std::string onePerson : seperatedData)
  {
    if (validPassport(onePerson))
    {
      numberOfValidPassports++;
    }
  }

  std::cout << "Number of valid passports are: " << numberOfValidPassports << std::endl;

  return 0;
}

std::vector<std::string> seperatePersons(std::vector<std::string> data)
{
  std::vector<std::string> output;
  std::string tempPerson = "";

  for (std::string line : data)
  {
    if (line.size() == 0)
    {
      output.emplace_back(tempPerson);
      tempPerson = "";
    }
    else
    {
      tempPerson += line + " ";
    }
  }
  //Final person if data doesn't end with an empty line.
  if (tempPerson.size() != 0)
  {
    output.emplace_back(tempPerson);
  }

  return output;
}

bool validPassport(std::string onePerson)
{
  std::map<std::string, std::function<bool(std::string)>> keyMap;

  auto integerCheck = [](std::string input, int lower, int upper) {
    int value = stoi(input);
    return value >= lower && upper >= value;
  };

  keyMap.emplace("byr", [integerCheck](std::string input) { return integerCheck(input, 1920, 2002); });

  keyMap.emplace("iyr", [integerCheck](std::string input) { return integerCheck(input, 2010, 2020); });

  keyMap.emplace("eyr", [integerCheck](std::string input) { return integerCheck(input, 2020, 2030); });

  keyMap.emplace("hgt", [integerCheck](std::string input) {
    if (input.find("cm") != std::string::npos)
    {
      return integerCheck(input.substr(0, 3), 150, 193);
    }
    else if (input.find("in") != std::string::npos)
    {
      return integerCheck(input.substr(0, 2), 59, 76);
    }
    return false;
  });

  keyMap.emplace("hcl", [](std::string input) {
    if (input.size() != 7)
    {
      return false;
    }
    if (input.substr(0, 1) != "#")
    {
      return false;
    }
    std::string validSing = "0123456789abcdef";
    for (unsigned int i = 1; i < input.size(); i++)
    {
      if (validSing.find(input.substr(i, 1)) == std::string::npos)
      {
        return false;
      }
    }
    return true;
  });

  keyMap.emplace("ecl", [](std::string input) {
    std::vector<std::string> validData = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    if (input.size() != 3)
    {
      return false;
    }
    for (std::string valid : validData)
    {
      if (input == valid)
      {
        return true;
      }
    }
    return false;
  });

  keyMap.emplace("pid", [](std::string input) {
    std::string validSing = "0123456789";

    if (input.size() != 9)
    {
      return false;
    }

    for (unsigned int i = 0; i < input.size(); i++)
    {
      if (validSing.find(input.substr(i, 1)) == std::string::npos)
      {
        return false;
      }
    }
    return true;
  });

  //std::cout << oneLinePerson << std::endl;
  for (std::map<std::string, std::function<bool(std::string)>>::iterator it = keyMap.begin(); it != keyMap.end(); ++it)
  {
    int position = onePerson.find(it->first + ":");
    if (position == (int)std::string::npos)
    {
      return false;
    }
    unsigned int colonPosition = onePerson.find(":", position) + 1;
    unsigned int nextSpace = onePerson.find(" ", position);

    std::string value = onePerson.substr(colonPosition, nextSpace - colonPosition);
    //std::cout << "Key: " << it->first + ":" << " - Value: " << value << std::endl;

    if (!((it->second)(value)))
    {
      return false;
    }
  }
  return true;
}