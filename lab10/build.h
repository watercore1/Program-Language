#ifndef BUILD_H_
#define BUILD_H_

#include "warrior.h"

/**
 * @brief  : abstract class of city and headquarter
 */
class Build {
 public:
  Build(int initial_elements = 0);
  virtual ~Build();

  static void InitialCityNum(int city_num);

  // march functions

  /**
   * @brief  : Is there red warrior to march right in build
   * @return : bool:
   */
  virtual bool HasRedWarriorToMarch() = 0;

  /**
   * @brief  : Is there blue warrior to march left in build
   * @return : bool:
   */
  virtual bool HasBlueWarriorToMarch() = 0;

  /**
   * @brief  : After red warrior leave build, set red warrior pointer = nullptr
   * @return : Warrior*: the red warrior who leave
   */
  virtual Warrior* RedWarriorLeave() = 0;

  /**
   * @brief  : After blue warrior leave build, set blue warrior pointer =
   * nullptr
   * @return : Warrior*: the blue warrior who leave
   */
  virtual Warrior* BlueWarriorLeave() = 0;

  /**
   * @brief  : After red warrior arrived, set red warrior pointer
   * @param  : red_warrior: red warrior arrive build
   */
  virtual void ReachedByRedWarrior(Warrior* red_warrior) = 0;

  /**
   * @brief  : After blue warrior arrived, set blue warrior pointer
   * @param  : blue_Warrior: blue warrior arrive build
   */
  virtual void ReachedByBlueWarrior(Warrior* blue_Warrior) = 0;

  /**
   * @brief  : get current elements in build
   * @return : int: 
   */
  int GetElements();

 protected:
  // current elements
  int elements_;
  // used to determine if city is adjacent to headquarter, it's important for warriors march
  static int city_num_;
};

#endif