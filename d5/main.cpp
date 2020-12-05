#include <iostream>
#include <algorithm>
#include <map>
#include <functional>
#include "support/support.h"

int getSeatID(std::string seatKey);

int main(int argc, char *argv[])
{
  std::string fileName = findFileLocation(argc, argv, "input.txt");
  std::vector<std::string> data = readFileStrings(fileName);

  std::vector<int> vectorOfSeatId;

  int highestID = 0;
  for (std::string seatKey : data)
  {
    int seatID = getSeatID(seatKey);
    vectorOfSeatId.emplace_back(seatID);
    if(seatID > highestID){
      highestID = seatID;
    }
    std::cout << seatKey << " - sead ID: " << seatID << std::endl;
  }

  std::cout << "Highest seat ID: " << highestID << std::endl;

  //Part 2
  for(int i=highestID; i>0; i--){
    if(std::find(vectorOfSeatId.begin(), vectorOfSeatId.end(), i) == vectorOfSeatId.end()){ //Value not in vector
      std::cout << "Empty seatID: " << i << std::endl;
      break;
    }
  }

  return 0;
}

int getSeatID(std::string seatKey){
  int seatID = 0;
  for(int i=0; i<seatKey.length(); i++){
    seatID *= 2;
    if(seatKey.substr(i,1) == "B" || seatKey.substr(i,1) == "R"){
      seatID += 1;
    }
  }
  return seatID;
}
