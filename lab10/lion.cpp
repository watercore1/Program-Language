#include "lion.h"

int Lion::initial_elements_ = 0;
int Lion::initial_force_ = 0;

Lion::Lion(Faction faction, int id) : Warrior(faction, id) {
  type_ = LION;
  elements_ = initial_elements_;
  force_ = initial_force_;
}

Lion::~Lion() {}

void Lion::SetInitialElements(int elements) { initial_elements_ = elements; }

void Lion::SetInitialForce(int force) { initial_force_ = force; }

int Lion::GetInitialElements() { return initial_elements_; }

int Lion::GetInitialForce() { return initial_force_; }

string Lion::NameToString() {
  string faction = faction_ == Faction::RED ? "red" : "blue";
  return faction + " lion " + to_string(id_);
}