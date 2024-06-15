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
    vect.push_back(el);
  }
  return (vect);
}

int solve() {
  // Code aquí
  vi vect;
  int n;
  cin >> n;
  vect = lee(n);
  cout << n - 1 << endl;
  if (n - 1 != 0) {
    cout << "1 " << n << endl;
    int mod = vect[0] % 2;
    for (int i = 1; i < n - 1; i++) {
      if (vect[i] % 2 == mod) {
        cout << i + 1 << " " << n << endl;
      } else {
        cout << i << " " << i + 1 << endl;
      }
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