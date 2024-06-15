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

vi lee(int n) {
  int el;
  vi vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

int solve() {
  // Code aquí
  int n;
  vi a, b;
  cin >> n;
  a = lee(n);
  b = lee(n);

  int tipo = 0, tipo_caso;
  vector<pii> posibles(3);

  for (int i = 0; i < n; i++) {
    if (a[i] != 0 || b[i] != 0) {
      posibles[0].first = a[i];
      posibles[0].second = 1;
      posibles[0].first = b[i];
      posibles[0].second = 2;
      posibles[0].first = abs(a[i] - b[i]);
      posibles[0].second = 3;
      if (posibles[0].first = a[i] == 0) {
        tipo_caso = 1;
      } else if (posibles[0].first = a[i] == 0) {
        tipo_caso = 2;

      } else if (posibles[0].first = a[i] == 0) {
        tipo_caso = 3;

      } else {
        ord(posibles);
        if (posibles[0] == posibles[1]) {
          tipo_caso = posibles[2].second;
        } else {
          tipo_caso = posibles[1].second;
        }
      }
      cout << tipo_caso << endl;
      if (tipo == 0) {
        tipo = tipo_caso;
      } else {
        if (tipo != tipo_caso) {
          cout << "NO" << endl;
          return 0;
        }
      }
    }
  }
  cout << "YES" << endl;

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