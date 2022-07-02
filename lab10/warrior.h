#ifndef WARRIOR_H
#define WARRIOR_H

#include "util.h"

class Warrior {
 public:
  Warrior() = default;
  Warrior(Faction faction, int id);
  virtual ~Warrior();

  /**
   * @brief  : for different type warrior, the name is different
   * @return : string:
   */
  virtual string NameToString() = 0;

  /**
   * @brief  : for different type warrior, the attribute is same
   * @return : string:
   */
  string AttributeToString();

  /**
   * @brief  : if elements>0
   * @return : bool:
   */
  bool IsAlive();

  virtual void March() {}

  /**
   * @brief  : initiate a war to enemy
   * @param  : enemy: 
   * @param  : city_id: the war position
   * @return : Warrior*: the died warrior
   */
  virtual Warrior* InitiateWarTo(Warrior* enemy, int city_id);
  /**
   * @brief  : attack enemy, if enemy is Lion and died, add elements
   * @param  : enemy: 
   */
  virtual void Attack(Warrior* enemy);

  /**
   * @brief  : attack back to enemy, if enemy is Lion and died, add elements
   * @param  : enemy: 
   */
  void AttackBack(Warrior* enemy);


  int GetCurrentElements();
  void AddElements(int elements);
  void DelElements(int elements);
  WarriorType GetType();
  Faction GetFaction();

 protected:
  WarriorType type_;
  Faction faction_;
  int id_;
  int elements_;
  int force_;

  void PrintAttackEvent(Warrior* enemy, int city_id);
  void PrintAttackBackEvent(Warrior* enemy, int city_id);
  void PrintDieEventInCity(int city_id);
};

#endif  // WARRIOR_H
