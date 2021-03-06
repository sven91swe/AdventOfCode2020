#include <iostream>
#include <algorithm>
#include <map>
#include <functional>
#include <regex>
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
  std::vector<std::function<bool(std::string)>> passportChecks;

  passportChecks.emplace_back([](std::string full) {
    return regex_search(full, regex("\\s*byr:(19[2-9][0-9]|200[0-2])\\s"));
  });

  passportChecks.emplace_back([](std::string full) {
    return regex_search(full, regex("\\s*iyr:20(1[0-9]|20)\\s"));
  });

  passportChecks.emplace_back([](std::string full) {
    return regex_search(full, regex("\\s*eyr:20(2[0-9]|30)\\s"));
  });

  passportChecks.emplace_back([](std::string full) {
    return regex_search(full, regex("\\s*hgt:(1([5-8][0-9]|9[0-3])cm|(59|6[0-9]|7[0-6])in)\\s"));
  });

  passportChecks.emplace_back([](std::string full) {
    return regex_search(full, regex("\\s*hcl:#[0-9a-f]{6}\\s"));
  });

  passportChecks.emplace_back([](std::string full) {
    return regex_search(full, regex("\\s*ecl:(amb|blu|brn|gry|grn|hzl|oth)\\s"));
  });

  passportChecks.emplace_back([](std::string full) {
    return regex_search(full, regex("\\s*pid:[0-9]{9}\\s"));
  });

  for (std::function<bool(std::string)> check: passportChecks)
  {
    if (!check(onePerson))
    {
      return false;
    }
  }
  return true;
}