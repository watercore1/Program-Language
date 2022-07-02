#include "dragon.h"

int Dragon::initial_elements_ = 0;
int Dragon::initial_force_ = 0;

Dragon::Dragon(Faction faction, int id) : Warrior(faction, id) {
  type_ = DRAGON;
  elements_ = initial_elements_;
  force_ = initial_force_;
}

Dragon::~Dragon() {}

void Dragon::SetInitialElements(int elements) { initial_elements_ = elements; }

void Dragon::SetInitialForce(int force) { initial_force_ = force; }

int Dragon::GetInitialElements() { return initial_elements_; }

int Dragon::GetInitialForce() { return initial_force_; }

string Dragon::NameToString() {
  string faction = faction_ == Faction::RED ? "red" : "blue";
  return faction + " dragon " + to_string(id_);
}

Warrior* Dragon::InitiateWarTo(Warrior* enemy, int city_id)
{
  Warrior* died_warrior = Warrior::InitiateWarTo(enemy,city_id);
  if(died_warrior!=this)
    PrintYellEventInCity(city_id);
  return died_warrior;
}

void Dragon::PrintYellEventInCity(int city_id)
{
  Util::ofs_ << Util::TimeToString() << " " << this->NameToString()
             << " yelled in city " << to_string(city_id) << endl;
}