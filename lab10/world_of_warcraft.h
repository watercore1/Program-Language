#ifndef WORLD_OF_WARCRAFT_H_
#define WORLD_OF_WARCRAFT_H_

#include "city.h"
#include "headquarter.h"
#include "warrior.h"

class WorldOfWarcraft {
 public:
  WorldOfWarcraft(ifstream& ifs);
  ~WorldOfWarcraft();

  /**
   * @brief  : game begins, and print event in file
   * @param  : ofs: output file stream
   */
  void Run();

 private:
  vector<Build*> builds_;

  /**
   * @brief  : At 0 Minute, two headquarter create warrior
   */
  void CreateWarrior();

  /**
   * @brief  : At 10 Minute, all warriors march forward one city
   * @return : bool: determine if a headquarter is occupied
   */
  bool WarriorsMarch();

  /**
   * @brief  : At 20 Minute, all cities produce 10 elements
   */
  void CitiesProduceElements();

  /**
   * @brief  : At 30 Minute, in cities with one warrior, the warrior earn all
   * elements in the city, and transfer elements into  headquarter
   */
  void WarriorsEarnElements();

  /**
   * @brief  : At 40 Minute, in cites with two warriors, there will be wars;
   */
  void WarriorsFight();

  /**
   * @brief  : At 50 Minute, two headquarters report elements they have;
   */
  void HeadquarterReportElements();

  /**
   * @brief  : determine whether there is headquarter is reached by two enemy
   * warriors
   */
  bool IsHeadquarterOccupied();
};

#endif