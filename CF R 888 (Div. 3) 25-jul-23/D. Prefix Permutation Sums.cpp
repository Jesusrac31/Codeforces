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

bool sort_func(lli a, lli b) {
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

void Imprime(vll vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i] << " ";
  }
  cout << endl;
}

vll lee(int n) {
  lli el;
  vll vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

int solve() {
  // Code aquí
  lli n, rec = 0, contador = 0, repe = -1;
  vll a, b, mal;
  cin >> n;
  a = lee(n - 1);
  for (int i = 0; i < n - 1; i++) {
    b.PB(a[i] - rec);
    rec = a[i];
  }
  ord(b);

  if (n - 1 > 1) {
    if (b[n - 3] > n) {
      cout << "NO" << endl;
      return 0;
    }
  }
  for (int i = 0; i < n - 1; i++) {
    contador++;
    while (contador < b[i] && contador <= n) {
      mal.PB(contador);
      contador++;
    }
    if (contador > b[i]) {
      if (repe != -1) {
        cout << "NO" << endl;
        return 0;
      }
      repe = b[i];
      contador--;
    }
  }
  contador++;
  while (contador <= n) {
    mal.PB(contador);
    contador++;
  }
  if (b[n - 2] > n) {
    if (repe != -1) {
      cout << "NO" << endl;
      return 0;
    }
    repe = b[n - 2];
  }

  if (mal.size() == 1) {
    cout << "YES" << endl;
  } else if (mal.size() == 2) {
    if (mal[0] + mal[1] == repe) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  } else {
    cout << "NO" << endl;
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