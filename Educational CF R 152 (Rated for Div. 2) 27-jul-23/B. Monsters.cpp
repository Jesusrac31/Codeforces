#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef pair<int, int> pii;
typedef map<string, int> msi;
typedef map<int, vector<int>> miv;

// Funciones vector
#define PB(a) push_back(a);

int k;

bool sort_func(pii a, pii b) {
  return (a.first > b.first || (a.first == b.first && a.second < b.second));
}
#define ord(vect) sort(vect.begin(), vect.end(), sort_func);

#define borra_el(vect, el) vect.erase(vect.find(el));
#define borra_range(vect, a, b) vect.erase(a, b);
#define borra(vect, n) vect.erase(vect.begin() + n);
#define B begin();
#define E end();
#define copia(v1, v2)                                                          \
  ;                                                                            \
  copy(v1.begin(), v1.end(), back_inserter(v2));

// Funciones map
#define F first;
#define S second;

// Logaritmo de 2
double log_2 = log(2);
double log2(int a) { return (log(a) / log_2); }

void Imprime(vector<vector<int>> vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i][1] << " ";
  }
  cout << endl;
}

vector<vector<int>> lee(int n) {
  int el;
  vi vect;
  vector<vector<int>> a;
  for (int i = 0; i < n; i++) {
    vect.clear();
    cin >> el;
    vect.PB((el - 1) % k);
    vect.PB(i + 1);
    a.PB(vect);
  }
  return (a);
}

int solve() {
  // Code aquí
  int n;

  cin >> n >> k;

  vector<pii> a(n);
  int el;
  vi vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    a[i].first = (el - 1) % k;
    a[i].second = i + 1;
  }
  ord(a);
  for (int i = 0; i < a.size(); i++) {
    cout << a[i].second << " ";
  }
  cout << endl;

  return 0;
}

int main() {
  int T;
  cin >> T; // Número de casos
  while (T--) {
    solve();
  }
  return 0;
}