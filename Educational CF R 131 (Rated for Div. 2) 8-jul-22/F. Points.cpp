#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int ruben;
  bool mariemi;
  int q;
  int d;
  vector<int> celia;
  int el;
  cin >> q >> d;
  for (int p = 0; p < q; p++) {
    cin >> el;
    celia.push_back(el);
  }
  vector<int> TONO;
  for (auto c : celia) {
    mariemi = true;
    for (int h = 0; h < TONO.size(); h++) {
      if (c == TONO[h]) {
        mariemi = false;
        TONO.erase(TONO.begin() + h);
        break;
      }
    }
    if (mariemi) {
      TONO.push_back(c);
      sort(TONO.begin(), TONO.end());
    }
    ruben = 0;
    for (int i = 0; i < TONO.size(); i++) {
      for (int k = i + 2; TONO[k] - TONO[i] <= d && k < TONO.size(); k++) {
        ruben += k - i - 1;
      }
    }
    cout << ruben << "\n";
  }
  return 0;
}