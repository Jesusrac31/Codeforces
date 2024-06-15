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
  vi vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

int solve(int T) {
  // Code aquí
  int n, maxi = -21, maxi_index, mini = 21, mini_copy, mini_index;
  vi a, b, pos, neg;
  bool ok1 = false, ok2 = false;
  vector<pii> operaciones, operaciones2;
  pii elemento;
  cin >> n;
  a = lee(n);
  copia(a, b);

  /*if (T==500-12){
    Imprime(a);
  }*/
  for (int i = 0; i < a.size(); i++) {
    if (maxi < a[i]) {
      maxi = a[i];
      maxi_index = i;
    }
    if (mini > a[i]) {
      mini = a[i];
      mini_index = i;
    }
    if (a[i] > 0) {
      pos.PB(i);
    }
    if (a[i] < 0) {
      neg.PB(i);
    }
  }
  mini_copy = mini;
  if (mini < 0) {
    ok1 = true;
    while (abs(mini) < abs(maxi)) {
      a[mini_index] = a[mini_index] + mini;
      mini = mini + mini;
      elemento.first = mini_index;
      elemento.second = mini_index;
      operaciones.PB(elemento);
    }
    for (int i = 0; i < pos.size(); i++) {
      a[pos[i]] = a[pos[i]] + mini;
      elemento.first = pos[i];
      elemento.second = mini_index;
      operaciones.PB(elemento);
    }
    for (int i = a.size() - 2; i >= 0; i--) {
      if (a[i] > a[i + 1]) {
        a[i] = a[i] + a[i + 1];
        elemento.first = i;
        elemento.second = i + 1;
        operaciones.PB(elemento);
      }
    }
  }
  if (maxi > 0) {
    ok2 = true;
    while (abs(maxi) < abs(mini_copy)) {
      b[maxi_index] = b[maxi_index] + maxi;
      maxi = maxi + maxi;
      elemento.first = maxi_index;
      elemento.second = maxi_index;
      operaciones2.PB(elemento);
    }
    for (int i = 0; i < neg.size(); i++) {
      b[neg[i]] = b[neg[i]] + maxi;
      elemento.first = neg[i];
      elemento.second = maxi_index;
      operaciones2.PB(elemento);
    }
    for (int i = 1; i < b.size(); i++) {
      if (b[i] < b[i - 1]) {
        b[i] = b[i] + b[i - 1];
        elemento.first = i;
        elemento.second = i - 1;
        operaciones2.PB(elemento);
      }
    }
  }
  if ((operaciones.size() < operaciones2.size() && ok1) || !ok2) {
    cout << operaciones.size() << endl;
    for (int i = 0; i < operaciones.size(); i++) {
      cout << operaciones[i].first + 1 << " " << operaciones[i].second + 1
           << endl;
    }
  } else {
    cout << operaciones2.size() << endl;
    for (int i = 0; i < operaciones2.size(); i++) {
      cout << operaciones2[i].first + 1 << " " << operaciones2[i].second + 1
           << endl;
    }
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