#include <bits/stdc++.h>
#include <iostream>
#include <string>
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

int solve() {
  // Code aquí
  string s, l, r;
  int m;

  cin >> s;
  cin >> m;
  cin >> l;
  cin >> r;

  set<int> faltantes;
  int index = 0;

  for (int i = 0; i <= s.size(); i++) {
    if (faltantes.size() == 0) {
      if (index == l.size()) {
        cout << "NO" << endl;
        return 0;
      }
      for (int j = ((int)l[index] - 48); j <= ((int)r[index] - 48); j++) {
        faltantes.insert(j);
      }
      index++;
    }
    if (i == s.size()){
      break;
    }
    if (faltantes.count((int)s[i] - 48)){
      faltantes.erase((int)s[i] - 48);
    }
  }
  cout << "YES" << endl;

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