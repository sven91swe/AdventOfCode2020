#include <iostream>
#include <algorithm>
#include <limits.h>
#include <functional>
#include "support/support.h"

void updateMap(std::vector<std::string> &toUpdate, const std::vector<std::string> &basedOn);
void updateMap2(std::vector<std::string> &toUpdate, const std::vector<std::string> &basedOn);
bool mapsAreEqual(const std::vector<std::string> &map1, const std::vector<std::string> &map2);
int countSeats(const std::vector<std::string> &map);

int main(int argc, char *argv[])
{
  std::string inputFile = "input.txt";
  std::string fileName = findFileLocation(argc, argv, inputFile);
  std::vector<std::vector<std::string>> data;
  data.emplace_back(readFileStrings(fileName));
  data.emplace_back(readFileStrings(fileName));

  int numberOfUpdates = 0;
  while (true)
  {
    updateMap(data.at((numberOfUpdates + 1) % 2), data.at(numberOfUpdates % 2));
    numberOfUpdates++;
    if (mapsAreEqual(data.at((numberOfUpdates + 1) % 2), data.at(numberOfUpdates % 2)))
    {
      break;
    }
  }
  std::cout << numberOfUpdates << " - " << countSeats(data.at(0)) << std::endl;


  //Part 2
  std::vector<std::vector<std::string>> data2;
  data2.emplace_back(readFileStrings(fileName));
  data2.emplace_back(readFileStrings(fileName));

  numberOfUpdates = 0;
  while (true)
  {
    updateMap2(data2.at((numberOfUpdates + 1) % 2), data2.at(numberOfUpdates % 2));
    numberOfUpdates++;
    if (mapsAreEqual(data2.at((numberOfUpdates + 1) % 2), data2.at(numberOfUpdates % 2)))
    {
      break;
    }
  }
  std::cout << numberOfUpdates << " - " << countSeats(data2.at(0)) << std::endl;

  return 0;
}

void updateMap(std::vector<std::string> &toUpdate, const std::vector<std::string> &basedOn)
{
  std::function<char(int, int)>
      nextState = [basedOn](int x, int y)
  {
    std::function<int(int, int)> personAt = [basedOn](int x, int y) {
      if (x < 0 || y < 0 || x >= basedOn.size() || y >= basedOn.at(0).size())
      {
        return 0;
      }

      if (basedOn.at(x).at(y) == '#')
      {
        return 1;
      }
      return 0;
    };

    int numberOfPeopleAround = 0;
    numberOfPeopleAround += personAt(x - 1, y - 1);
    numberOfPeopleAround += personAt(x - 1, y);
    numberOfPeopleAround += personAt(x - 1, y + 1);
    numberOfPeopleAround += personAt(x, y - 1);
    numberOfPeopleAround += personAt(x, y + 1);
    numberOfPeopleAround += personAt(x + 1, y - 1);
    numberOfPeopleAround += personAt(x + 1, y);
    numberOfPeopleAround += personAt(x + 1, y + 1);

    char currentState = basedOn.at(x).at(y);
    if (currentState == '#')
    {
      if (numberOfPeopleAround >= 4)
      {
        return 'L';
      }
    }
    else if (currentState == 'L')
    {
      if (numberOfPeopleAround == 0)
      {
        return '#';
      }
    }
    return currentState;
  };

  for (unsigned int i = 0; i < toUpdate.size(); i++)
  {
    for (unsigned int j = 0; j < toUpdate.at(i).size(); j++)
    {
      toUpdate.at(i).at(j) = nextState(i, j);
    }
  }
}

void updateMap2(std::vector<std::string> &toUpdate, const std::vector<std::string> &basedOn)
{
  std::function<char(int, int)>
      nextState = [basedOn](int x, int y)
  {
    std::function<int(int, int, int, int)> personAt2 = [basedOn, &personAt2](int x, int y, int directionX, int directionY) {
      x += directionX;
      y += directionY;
      if (x < 0 || y < 0 || x >= basedOn.size() || y >= basedOn.at(0).size())
      {
        return 0;
      }

      if (basedOn.at(x).at(y) == '#')
      {
        return 1;
      }else if(basedOn.at(x).at(y) == '.'){
        return personAt2(x, y, directionX, directionY);
      }
      return 0;
    };

    int numberOfPeopleAround = 0;
    numberOfPeopleAround += personAt2(x, y, -1, -1);
    numberOfPeopleAround += personAt2(x, y, -1, 0);
    numberOfPeopleAround += personAt2(x, y, -1, +1);
    numberOfPeopleAround += personAt2(x, y, 0, -1);
    numberOfPeopleAround += personAt2(x, y, 0, +1);
    numberOfPeopleAround += personAt2(x, y, +1, -1);
    numberOfPeopleAround += personAt2(x, y, +1, 0);
    numberOfPeopleAround += personAt2(x, y, +1, +1);
    
    char currentState = basedOn.at(x).at(y);
    if (currentState == '#')
    {
      if (numberOfPeopleAround >= 5)
      {
        return 'L';
      }
    }
    else if (currentState == 'L')
    {
      if (numberOfPeopleAround == 0)
      {
        return '#';
      }
    }
    return currentState;
  };

  for (unsigned int i = 0; i < toUpdate.size(); i++)
  {
    for (unsigned int j = 0; j < toUpdate.at(i).size(); j++)
    {
      toUpdate.at(i).at(j) = nextState(i, j);
    }
  }
}

bool mapsAreEqual(const std::vector<std::string> &map1, const std::vector<std::string> &map2)
{
  for (unsigned int i = 0; i < map1.size(); i++)
  {
    for (unsigned int j = 0; j < map1.at(i).size(); j++)
    {
      if(map1.at(i).substr(j,1) != map2.at(i).substr(j,1)){
        return false;
      }
    }
  }
  return true;
}

int countSeats(const std::vector<std::string> &map){
  int numberOfSeats = 0;

  for (unsigned int i = 0; i < map.size(); i++)
  {
    for (unsigned int j = 0; j < map.at(i).size(); j++)
    {
      if(map.at(i).substr(j,1) == "#"){
        numberOfSeats++;
      }
    }
  }
  return numberOfSeats;
}