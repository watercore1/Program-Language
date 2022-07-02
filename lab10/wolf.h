#ifndef WOLF_H_
#define WOLF_H_

#include "warrior.h"

class Wolf : public Warrior {
 public:
  Wolf() = default;
  Wolf(Faction faction, int id);
  ~Wolf();
  static void SetInitialElements(int);
  static void SetInitialForce(int);
  static int GetInitialElements();
  static int GetInitialForce();

  virtual string NameToString();

  virtual void Attack(Warrior* enemy);

 private:
  static int initial_elements_;
  static int initial_force_;
  // number of warriors killed by wolf
  int kill_num_;
};

#endif