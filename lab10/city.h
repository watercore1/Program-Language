#ifndef CITY_H_
#define CITY_H_

#include "build.h"
#include "warrior.h"

class City : public Build {
 public:
  City() = default;
  City(int id);
  ~City();

  // (1) virtual functions in Build class 

 
  virtual bool HasRedWarriorToMarch();
  virtual bool HasBlueWarriorToMarch();
  virtual Warrior* RedWarriorLeave();
  virtual Warrior* BlueWarriorLeave();
  virtual void ReachedByRedWarrior(Warrior* red_warrior);
  virtual void ReachedByBlueWarrior(Warrior* blue_warrior);

  /**
   * @brief  : used for red warrior march
   */
  void UpdateBackupRedWarrior();

  /**
   * @brief  : produce 10 elements
   */
  void ProduceElements();

  /**
   * @brief  : there is only red warrior
   * @return : bool: 
   */
  bool IsOccupiedByRed();

  /**
   * @brief  : there is only blue warrior
   * @return : bool: 
   */
  bool IsOccupiedByBlue();

  /**
   * @brief  : the only warrior take elements in city, and print event to file
   * @return : int: the token elements
   */
  int TokenElements();

  /**
   * @brief  : fight in city
   * @return : FightResult: 
   */
  FightResult WarriorsFight();

  /**
   * @brief  : return the red warrior
   * @return : Warrior*: 
   */
  Warrior* GetRedWarrior() { return red_warrior_; }

  /**
   * @brief  : return the blue warrior
   * @return : Warrior*: 
   */
  Warrior* GetBlueWarrior() { return blue_warrior_; }

 private:
  // id, start from 1 to city_num_
  int id_;
  // current red warrior in city
  Warrior* red_warrior_;
  // used to red warrior march
  Warrior* backup_red_warrior_;
  // current blue warrior in city
  Warrior* blue_warrior_;
  // city flag
  CityFlag flag_;
  // last war result, used to determine flag
  FightResult last_war_result_;

  /**
   * @brief  : print march event to file
   * @param  : warrior: warrior who arrive the city
   */
  void PrintReachedWarrior(Warrior* warrior);
};

#endif