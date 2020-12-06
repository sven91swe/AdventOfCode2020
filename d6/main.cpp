#include <iostream>
#include <algorithm>
#include <map>
#include <functional>
#include <regex>
#include "support/support.h"

std::vector<std::string> seperateGroups(std::vector<std::string> data);
int answersPerGroup(std::string onePerson);
int answersPerGroup2(std::string onePerson);

int main(int argc, char *argv[])
{
  std::string fileName = findFileLocation(argc, argv, "input.txt");
  std::vector<std::string> data = readFileStrings(fileName);

  std::vector<std::string> seperatedData = seperateGroups(data);
  unsigned int sumOfAnswerPerGroup = 0;
  unsigned int sumOfAnswerPerGroup2 = 0;
  for (std::string onePerson : seperatedData)
  {
    int answerForGroup = answersPerGroup(onePerson);
    sumOfAnswerPerGroup += answerForGroup;

    int answerForGroup2 = answersPerGroup2(onePerson);
    sumOfAnswerPerGroup2 += answerForGroup2;
    std::cout << onePerson << " " << answerForGroup << " " << answerForGroup2 << std::endl;
  }

  std::cout << "Number of answers are: " << sumOfAnswerPerGroup << " " << sumOfAnswerPerGroup2 << std::endl;

  return 0;
}

std::vector<std::string> seperateGroups(std::vector<std::string> data)
{
  std::vector<std::string> output;
  std::string tempGroup = "";

  for (std::string line : data)
  {
    if (line.size() == 0)
    {
      output.emplace_back(tempGroup);
      tempGroup = "";
    }
    else
    {
      tempGroup += line + " ";
    }
  }
  //Final person if data doesn't end with an empty line.
  if (tempGroup.size() != 0)
  {
    output.emplace_back(tempGroup);
  }

  return output;
}

int answersPerGroup(std::string oneGroup)
{
  std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
  std::vector<std::string> answerKeys;
  for (unsigned int i = 0; i < alphabet.length(); i++)
  {
    answerKeys.emplace_back(alphabet.substr(i, 1));
  }

  int numberOfPresentAnswerKeys = 0;

  for (std::string key : answerKeys)
  {
    if (oneGroup.find(key) != std::string::npos)
    {
      numberOfPresentAnswerKeys++;
    }
  }

  return numberOfPresentAnswerKeys;
}

int answersPerGroup2(std::string oneGroup)
{
  std::function<int(std::string, std::string)> numberOfMatchingStrings = [](std::string input, std::string match) {
    int counts = 0;
    for (char c : input)
    {
      if (c == match.at(0))
      {
        counts++;
      }
    }
    return counts;
  };

  int numberOfMembersInGroup = numberOfMatchingStrings(oneGroup, " ");

  std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
  //std::string alphabet = "abc";
  std::vector<std::string> answerKeys;
  for (unsigned int i = 0; i < alphabet.length(); i++)
  {
    answerKeys.emplace_back(alphabet.substr(i, 1));
  }

  int numberOfPresentAnswerKeys = 0;

  for (std::string key : answerKeys)
  {
    if (numberOfMatchingStrings(oneGroup, key) == numberOfMembersInGroup)
    {
      numberOfPresentAnswerKeys++;
    }
  }

  return numberOfPresentAnswerKeys;
}