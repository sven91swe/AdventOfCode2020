#include <iostream>
#include <algorithm>
#include "support/support.h"

bool validPassword(std::string passwordline);
bool validPassword2(std::string passwordline);


int main(int argc, char *argv[])
{
  std::string fileName = findFileLocation(argc, argv, "input.txt");
  std::vector<std::string> data = readFileStrings(fileName);

  std::cout << "Part 1:" << std::endl;
  unsigned int numberOfValidPasswords = 0;
  for(std::string passwordLine: data){
    if(validPassword(passwordLine)){
      numberOfValidPasswords++;
    }
  }
  std::cout << "Number of valid passwords: " << numberOfValidPasswords << std::endl;


  std::cout << "Part 2:" << std::endl;
  numberOfValidPasswords = 0;
  for(std::string passwordLine: data){
    if(validPassword2(passwordLine)){
      numberOfValidPasswords++;
    }
  }
  std::cout << "Number of valid passwords: " << numberOfValidPasswords << std::endl;
  

  return 0;
}


bool validPassword(std::string passwordline){
  int splitPoint = passwordline.find(" ");
  std::string boundaries = passwordline.substr(0,splitPoint);
  std::string letter =  passwordline.substr(splitPoint+1, 1);
  std::string password =  passwordline.substr(splitPoint+4);

  splitPoint = boundaries.find("-");
  unsigned int lowerbound = stoi(boundaries.substr(0, splitPoint));
  unsigned int upperbound = stoi(boundaries.substr(splitPoint+1));

  unsigned int numberOfLetterOccurance = std::count(password.begin(), password.end(), letter.at(0));

  return lowerbound <= numberOfLetterOccurance && numberOfLetterOccurance <= upperbound;
}

bool validPassword2(std::string passwordline){
  int splitPoint = passwordline.find(" ");
  std::string boundaries = passwordline.substr(0,splitPoint);
  std::string letter =  passwordline.substr(splitPoint+1, 1);
  std::string password =  passwordline.substr(splitPoint+4);

  splitPoint = boundaries.find("-");
  unsigned int lowerIndex = stoi(boundaries.substr(0, splitPoint));
  unsigned int upperIndex = stoi(boundaries.substr(splitPoint+1));

  bool firstLocation = password.at(lowerIndex-1) ==  letter.at(0);
  bool secondLocation = password.at(upperIndex-1) ==  letter.at(0);

  return (firstLocation && !secondLocation) || (!firstLocation && secondLocation);
}