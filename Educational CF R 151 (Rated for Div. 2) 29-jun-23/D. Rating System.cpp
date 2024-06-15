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

lli relu(lli a) { return ((a + abs(a)) / 2); }

void Imprime(vector<lli> vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i] << " ";
  }
  cout << endl;
}

void Imprime_set(set<int> s) {
  copy(s.begin(), s.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
}

lli suma_total = 0;

vector<lli> lee(lli n) {
  suma_total = 0;
  lli el;
  vector<lli> vect;
  vect.PB(0);
  for (int i = 0; i < n; i++) {
    cin >> el;
    suma_total = suma_total + el;
    if (vect[vect.size() - 1] < 0 ^ el < 0) {
      vect.PB(el);
    } else {
      vect[vect.size() - 1] = vect[vect.size() - 1] + el;
    }
  }
  if (vect[vect.size() - 1] < 0) {
    vect.PB(0);
  }
  return (vect);
}

int solve(int T) {
  // Code aquí
  lli n, k, suma_k, t = 421;
  vector<lli> a, suma_final, suma_inicio;
  cin >> n;
  a = lee(n);

  /*if (T == 10000 - t) {
    Imprime(a);
  }*/

  if (a.size() >= 2) {

    suma_inicio.PB(suma_total - a[a.size() - 1] - a[a.size() - 2]);
    k = suma_inicio[suma_inicio.size() - 1];
    suma_k = k;
    lli neg = 0, guardado = 0;

    for (int i = a.size() - 4; i < a.size(); i = i - 2) {
      suma_inicio.PB(suma_inicio[suma_inicio.size() - 1] - a[i + 1] - a[i]);
      neg = neg + a[i + 1] + a[i + 2];
      if (neg > 0) {
        guardado = guardado + neg;
        neg = 0;
      }
      if (suma_k < guardado + suma_inicio[suma_inicio.size() - 1]) {
        suma_k = guardado + suma_inicio[suma_inicio.size() - 1];
        k = suma_inicio[suma_inicio.size() - 1];
      }
    }

    // if (T <= 10000 - t) {
    if (k > 0) {
      cout << k << endl;
    } else {
      cout << a[0] << endl;
    }
    //}

  } else {
    // if (T <= 10000 - t) {
    cout << 0 << endl;
    //}
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