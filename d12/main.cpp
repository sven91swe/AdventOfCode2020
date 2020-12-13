#include <iostream>
#include <algorithm>
#include <regex>
#include "support/support.h"

enum class Direction
{
  N,
  S,
  E,
  W,
  L,
  R,
  F
};

struct NavigationInstruction
{
  Direction dir;
  int value;
};

NavigationInstruction interpretNavigationInstruction(std::string line)
{
  NavigationInstruction output;
  std::smatch match;
  regex re("^([A-Za-z]+)(\\d+)$");
  regex_search(line, match, re);

  std::string key = match.str(1);
  output.value = stoi(match.str(2));

  //std::cout << key << " - " << output.value << std::endl;

  if (key == "N")
  {
    output.dir = Direction::N;
  }
  else if (key == "S")
  {
    output.dir = Direction::S;
  }
  else if (key == "E")
  {
    output.dir = Direction::E;
  }
  else if (key == "W")
  {
    output.dir = Direction::W;
  }
  else if (key == "L")
  {
    output.dir = Direction::L;
  }
  else if (key == "R")
  {
    output.dir = Direction::R;
  }
  else //(key == "F")
  {
    output.dir = Direction::F;
  }
  return output;
}

void updatePosition(Direction d, int value, int &x, int &y)
{
  switch (d){
    case Direction::N:
      x += value;
      break;
    case Direction::S:
      x -= value;
      break;
    case Direction::E:
      y += value;
      break;
    case Direction::W:
      y -= value;
      break;
  }
}

void updateDirection(Direction &d, Direction instruction, int value)
{
  if (instruction == Direction::L)
  {
  }
  else if (instruction == Direction::R)
  {
    value = 720 - value; //I assume that no value is above 720
  }

  while (value > 0)
  {
    value -= 90;

    switch (d)
    {
    case Direction::N:
      d = Direction::W;
      break;
    case Direction::W:
      d = Direction::S;
      break;
    case Direction::S:
      d = Direction::E;
      break;
    case Direction::E:
      d = Direction::N;
      break;
    }
  }
}

void updateDirection2(Direction instruction, int value, int &x, int &y)
{
  if (instruction == Direction::L)
  {
  }
  else if (instruction == Direction::R)
  {
    value = 720 - value; //I assume that no value is above 720
  }

  while (value > 0)
  {
    value -= 90;

    int temp = x;
    x = y;
    y = -temp;
  }
}

int main(int argc, char *argv[])
{
  std::string inputFile = "input.txt";
  std::string fileName = findFileLocation(argc, argv, inputFile);
  std::vector<std::string> data = readFileStrings(fileName);
  std::vector<NavigationInstruction> navigationInstruction;
  for (std::string line : data)
  {
    navigationInstruction.emplace_back(interpretNavigationInstruction(line));
  }

  int x = 0;
  int y = 0;
  Direction currentDirection = Direction::E;
  for (NavigationInstruction i : navigationInstruction)
  {
    if (i.dir == Direction::N ||
        i.dir == Direction::S ||
        i.dir == Direction::E ||
        i.dir == Direction::W)
    {
      updatePosition(i.dir, i.value, x, y);
    }
    else if (i.dir == Direction::F)
    {
      updatePosition(currentDirection, i.value, x, y);
    }
    else if (i.dir == Direction::L ||
             i.dir == Direction::R)
    {
      updateDirection(currentDirection, i.dir, i.value);
    }
  }
  std::cout << x << " " << y << " " << abs(x)+abs(y) << std::endl;

  //Part 2
  x = 0;
  y = 0;
  int waypointX = 1;
  int waypointY = 10;
  for (NavigationInstruction i : navigationInstruction)
  {
    if (i.dir == Direction::N ||
        i.dir == Direction::S ||
        i.dir == Direction::E ||
        i.dir == Direction::W)
    {
      updatePosition(i.dir, i.value, waypointX, waypointY);
    }
    else if (i.dir == Direction::F)
    {
      x += waypointX * i.value;
      y += waypointY * i.value;
    }
    else if (i.dir == Direction::L ||
             i.dir == Direction::R)
    {
      updateDirection2(i.dir, i.value, waypointX, waypointY);
    }
  }
  std::cout << x << " " << y << " " << abs(x)+abs(y) << std::endl;

  return 0;
}