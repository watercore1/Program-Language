#include "world_of_warcraft.h"

WorldOfWarcraft::WorldOfWarcraft(ifstream& ifs) {
  // (1) read data from file

  int headquarter_initial_elements, city_num, end_clock_in_minute;
  int dragon_elements, ninja_elements, iceman_elements, lion_elements,
      wolf_elements;
  int dragon_force, ninja_force, iceman_force, lion_force, wolf_force;

  ifs >> headquarter_initial_elements >> city_num >> end_clock_in_minute >>
      dragon_elements >> ninja_elements >> iceman_elements >> lion_elements >>
      wolf_elements >> dragon_force >> ninja_force >> iceman_force >>
      lion_force >> wolf_force;

  // (2) initial warrior static data and time

  Dragon::SetInitialElements(dragon_elements);
  Ninja::SetInitialElements(ninja_elements);
  Iceman::SetInitialElements(iceman_elements);
  Lion::SetInitialElements(lion_elements);
  Wolf::SetInitialElements(wolf_elements);
  Dragon::SetInitialForce(dragon_force);
  Ninja::SetInitialForce(ninja_force);
  Iceman::SetInitialForce(iceman_force);
  Lion::SetInitialForce(lion_force);
  Wolf::SetInitialForce(wolf_force);

  Util::InitialCurrentTime();
  Util::SetEndTime(end_clock_in_minute);

  Build::InitialCityNum(city_num);

  // (3) initial member data

  builds_.push_back(
      new Headquarter(Faction::RED, headquarter_initial_elements));
  for (int i = 1; i <= city_num; i++) {
    builds_.push_back(new City(i));
  }
  builds_.push_back(
      new Headquarter(Faction::BLUE, headquarter_initial_elements));
}

WorldOfWarcraft::~WorldOfWarcraft() {
  for (auto build : builds_) delete build;
}

void WorldOfWarcraft::Run() {
  bool is_headquarter_occupied = false;
  while (!Util::IsTimeOver()) {
    switch (Util::Minutes()) {
      case 0:
        CreateWarrior();
        break;
      case 10: {
        is_headquarter_occupied = WarriorsMarch();
        break;
      }
      case 20:
        CitiesProduceElements();
        break;
      case 30:
        WarriorsEarnElements();
        break;
      case 40:
        WarriorsFight();
        break;
      case 50:
        HeadquarterReportElements();
        break;
    }

    if (is_headquarter_occupied) break;

    Util::Past10Minutes();
  }
}

void WorldOfWarcraft::CreateWarrior() {
  // use build pointer type to call headquarter class method
  dynamic_cast<Headquarter*>(builds_.front())->CreateWarrior();
  dynamic_cast<Headquarter*>(builds_.back())->CreateWarrior();
}

bool WorldOfWarcraft::WarriorsMarch() {
  // (1) update city backup red warrior
  for (size_t i = 1; i < builds_.size() - 1; i++) {
    dynamic_cast<City*>(builds_[i])->UpdateBackupRedWarrior();
  }

  // (2) warriors march and print event

  size_t i = 0;
  // red headquarter reached by blue warrior
  if (builds_[i + 1]->HasBlueWarriorToMarch())
    builds_[i]->ReachedByBlueWarrior(builds_[i + 1]->BlueWarriorLeave());

  // cities reached by warriors, first print red warriors
  for (i++; i < builds_.size() - 1; i++) {
    if (builds_[i - 1]->HasRedWarriorToMarch()) {
      // build[i-1] leave red warrior
      // build[i] reached by red warrior
      builds_[i]->ReachedByRedWarrior(builds_[i - 1]->RedWarriorLeave());
    }
    if (builds_[i + 1]->HasBlueWarriorToMarch()) {
      // build[i+1] leave blue warrior
      // build[i] reached by blue warrior
      builds_[i]->ReachedByBlueWarrior(builds_[i + 1]->BlueWarriorLeave());
    }
  }

  // blue headquarter reached by red warrior
  if (builds_[i - 1]->HasRedWarriorToMarch())
    builds_[i]->ReachedByRedWarrior(builds_[i - 1]->RedWarriorLeave());

  // determine if a headquarter is occupied;
  return IsHeadquarterOccupied();
}

void WorldOfWarcraft::CitiesProduceElements() {
  for (size_t i = 1; i < builds_.size() - 1; i++) {
    dynamic_cast<City*>(builds_[i])->ProduceElements();
  }
}

void WorldOfWarcraft::WarriorsEarnElements() {
  for (size_t i = 1; i < builds_.size() - 1; i++) {
    City* city = dynamic_cast<City*>(builds_[i]);
    if (city->IsOccupiedByRed())
      dynamic_cast<Headquarter*>(builds_.front())
          ->AddElements(city->TokenElements());
    else if (city->IsOccupiedByBlue())
      dynamic_cast<Headquarter*>(builds_.back())
          ->AddElements(city->TokenElements());
    else
      continue;
  }
}

void WorldOfWarcraft::WarriorsFight() {
  // (1) record cities where red warrior wins or blur warrior wins;
  vector<int> red_win_city;
  int red_reward = 0;
  vector<int> blue_win_city;
  int blue_Reward = 0;

  for (size_t i = 1; i < builds_.size() - 1; i++) {
    City* city = dynamic_cast<City*>(builds_[i]);
    switch (city->WarriorsFight()) {
      case RED_WIN:
        red_win_city.insert(red_win_city.begin(), i);
        red_reward += city->TokenElements();
        break;
      case BLUE_WIN:
        blue_win_city.push_back(i);
        blue_Reward += city->TokenElements();
        break;
      default:
        break;
    }
  }

  // (2) red headquarter reward winner warriors and earn elements
  Headquarter* red_headquarter = dynamic_cast<Headquarter*>(builds_.front());
  for (auto index : red_win_city) {
    if (!red_headquarter->TryToRewardWarrior(
            dynamic_cast<City*>(builds_[index])->GetRedWarrior()))
      break;
  }

  red_headquarter->AddElements(red_reward);

  // (3) blue headquarter reward winner warriors and earn elements

  Headquarter* blue_headquarter = dynamic_cast<Headquarter*>(builds_.back());
  for (auto index : blue_win_city) {
    if (!blue_headquarter->TryToRewardWarrior(
            dynamic_cast<City*>(builds_[index])->GetBlueWarrior()))
      break;
  }

  blue_headquarter->AddElements(blue_Reward);
}

void WorldOfWarcraft::HeadquarterReportElements() {
  Util::ofs_ << Util::TimeToString() << " " << builds_.front()->GetElements()
             << " elements in red headquarter" << endl;
  Util::ofs_ << Util::TimeToString() << " " << builds_.back()->GetElements()
             << " elements in blue headquarter" << endl;
}

bool WorldOfWarcraft::IsHeadquarterOccupied() {
  return dynamic_cast<Headquarter*>(builds_.front())->IsOccupied() ||
         dynamic_cast<Headquarter*>(builds_.back())->IsOccupied();
}