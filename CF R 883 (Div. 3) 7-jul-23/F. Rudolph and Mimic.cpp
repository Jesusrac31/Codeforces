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

vi lee(int n) {
  int el;
  vi vect(9);
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

int solve() {
  // Code aquí
  int n, tipo_m;
  cin >> n;
  vi normal, a(9), b;
  int el;
  for (int i = 0; i < n; i++) {
    cin >> el;
    normal.PB(el);
    a[el - 1]++;
  }
  bool fuera = false;
  while (true) {
    cout << "- 0" << endl;
    cout.flush();
    b.clear();
    for (int i = 0; i < 9; i++) {
      b.PB(0);
    }
    normal.clear();
    for (int i = 0; i < n; i++) {
      cin >> el;
      normal.PB(el);
      b[el - 1]++;
    }
    for (int i = 0; i < b.size(); i++) {
      if (b[i] > a[i]) {
        tipo_m = i;
        cout << "- " << n-b[i] << " ";
        for (int j = 0; j < normal.size(); j++) {
          if (normal[j] != i+1) {
            cout << j + 1 << " ";
          }
        }
        cout << endl;
        cout.flush();
        fuera = true;
        break;
      }
    }
    if (fuera) {
      fuera = false;
      break;
    }
  }

  // solo un número

  while (true) {
    for (int i = 0; i < b[tipo_m]; i++) {
      cin >> el;
      normal.PB(el);
      if (el - 1 != tipo_m) {
        cout << "! " << i + 1 << endl;
        cout.flush();
        fuera = true;
      }
    }
    if (fuera) {
      fuera = false;
      break;
    }
    cout << "- 0" << endl;
    cout.flush();
  }
  
  return 0;
}

int main() {
  int T;
  cin >> T; // Número de casos
  while (T--) {
    solve();
    cout << endl;
  }
  return 0;
}