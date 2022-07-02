#ifndef LION_H_
#define LION_H_

#include "warrior.h"

class Lion : public Warrior {
 public:
  Lion() = default;
  Lion(Faction faction, int id);
  ~Lion();
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