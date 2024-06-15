#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef map<int, int> mii;
typedef map<string, int> msi;
typedef map<int, vector<int>> miv;

// Funciones standard
#define repite(n)                                                              \
  for (int i = 0; i < n; i++)                                                  \
    ;

// Funciones vector
#define PB(a) push_back(a);
#define ord(vect) sort(vect.begin(), vect.end, sort_func);

#define borra_el(vect, el) vect.erase(vect.find(el));
#define borra_range(vect, a, b) vect.erase(a, b);
#define corta(vect, n) vect.erase(n);
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

vi lee(vi vect, int n) {
  int el;
  repite(n) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

int solve() {
  // Code aquí
  int n, x, y;
  cin >> n >> x >> y;
  if (x == 0 ^ y == 0) {
    if ((n - 1) % (x + y) == 0) {
      int win = 2, change = 0;
      for (int i = 1; i < n; i++) {
        change++;
        cout << win << " ";
        if (i % (x + y) == 0) {
          win += change;
          change = 0;
        }
      }
      cout << endl;
    } else {
      cout << "-1" << endl;
    }
  } else {
    cout << "-1" << endl;
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