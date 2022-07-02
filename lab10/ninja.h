#ifndef NINJA_H_
#define NINJA_H_

#include "warrior.h"

class Ninja : public Warrior {
 public:
  Ninja() = default;
  Ninja(Faction faction, int id);
  ~Ninja();
  static void SetInitialElements(int);
  static void SetInitialForce(int);
  static int GetInitialElements();
  static int GetInitialForce();

  virtual string NameToString();

 private:
  static int initial_elements_;
  static int initial_force_;
};

#endif