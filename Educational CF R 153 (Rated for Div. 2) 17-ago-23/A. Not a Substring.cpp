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

bool sort_func(int a, int b) {
  if (a < b) {
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

vi lee(int n) {
  int el;
  vi vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

void Imprime_seq(int tipo, int n) {
  cout << "YES" << endl;
  if (tipo == 0) { // ()()()()
    for (int i = 0; i<n; i++){
      cout << "()";
    }
  } else { //(((((())))))
    for (int i = 0; i<n; i++){
      cout << "(";
    }
    for (int i = 0; i<n; i++){
      cout << ")";
    }
  }
  cout << endl;
}

int solve() {
  // Code aquí
  string s;
  cin >> s;
  if (s.size() == 2 && s == "()") {
    cout << "NO" << endl;
  } else if (s[0] == s[1]) {
    Imprime_seq(0, s.size());
  } else {
    if (s[0] == ')') {
      Imprime_seq(1, s.size());
    } else if (s[2] == s[1]) {
      Imprime_seq(0, s.size());
    } else {
      Imprime_seq(1, s.size());
    }
  }

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