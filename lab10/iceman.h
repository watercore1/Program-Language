#ifndef ICEMAN_H_
#define ICEMAN_H_

#include "warrior.h"

class Iceman : public Warrior {
 public:
  Iceman() = default;
  Iceman(Faction faction, int id);
  ~Iceman();

  static void SetInitialElements(int);
  static void SetInitialForce(int);
  static int GetInitialElements();
  static int GetInitialForce();

  virtual string NameToString();

  /**
   * @brief  : iceman delete health and add force for every three cities he marches
   */
  virtual void March();

 private:
  static int initial_elements_;
  static int initial_force_;
  // number of marches;
  int step_;
};

#endif