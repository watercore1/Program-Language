#include "warrior.h"

Warrior::Warrior(Faction faction, int id) : faction_(faction), id_(id) {}

Warrior::~Warrior() {}

string Warrior::AttributeToString() {
  return to_string(elements_) + " elements and force " + to_string(force_);
}

bool Warrior::IsAlive() { return elements_ > 0; }

WarriorType Warrior::GetType() { return type_; }

void Warrior::AddElements(int elements) { elements_ += elements; }

Warrior* Warrior::InitiateWarTo(Warrior* enemy, int city_id) {
  PrintAttackEvent(enemy, city_id);
  this->Attack(enemy);
  if (enemy->IsAlive()) {
    if (enemy->GetType() == NINJA) return nullptr;
    enemy->PrintAttackBackEvent(this, city_id);
    enemy->AttackBack(this);
    if (this->IsAlive())
      return nullptr;
    else {
      this->PrintDieEventInCity(city_id);
      return this;
    }
  } else {
    enemy->PrintDieEventInCity(city_id);
    return enemy;
  }
}

void Warrior::Attack(Warrior* enemy) {
  int enemy_elements = enemy->GetCurrentElements();
  enemy->DelElements(this->force_);
  if (!enemy->IsAlive() && enemy->GetType() == LION) {
    elements_ += enemy_elements;
  }
}

void Warrior::AttackBack(Warrior* enemy) {
  int enemy_elements = enemy->GetCurrentElements();
  enemy->DelElements(this->force_ / 2);
  if (!enemy->IsAlive() && enemy->GetType() == LION)
    elements_ += enemy_elements;
}

void Warrior::DelElements(int elements) { elements_ -= elements; }

Faction Warrior::GetFaction() { return faction_; }

int Warrior::GetCurrentElements() { return elements_; }

void Warrior::PrintAttackEvent(Warrior* enemy, int city_id) {
  Util::ofs_ << Util::TimeToString() << " " << this->NameToString()
             << " attacked " << enemy->NameToString() << " in city "
             << to_string(city_id) << " with " << this->AttributeToString()
             << endl;
}

void Warrior::PrintAttackBackEvent(Warrior* enemy, int city_id) {
  Util::ofs_ << Util::TimeToString() << " " << this->NameToString()
             << " fought back against " << enemy->NameToString() << " in city "
             << to_string(city_id) << endl;
}

void Warrior::PrintDieEventInCity(int city_id) {
  Util::ofs_ << Util::TimeToString() << " " << this->NameToString()
             << " was killed in city " << to_string(city_id) << endl;
}
