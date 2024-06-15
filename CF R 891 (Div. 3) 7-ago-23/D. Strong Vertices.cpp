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

bool sort_func(pii a, pii b) {
  if (a.first < b.first) {
    return true;
  } else {
    return false;
  }
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

void Imprime(vi vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i] << " ";
  }
  cout << endl;
}

void Imprime_set(set<int> s) {
  copy(s.begin(), s.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
}

vector<pii> lee(int n) {
  pii el;
  vector<pii> vect;
  for (int i = 0; i < n; i++) {
    cin >> el.first;
    el.second = i;
    vect.PB(el);
  }
  return (vect);
}

int solve() {
  // Code aquí
  int n;
  cin >> n;
  vector<pii> a;
  a = lee(n);
  int el;
  for (int i = 0; i < n; i++) {
    cin >> el;
    a[i].first = a[i].first - el;
  }
  ord(a);
  int ant = a[n - 1].first;
  vi b;
  for (int i = n - 1; ant == a[i].first; i--) {
    b.PB(a[i].second + 1);
    ant = a[i].first;
  }
  cout << b.size() << endl;
  sort(b.begin(), b.end());
  Imprime(b);

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