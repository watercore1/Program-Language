#include "util.h"

ofstream Util::ofs_;
int Util::current_time_ = 0;
int Util::end_time_ = 0;

Util::Util() {}

Util::~Util() {}

void Util::InitialCurrentTime() { current_time_ = 0; }

void Util::SetEndTime(int end_time) { end_time_ = end_time; }

int Util::Minutes() { return current_time_ % 60; }

bool Util::IsTimeOver() { return current_time_ > end_time_; }

void Util::Past10Minutes() { current_time_ += 10; }

string Util::TimeToString() {
  int hours = current_time_ / 60;
  int minutes = current_time_ % 60;
  char time[6];
  sprintf(time, "%03d:%02d", hours, minutes);
  return string(time);
}
