#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
#define PB(a) push_back(a);
typedef vector<int> vi;

int main() {
  int T;
  cin >> T;

  while (T--) {
    int n, min = 0, max, el, dif;
    vi utiles;
    cin >> n;
    max = floor(n / 2)-1;
    if (max % 2 == 1) {
      max += 1;
    }

    while (utiles.size() != 1) {
      utiles = {};
      cout << "? " << min+1 << " " << max+1 << "\n";
      for (int i = 0; i <= max-min; i++) {
        cin >> el;
        if (el-1 >= min && el-1 <= max) {
          utiles.PB(el);
        }
      }
      dif = max-min;
      if (utiles.size() % 2 == 1){ 
        max = floor(dif/2+min);
        if (dif % 2 == 1) {
          max += 1;
        }
      }
      else{
        min = max+1;
        max = floor(dif/2+min);
      }
    }
    cout << "! " << utiles[0] << "\n";
  }

  return 0;
}