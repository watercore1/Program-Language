#ifndef HEADQUARTER_H_
#define HEADQUARTER_H_

#include "build.h"
#include "dragon.h"
#include "iceman.h"
#include "lion.h"
#include "ninja.h"
#include "wolf.h"

class Headquarter : public Build {
 public:
  Headquarter(Faction faction, int initial_element);
  virtual ~Headquarter();

  // headquarter create warrior
  void CreateWarrior();

  // march functions
  virtual bool HasRedWarriorToMarch();
  virtual bool HasBlueWarriorToMarch();
  virtual Warrior* RedWarriorLeave();
  virtual Warrior* BlueWarriorLeave();
  virtual void ReachedByRedWarrior(Warrior* red_warrior);
  virtual void ReachedByBlueWarrior(Warrior* blue_Warrior);

  /**
   * @brief  : if there are two enemy warrior
   * @return : bool:
   */
  bool IsOccupied();

  /**
   * @brief  : Add city elements
   * @param  : city_elements:
   */
  void AddElements(int city_elements);

  /**
   * @brief  : try to reward warrior 8 elements
   * @param  : warrior: 
   * @return : bool: if reward successful, return true
   */
  bool TryToRewardWarrior(Warrior* warrior);

 private:
  Faction faction_;
  // current created warrior pointer, used to print event
  Warrior* current_created_warrior_;
  // the first reached enemy warrior, initial with nullptr
  Warrior* first_enemy_warrior_;
  // the second reached enemy warrior, initial with nullptr
  Warrior* second_enemy_warrior_;
  // red and blue headquarters have different warrior order to creative
  vector<WarriorType> create_warrior_order_;
  // store all created warriors, used to delete pointer.
  vector<Warrior*> all_created_warriors_;

  /**
   * @brief  : try to create warrior. if create successfully, print creation
   * event
   * @tparam T type of the the created warrior
   */
  template <typename T>
  void TryToCreateWarrior() {
    if (elements_ < T::GetInitialElements()) return;
    // initial with faction and id
    current_created_warrior_ =
        new T(faction_, all_created_warriors_.size() + 1);
    elements_ -= T::GetInitialElements();
    all_created_warriors_.push_back(current_created_warrior_);
    PrintCreatedWarrior();
  }

  // print creation event
  void PrintCreatedWarrior();
};

#endif