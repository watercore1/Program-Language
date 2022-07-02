#include "iceman.h"

int Iceman::initial_elements_ = 0;
int Iceman::initial_force_ = 0;

Iceman::Iceman(Faction faction, int id) : Warrior(faction, id), step_(0) {
  type_ = ICEMAN;
  elements_ = initial_elements_;
  force_ = initial_force_;
}

Iceman::~Iceman() {}

void Iceman::SetInitialElements(int elements) { initial_elements_ = elements; }

void Iceman::SetInitialForce(int force) { initial_force_ = force; }

int Iceman::GetInitialElements() { return initial_elements_; }

int Iceman::GetInitialForce() { return initial_force_; }

string Iceman::NameToString() {
  string faction = faction_ == Faction::RED ? "red" : "blue";
  return faction + " iceman " + to_string(id_);
}

void Iceman::March() {
  step_++;
  if (step_ % 3 != 0) return;

  if (elements_ > 9)
    elements_ -= 9;
  else
    elements_ = 1;

  force_ += 20;
}