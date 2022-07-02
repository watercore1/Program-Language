#include "headquarter.h"

Headquarter::Headquarter(Faction faction, int initial_element)
    : Build(initial_element),
      faction_(faction),
      current_created_warrior_(nullptr),
      first_enemy_warrior_(nullptr),
      second_enemy_warrior_(nullptr) {
  if (faction_ == Faction::RED)
    create_warrior_order_ = {ICEMAN, LION, WOLF, NINJA, DRAGON};
  else
    create_warrior_order_ = {LION, DRAGON, NINJA, ICEMAN, WOLF};
}

Headquarter::~Headquarter() {
  // clear the heap memory
  for (auto warrior : all_created_warriors_) {
    delete warrior;
  }
}

void Headquarter::PrintCreatedWarrior() {
  Util::ofs_ << Util::TimeToString() << " "
             << current_created_warrior_->NameToString() << " born" << endl;
  ;
}

void Headquarter::CreateWarrior() {
  if (create_warrior_order_.size() == 0) throw RunningError::NOT_INITIAL_ORDER;

  int create_warrior_index = all_created_warriors_.size() % 5;

  switch (create_warrior_order_[create_warrior_index]) {
    case DRAGON: {
      TryToCreateWarrior<Dragon>();
      break;
    }
    case NINJA: {
      TryToCreateWarrior<Ninja>();
      break;
    }
    case ICEMAN: {
      TryToCreateWarrior<Iceman>();
      break;
    }
    case LION: {
      TryToCreateWarrior<Lion>();
      break;
    }
    case WOLF: {
      TryToCreateWarrior<Wolf>();
      break;
    }
    default:
      throw RunningError::UNKNOWN_WARRIOR_TYPE;
  }
}

bool Headquarter::HasRedWarriorToMarch() {
  return faction_ == Faction::RED && current_created_warrior_ != nullptr;
}

bool Headquarter::HasBlueWarriorToMarch() {
  return faction_ == Faction::BLUE && current_created_warrior_ != nullptr;
}

Warrior* Headquarter::RedWarriorLeave() {
  if (faction_ == Faction::BLUE) throw RunningError::ERROR_FACTION_WARRIOR;
  Warrior* temp = current_created_warrior_;
  current_created_warrior_ = nullptr;
  return temp;
}

Warrior* Headquarter::BlueWarriorLeave() {
  if (faction_ == Faction::RED) throw RunningError::ERROR_FACTION_WARRIOR;
  Warrior* temp = current_created_warrior_;
  current_created_warrior_ = nullptr;
  return temp;
}

void Headquarter::ReachedByRedWarrior(Warrior* red_warrior) {
  // red warrior can't reach red headquarter
  if (faction_ == Faction::RED) throw RunningError::ERROR_FACTION_WARRIOR;

  red_warrior->March();

  // print reached event
  Util::ofs_ << Util::TimeToString() << " " << red_warrior->NameToString()
             << " reached blue headquarter with "
             << red_warrior->AttributeToString() << endl;

  // update data
  if (first_enemy_warrior_ == nullptr)
    first_enemy_warrior_ = red_warrior;
  else if (second_enemy_warrior_ == nullptr) {
    second_enemy_warrior_ = red_warrior;
    Util::ofs_ << Util::TimeToString() << " blue headquarter was taken" << endl;
  } else
    throw TOO_MANY_WARRIORS;
}

void Headquarter::ReachedByBlueWarrior(Warrior* blue_warrior) {
  // blue warrior can't reach blue headquarter
  if (faction_ == Faction::BLUE) throw RunningError::ERROR_FACTION_WARRIOR;

  // determine if warrior is iceman
  blue_warrior->March();

  // print reached event
  Util::ofs_ << Util::TimeToString() << " " << blue_warrior->NameToString()
             << " reached red headquarter with "
             << blue_warrior->AttributeToString() << endl;

  // update data
  if (first_enemy_warrior_ == nullptr)
    first_enemy_warrior_ = blue_warrior;
  else if (second_enemy_warrior_ == nullptr) {
    second_enemy_warrior_ = blue_warrior;
    Util::ofs_ << Util::TimeToString() << " red headquarter was taken" << endl;
  } else
    throw TOO_MANY_WARRIORS;
}

bool Headquarter::IsOccupied() { return second_enemy_warrior_ != nullptr; }

void Headquarter::AddElements(int city_elements) { elements_ += city_elements; }

bool Headquarter::TryToRewardWarrior(Warrior* warrior) {
  if (elements_ < 8) return false;
  elements_ -= 8;
  warrior->AddElements(8);
  return true;
}
