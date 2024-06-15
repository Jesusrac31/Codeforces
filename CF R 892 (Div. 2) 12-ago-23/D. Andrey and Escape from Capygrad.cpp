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
  int n, info_basura, l, b;
  cin >> n;
  vi p;
  vector<tuple<int, int, int>> numeros;
  tuple<int, int, int> el;
  for (int i = 0; i < n; i++) {
    cin >> l;
    cin >> info_basura;
    cin >> info_basura;
    cin >> b;
    el = {b, i, 0};
    p.emplace_back(l);
    numeros.emplace_back(el);
  }

  int q, x;
  cin >> q;
  vi sol(q);
  for (int i = 0; i < q; i++) {
    cin >> x;
    el = {x, i, 1};
    numeros.emplace_back(el);
  }
  sort(numeros.begin(), numeros.end());
  reverse(numeros.begin(), numeros.end());

  /*for (int i = 0; i < numeros.size(); i++) {
    cout << "(" << get<0>(numeros[i]) << ", " << get<1>(numeros[i]) << ", " <<
  get<2>(numeros[i]) << "); ";
  }
  cout << endl;*/

  int last_b = 0, last_l = 1000000001;
  for (int i = 0; i < numeros.size(); i++) {
    if (get<2>(numeros[i]) == 1) { // Punto
      // cout << last_l << " " << last_b << endl;
      if (get<0>(numeros[i]) >= last_l && get<0>(numeros[i]) <= last_b) {
        sol[get<1>(numeros[i])] = last_b;
      } else {
        last_b = 0;
        sol[get<1>(numeros[i])] = get<0>(numeros[i]);
      }
    } else { // b
      if (last_b == 0 || get<0>(numeros[i]) < last_l) {
        last_b = get<0>(numeros[i]);
      }
      last_l = min(p[get<1>(numeros[i])], last_l);
    }
  }
  Imprime(sol);

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