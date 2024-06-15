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

bool sort_func(pii a, pii b) {
  if (a.first < b.first) {
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

vector<pii> lee(int n) {
  int el;
  vector<pii> vect;
  pii elemento;
  for (int i = 0; i < n; i++) {
    cin >> el;
    elemento.first = el;
    elemento.second = i;
    vect.PB(elemento);
  }
  return (vect);
}

int solve() {
  // Code aquí
  int n;
  vector<pii> a;
  cin >> n;
  a = lee(n);

  ord(a);

  int tamano = n, l = 0, r = n - 1;
  vi resp(n);

  while (l <= r) {
    if (a[l].first == n - 1 - r ^ a[r].first == n - l) {
      if (a[l].first == n - 1 - r) {
        resp[a[l].second] = -tamano;
        l++;
      } else {
        resp[a[r].second] = tamano;
        r--;
      }
      tamano--;
    } else {
      cout << "NO" << endl;
      return 0;
    }
  }
  cout << "YES" << endl;
  Imprime(resp);

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