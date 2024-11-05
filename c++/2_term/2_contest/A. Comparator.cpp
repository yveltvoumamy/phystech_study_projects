#include <iostream>
#include <algorithm>
#include <vector>

struct TeamRec {
  int correct;
  int penalty;
  int num;
  TeamRec() = default;
};

bool Comp(const TeamRec& one, const TeamRec& two);

int main() {
  int n, s, t, i;
  std::cin >> n;
  std::vector<TeamRec> teams(n);
  i = 0;
  while (i < n) {
    std::cin >> s >> t;
    teams[i].penalty = t;
    teams[i].correct = s;
    teams[i].num = 1 + i;
    ++i;
  }
  std::sort(teams.begin(), teams.end(), Comp);
  i = 0;
  while (i < n) {
    std::cout << teams[i].num << std::endl;
    i++;
  }
}

bool Comp(const TeamRec& one, const TeamRec& two) {
  if (one.correct != two.correct) {
    return two.correct < one.correct;
  }
  if (one.penalty != two.penalty) {
    return two.penalty > one.penalty;
  }
  return one.num < two.num;
}
