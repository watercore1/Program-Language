#ifndef DRAGON_H_
#define DRAGON_H_

#include "warrior.h"

class Dragon : public Warrior {
 public:
  Dragon() = default;
  Dragon(Faction faction, int id);
  ~Dragon();

  // (1) set and get initial static data

  static void SetInitialElements(int elements);
  static void SetInitialForce(int force);
  static int GetInitialElements();
  static int GetInitialForce();

  /**
   * @brief  : convert to string for output
   * @return : string: faction + type + id
   */
  virtual string NameToString();

  /**
   * @brief  : initiate a war to enemy, dragon will yell if not die
   * @param  : enemy: 
   * @param  : city_id: where the war happen
   * @return : Warrior*: the died warrior in the war
   */
  virtual Warrior* InitiateWarTo(Warrior* enemy, int city_id);

 private:
  static int initial_elements_;
  static int initial_force_;

  /**
   * @brief  : dragon yell
   * @param  : city_id: 
   */
  void PrintYellEventInCity(int city_id);
};

#endif