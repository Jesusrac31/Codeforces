#include <bits/stdc++.h>
#include <iostream>
using namespace std;

using vi = vector<int>;
using lli = long long int;

int solve() {
  int n, k;
  cin >> n >> k;
  vi lista;
  for (int i = 0; i < k; i++) {
    lista.push_back(0);
  }
  int el;
  for (int i = 0; i < n; i++) {
    cin >> el;
    if (lista[i % k] < el) {
      lista[i % k] = el;
    }
  }
  lli sum = 0;
  for (auto c : lista) {
    sum += c;
  }
  cout << sum << endl;
  return 0;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return (0);
}