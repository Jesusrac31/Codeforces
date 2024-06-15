#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

typedef map<int, int> mi;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, el, sol;
    cin >> n;
    mi a;
    for (int i = 0; i < n; i++) {
      cin >> el;
      a[el]++;
    }
    while (a.size() != 1) {
      sol = -1;
      for (auto i : a) {
        if (sol != -1) {
          a[i.first - sol]++;
          a[i.first]--;
          a[sol]--;
          cin >> el;
          if (i.second == 0){
            a.erase(a.find(i.first));
          }
          if (a[sol] == 0){
            a.erase(a.find(sol));
          }
        }
        sol = i.first;
      }
    }
    cout << sol << endl;
  }
  return 0;
}