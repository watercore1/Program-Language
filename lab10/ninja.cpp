#include "ninja.h"

int Ninja::initial_elements_ = 0;
int Ninja::initial_force_ = 0;

Ninja::Ninja(Faction faction, int id) : Warrior(faction, id) {
  type_ = NINJA;
  elements_ = initial_elements_;
  force_ = initial_force_;
}

Ninja::~Ninja() {}

void Ninja::SetInitialElements(int elements) { initial_elements_ = elements; }

void Ninja::SetInitialForce(int force) { initial_force_ = force; }

int Ninja::GetInitialElements() { return initial_elements_; }

int Ninja::GetInitialForce() { return initial_force_; }

string Ninja::NameToString() {
  string faction = faction_ == Faction::RED ? "red" : "blue";
  return faction + " ninja " + to_string(id_);
}