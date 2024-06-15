#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef map<int, int> mii;
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

void Imprime(vector<vector<int>> vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i][0] << " " << vect[i][1] << ";   ";
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
  int n, m, l, r;
  vector<vector<int>> opciones;
  string s;
  bool original = false;
  cin >> n >> m;
  vi puntos_inflexion;
  cin >> s;
  for (int i = 1; i < n; i++) {
    if (s[i] != s[i - 1]) {
      if (s[i] == '1') {
        puntos_inflexion.PB(i);
      }
    }
  }
  ord(puntos_inflexion);
  /*for (int i = 0; i < puntos_inflexion.size(); i++) {
    cout << puntos_inflexion[i] << ";   ";
  }
  cout << endl;*/
  while (m--) {
    cin >> l >> r;
    if (s[l - 1] == '0') {
      for (int i = 0; i < puntos_inflexion.size()+1; i++) {
        if (i == puntos_inflexion.size()){
          l=puntos_inflexion.size();
          break;
        }
        if (puntos_inflexion[i] > l) {
          l = puntos_inflexion[i]+1;
          break;
        }
      }
    }
    if (s[r - 1] == '1') {
      for (int i = puntos_inflexion.size() - 1; i >= 0; i--) {
        if (i == puntos_inflexion.size()){
          r=0;
          break;
        }
        if (puntos_inflexion[i] < r) {
          r = puntos_inflexion[i];
          break;
        }
      }
    }
    if (r - l < 0) {
      original = true;
    } else {
      vi vect = {l, r};
      bool inserta = true;
      for (int i = 0; i < opciones.size(); i++) {
        if (l == opciones[i][0] && r == opciones[i][1]) {
          inserta = false;
          break;
        }
        if (l < opciones[i][0] || (l == opciones[i][0] && r < opciones[i][1])) {
          cout << l << " " << r << endl;
          if (i + 1 == opciones.size()) {
            opciones.PB(vect);
          } else {
            opciones.insert(opciones.begin() + i + 1, vect);
          }
          inserta = false;
          break;
        }
      }
      if (inserta) {
        opciones.PB(vect);
      }
      Imprime(opciones);
    }
  }
  Imprime(opciones);
  cout << opciones.size() + original << endl;

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