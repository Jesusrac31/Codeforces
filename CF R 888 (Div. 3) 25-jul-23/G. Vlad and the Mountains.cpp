#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef map<int, int> mii;
typedef map<string, int> msi;
typedef map<int, vector<int>> miv;

// Funciones vector
#define PB(a) push_back(a);
#define ord(vect) sort(vect.begin(), vect.end, sort_func);

#define borra_el(vect, el) vect.erase(vect.find(el));
#define borra_range(vect, a, b) vect.erase(a, b);
#define borra(vect, n) vect.erase(vect.begin() + n);
#define B begin();
#define E end();

// Funciones map
#define F first;
#define S second;

// Logaritmo de 2
double log_2 = log(2);
double log2(int a) { return (log(a) / log_2); }

// bool sort_func(int a, int b) {}

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
  int n, m;
  vi h;
  vector<vector<int>> conex;

  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    vi fila;
    conex.PB(fila);
  }

  h = lee(n);

  int m1, m2;
  for (int i = 0; i < m; i++) {
    cin >> m1 >> m2;
    conex[m1 - 1].PB(m2 - 1);
  }

  int q;
  cin >> q;
  while (q--) {
    int a, b, e;
    vi marcadas(n), adyascentes;
    cin >> a >> b >> e;
    a--;
    b--;
    marcadas[a] = 1;
    for (int i = 0; i < conex[a].size(); i++) {
      adyascentes.PB(conex[a][i]);
    }
    while (adyascentes.size() > 0) {
      for (int i = 0; i < adyascentes.size(); i++) {
        if (h[conex[adyascentes[0]][i]] < h[a] + e) {
          marcadas[adyascentes[i]] = 1;
        }
      }
      int len = adyascentes.size();
      while (len--) {
        for (int i = 0; i < conex[adyascentes[0]].size(); i++) {
          if (marcadas[conex[adyascentes[0]][i]] == 0 &&
              h[conex[adyascentes[0]][i]] < h[a] + e) {
            adyascentes.PB(conex[adyascentes[0]][i]);
          }
        }
        adyascentes.erase(adyascentes.begin());
      }
    }
    if (marcadas[b] == 1) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
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