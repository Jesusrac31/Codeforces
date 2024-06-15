#include <bits/stdc++.h>
#include <iostream>
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
  lli n, x, y;
  cin >> n >> x >> y;
  string a, b;
  cin >> a;
  cin >> b;
  vi changes;
  for (int i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      changes.PB(i);
    }
  }
  // Imprime(changes);
  if (changes.size() % 2 == 0) {
    lli cost = 0;
    if (y <= x) {
      if (changes.size() == 2) {
        if ((changes[1] - changes[0]) == 1) {
          if (x < 2 * y) {
            cost = x;
          } else {
            cost = 2 * y;
          }
        } else {
          cost = y;
        }
      } else {
        cost = (changes.size() / 2) * y;
      }
    } else {
      int pares = 0;
      for (int i = 1; i < changes.size(); i++) {
        if (changes[i] - changes[i - 1] == 1) {
          pares += 1;
          i--;
        }
      }
      cost = pares * x + changes.size() * y / 2;
    }
    cout << cost << endl;
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