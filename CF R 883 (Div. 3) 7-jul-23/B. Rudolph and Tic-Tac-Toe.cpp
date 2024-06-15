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

void Imprime(vector<string> vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i] << " ";
  }
  cout << endl;
}

vector<string> lee(int n) {
  string el;
  vector<string> vect(n);
  for (int i = 0; i < n / 3; i++) {
    cin >> el;
    for (int j = 0; j < el.size(); j++) {
      vect[i * 3 + j] += el[j];
    }
  }
  return (vect);
}

int solve() {
  // Code aquí
  vector<string> tablero;
  tablero = lee(9);
  if (tablero[0] == tablero[1] && tablero[0] == tablero[2] &&
      tablero[0] != ".") {
    cout << tablero[0] << endl;
    return 0;
  }
  if (tablero[3] == tablero[4] && tablero[3] == tablero[5] &&
      tablero[3] != ".") {
    cout << tablero[3] << endl;
    return 0;
  }
  if (tablero[6] == tablero[7] && tablero[6] == tablero[8] &&
      tablero[6] != ".") {
    cout << tablero[6] << endl;
    return 0;
  }

  if (tablero[0] == tablero[3] && tablero[0] == tablero[6] &&
      tablero[0] != ".") {
    cout << tablero[0] << endl;
    return 0;
  }
  if (tablero[1] == tablero[4] && tablero[1] == tablero[7] &&
      tablero[1] != ".") {
    cout << tablero[1] << endl;
    return 0;
  }
  if (tablero[2] == tablero[5] && tablero[2] == tablero[8] &&
      tablero[2] != ".") {
    cout << tablero[2] << endl;
    return 0;
  }

  if (tablero[0] == tablero[4] && tablero[0] == tablero[8] &&
      tablero[0] != ".") {
    cout << tablero[0] << endl;
    return 0;
  }
  if (tablero[2] == tablero[4] && tablero[2] == tablero[6] &&
      tablero[2] != ".") {
    cout << tablero[2] << endl;
    return 0;
  }
  cout << "DRAW" << endl;
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