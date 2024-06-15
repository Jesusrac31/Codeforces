#include <iostream>
#include <vector>
using namespace std;

int main() {
  int T, n, q, IQ, el;
  vector<int> level;
  string sol;
  cin >> T;
  while (T--) {
    sol = "";
    level={};
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
      cin >> el;
      level.push_back(el);
      sol+='0';
    }
    IQ = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (IQ >= level[i]) {
        sol[i] = '1';
      } else if (IQ < q) {
        sol[i] = '1';
        IQ++;
      }
    }
    cout << sol << "\n";
  }
  return 0;
}