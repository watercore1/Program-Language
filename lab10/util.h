#ifndef UTIL_H_
#define UTIL_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum WarriorType { ICEMAN, LION, WOLF, NINJA, DRAGON };

enum Faction { RED, BLUE };

enum CityFlag { NO_FLAG, RED_FLAG, BLUE_FLAG };

enum FightResult {
  NO_WAR,
  BOTH_ALIVE,
  RED_WIN,
  BLUE_WIN,
};

enum RunningError {
  NOT_INITIAL_ORDER,
  UNKNOWN_WARRIOR_TYPE,
  TOO_MANY_WARRIORS,
  ERROR_FACTION_WARRIOR,
};

class Util {
 public:
  Util();
  ~Util();

  // (1) Output file stream
  static ofstream ofs_;

  // (2) current game time
  /**
   * @brief  : initial current time as 0
   */
  static void InitialCurrentTime();
  /**
   * @brief  : initial end time
   * @param  : end_time:
   */
  static void SetEndTime(int end_time);
  /**
   * @brief  : the remainder of dividing the current time by 60.
   * @return : int: the minutes of current time,
   */
  static int Minutes();
  /**
   * @brief  : determine if time is over
   * @return : bool:
   */
  static bool IsTimeOver();
  /**
   * @brief  : add 5 minutes to current time
   */
  static void Past10Minutes();
  /**
   * @brief  : convert current time to string
   * @return : string: format "000:00"
   */
  static string TimeToString();

 private:
  static int current_time_;
  static int end_time_;
};

#endif
