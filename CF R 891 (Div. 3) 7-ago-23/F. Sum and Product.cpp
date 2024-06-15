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

void Imprime_set(set<int> s) {
  copy(s.begin(), s.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
}

map<lli, lli> lee(int n) {
  int el;
  map<lli, lli> vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect[el] = vect[el] + 1;
  }
  return (vect);
}

int solve() {
  // Code aquí
  int n;
  map<lli, lli> a;
  cin >> n;
  a = lee(n);

  int q;
  lli x, y, sol_f;
  pair<lli, lli> sol1;
  cin >> q;
  while (q--) {
    cin >> x >> y;
    lli prueba = (lli)sqrt(x * x - 4 * y);
    if (prueba * prueba == x * x - 4 * y && (x + prueba) % 2 == 0) {
      sol1.first = (x + prueba) / 2;
      sol1.second = y / sol1.first;
    } else {
      cout << 0 << " ";
      continue;
    }
    if (sol1.first == sol1.second) {
      lli num = a[sol1.first] - 1;
      sol_f = (num + 1) * num / 2;
    } else {
      sol_f = a[sol1.first] * a[sol1.second];
    }
    cout << sol_f << " ";
  }
  cout << endl;
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