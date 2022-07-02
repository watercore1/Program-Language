#include "world_of_warcraft.h"

void Start();

int main(int argc, char* argv[]) {
  Start();
  return 0;
}

void Start() {
  ifstream ifs("input.txt");
  Util::ofs_.open("output.txt");
  int round = 0;
  ifs >> round;
  for (int i = 1; i <= round; i++) {
    try {
      Util::ofs_ << "Case:" << to_string(i) << endl;
      WorldOfWarcraft wow(ifs);
      wow.Run();
    } catch (RunningError error) {
      switch (error) {
        case NOT_INITIAL_ORDER:
          cout << "Not initial warrior creation order";
          break;
        default:
          break;
      }
    }
  }

  ifs.close();
  Util::ofs_.close();
}
