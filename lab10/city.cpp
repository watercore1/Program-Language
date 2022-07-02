#include "city.h"

City::City(int id)
    : id_(id),
      red_warrior_(nullptr),
      backup_red_warrior_(nullptr),
      blue_warrior_(nullptr),
      flag_(CityFlag::NO_FLAG),
      last_war_result_(NO_WAR) {}

City::~City() {}

void City::UpdateBackupRedWarrior() {
  backup_red_warrior_ = red_warrior_;
  red_warrior_ = nullptr;
}

bool City::HasRedWarriorToMarch() { return backup_red_warrior_ != nullptr; }

bool City::HasBlueWarriorToMarch() { return blue_warrior_ != nullptr; }

Warrior* City::RedWarriorLeave() {
  Warrior* temp = backup_red_warrior_;
  backup_red_warrior_ = nullptr;
  return temp;
}

Warrior* City::BlueWarriorLeave() {
  Warrior* temp = blue_warrior_;
  blue_warrior_ = nullptr;
  return temp;
}

void City::ReachedByRedWarrior(Warrior* red_warrior) {
  if (red_warrior_ != nullptr) throw RunningError::TOO_MANY_WARRIORS;
  red_warrior->March();
  red_warrior_ = red_warrior;
  PrintReachedWarrior(red_warrior);
}

void City::ReachedByBlueWarrior(Warrior* blue_warrior) {
  if (blue_warrior_ != nullptr) throw RunningError::TOO_MANY_WARRIORS;
  blue_warrior->March();
  blue_warrior_ = blue_warrior;
  PrintReachedWarrior(blue_warrior);
}

void City::ProduceElements() { elements_ += 10; }

bool City::IsOccupiedByRed() {
  return red_warrior_ != nullptr && blue_warrior_ == nullptr;
}

bool City::IsOccupiedByBlue() {
  return red_warrior_ == nullptr && blue_warrior_ != nullptr;
}

int City::TokenElements() {
  // (1) print event

  // the only warrior left
  Warrior* warrior = IsOccupiedByRed() ? red_warrior_ : blue_warrior_;

  Util::ofs_ << Util::TimeToString() << " " << warrior->NameToString()
             << " earned " << to_string(elements_)
             << " elements for his headquarter" << endl;

  // (2) update data
  int temp = elements_;
  elements_ = 0;
  return temp;
}

void City::PrintReachedWarrior(Warrior* warrior) {
  Util::ofs_ << Util::TimeToString() << " " << warrior->NameToString()
             << " marched to city " << to_string(id_) << " with "
             << warrior->AttributeToString() << endl;
}



FightResult City::WarriorsFight() {

  // (1) if there is a war
  if (red_warrior_ == nullptr || blue_warrior_ == nullptr) return NO_WAR;

  // (2) Get the war result
  FightResult result;
  Warrior* died_warrior;

  if (flag_ == RED_FLAG || (flag_ == NO_FLAG && id_ % 2 == 0)) {
    died_warrior = red_warrior_->InitiateWarTo(blue_warrior_,id_);
  }
  else {
    died_warrior = blue_warrior_->InitiateWarTo(red_warrior_,id_);
  }

  if(died_warrior == nullptr)
    result = BOTH_ALIVE;
  else if(died_warrior->GetFaction()==Faction::RED){
    red_warrior_ = nullptr;
    result = BLUE_WIN;
  }
  else{
    blue_warrior_ = nullptr;
    result = RED_WIN;
  }

  // (3) update flag
  if (last_war_result_ == RED_WIN && result == RED_WIN) flag_ = RED_FLAG;
  if (last_war_result_ == BLUE_WIN && result == BLUE_WIN) flag_ = BLUE_FLAG;
  last_war_result_ = result;

  return result;
}