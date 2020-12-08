#include <iostream>
#include <algorithm>
#include <map>
#include <functional>
#include <regex>
#include "support/support.h"

struct BagData
{
  std::string name;
  std::map<std::string, int> containsBags;
};

std::map<std::string, BagData> buildBags(std::vector<std::string> data);

bool containsBag(std::map<std::string, BagData> data, std::string startBag, std::string searchName);
int containsNumberOfBags(std::map<std::string, BagData> data, std::string startBag);

int main(int argc, char *argv[])
{
  std::string fileName = findFileLocation(argc, argv, "input.txt");
  std::vector<std::string> data = readFileStrings(fileName);

  std::cout << "Start building map" << std::endl;
  std::map<std::string, BagData> allBags = buildBags(data);
  std::cout << "Map done" << std::endl;
  /*
  for(auto const& p : allBags){
    std::cout << p.first << " contains ";
    for(auto const& p2 : p.second.containsBags){
      std::cout << p2.second << " " << p2.first << " - ";
    }
    std::cout << std::endl;
  }
  */

  std::string searchBag = "shiny gold";

  //Part 1
  std::cout << "Part 1 " << std::endl;
  int numberOfOuterBags = 0;
  for (auto const &p : allBags)
  {
    if (containsBag(allBags, p.first, searchBag))
    {
      numberOfOuterBags++;
    }
  }
  std::cout << numberOfOuterBags << " bags can contain a " << searchBag << " bag" << std::endl;

  //Part 2
  std::cout << "Part 2 " << std::endl;
  std::cout << "A " << searchBag << " bag contains " << containsNumberOfBags(allBags, searchBag) << " other bags" << std::endl;

  return 0;
}

std::map<std::string, BagData> buildBags(std::vector<std::string> data)
{
  std::map<std::string, BagData> output;

  for (std::string line : data)
  {
    BagData oneBag;
    std::smatch match;
    regex re1("^(\\w+ \\w+) bag");
    regex re2("(\\d+) (\\w+ \\w+) bags?");

    regex_search(line, match, re1);
    oneBag.name = match.str(1);

    while (regex_search(line, match, re2))
    {
      oneBag.containsBags.emplace(match.str(2), stoi(match.str(1)));
      line = match.suffix().str();
    }
    output.emplace(oneBag.name, oneBag);
  }
  return output;
}

bool containsBag(std::map<std::string, BagData> data, std::string startBag, std::string searchName)
{
  bool contains = false;
  BagData bag = data.at(startBag);
  for (auto const &p : bag.containsBags)
  {
    contains |= searchName == p.first;
    contains |= containsBag(data, p.first, searchName);
  }
  return contains;
}

int containsNumberOfBags(std::map<std::string, BagData> data, std::string startBag)
{
  int numberOfBags = 0; //Count self
  BagData bag = data.at(startBag);
  for (auto const &p : bag.containsBags)
  {
    //1 for the bag and containsNumberOfBags for all bags it contain.
    numberOfBags += p.second * (1 + containsNumberOfBags(data, p.first));
  }
  return numberOfBags;
}
