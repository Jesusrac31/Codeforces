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
    if (i % 30 == 29) {
      cout << endl;
    }
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

vi posibles;
set<int> marcadas, trayecto;

void resuelve(vector<vector<int>> conexiones, int vertice) {
  trayecto.insert(vertice);
  for (int i = 0; i < conexiones[vertice].size(); i++) {
    if (!trayecto.count(conexiones[vertice][i])) {
      if (!marcadas.count(conexiones[vertice][i])) {
        resuelve(conexiones, conexiones[vertice][i]);
      }
      posibles[vertice] = posibles[vertice] + posibles[conexiones[vertice][i]];
    }
  }
  if (posibles[vertice] == 0) {
    posibles[vertice]++;
  }
  trayecto.erase(vertice);
  marcadas.insert(vertice);
}
int query = 1;

int solve(int T) {
  // Code aquí
  int n;
  cin >> n;
  vector<vector<int>> conexiones(n);
  int u, v;
  posibles.clear();
  marcadas.clear();
  trayecto.clear();
  for (int i = 0; i < n - 1; i++) {
    posibles.PB(0);
    cin >> u >> v;
    conexiones[u - 1].PB(v - 1);
    conexiones[v - 1].PB(u - 1);
  }

  posibles.PB(0);
  resuelve(conexiones, 0);
  int q, a, b;
  cin >> q;
  for (int i = 0; i < q; i++) {
    cin >> a >> b;
    cout << posibles[a - 1] * posibles[b - 1] << endl;
    query++;
  }

  return 0;
}

int main() {
  int T;
  cin >> T; // Número de casos
  while (T--) {
    solve(T);
  }
  return 0;
}