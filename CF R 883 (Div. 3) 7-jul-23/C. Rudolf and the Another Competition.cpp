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
bool sort_func2(pair<int, lli> a, pair<int, lli> b) {
  return a.first > b.first || (a.first == b.first && a.second < b.second);
}
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

vector<vector<int>> lee(int n, int m) {
  int el;
  vector<vector<int>> vect;
  vi vect2;
  for (int i = 0; i < n; i++) {
    vect2.clear();
    for (int j = 0; j < m; j++) {
      cin >> el;
      vect2.PB(el);
    }
    ord(vect2);
    vect.PB(vect2);
  }
  return (vect);
}

int solve() {
  // Code aquí
  int n, m, h;
  cin >> n >> m >> h;

  pair<int, lli> Rudolf;
  int el;
  lli cont = 0;
  vi tiempo;
  for (int i = 0; i < m; i++) {
    cin >> el;
    tiempo.PB(el);
  }
  ord(tiempo);
  Rudolf.second = 0;
  for (Rudolf.first = 0; Rudolf.first < tiempo.size(); Rudolf.first++) {
    cont = cont + tiempo[Rudolf.first];
    if (cont > h) {
      break;
    } else {
      Rudolf.second = Rudolf.second + cont;
    }
  }

  vector<vector<int>> tiempos;
  vector<pair<int, lli>> pp(n - 1);
  tiempos = lee(n - 1, m);

  int j;
  lli penalty, suma;
  for (int i = 0; i < n - 1; i++) {
    suma = 0;
    penalty = 0;
    j = 0;
    for (j = 0; j < m; ++j) {
      suma = suma + tiempos[i][j];
      if (suma > h) {
        break;
      } else {
        penalty = penalty + suma;
      }
    }
    // cout << j << " " << penalty << endl;
    pp[i].first = j;
    pp[i].second = penalty;
  }
  sort(pp.begin(), pp.end(), sort_func2);
  /*for (int i = 0; i<pp.size(); i++){
    cout << pp[i].first << " " << pp[i].second << endl;
  }*/
  int i = 0;
  // cout << "Rudolf "  << Rudolf.first << " " << Rudolf.second << endl;
  for (i = 0; i < pp.size(); i++) {
    // cout << pp[i].first << " " << pp[i].second << endl;
    if (Rudolf.first > pp[i].first ||
        (Rudolf.first == pp[i].first && Rudolf.second <= pp[i].second)) {
      break;
    }
  }
  cout << i + 1 << endl;

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