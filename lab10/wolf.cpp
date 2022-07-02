#include "wolf.h"

int Wolf::initial_elements_ = 0;
int Wolf::initial_force_ = 0;

Wolf::Wolf(Faction faction, int id) : Warrior(faction, id), kill_num_(0) {
  type_ = WOLF;
  elements_ = initial_elements_;
  force_ = initial_force_;
}

Wolf::~Wolf() {}

void Wolf::SetInitialElements(int elements) { initial_elements_ = elements; }

void Wolf::SetInitialForce(int force) { initial_force_ = force; }

int Wolf::GetInitialElements() { return initial_elements_; }

int Wolf::GetInitialForce() { return initial_force_; }

string Wolf::NameToString() {
  string faction = faction_ == Faction::RED ? "red" : "blue";
  return faction + " wolf " + to_string(id_);
}

void Wolf::Attack(Warrior* enemy) {
  int enemy_elements = enemy->GetCurrentElements();
  enemy->DelElements(force_);

  if (!enemy->IsAlive()) {
    kill_num_++;
    if (kill_num_ % 2 == 0) {
      elements_ *= 2;
      force_ *= 2;
    }
    if (enemy->GetType() == LION) elements_ += enemy_elements;
  }
}