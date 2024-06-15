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
  vect.PB(1);
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

int solve() {
  // Code aquí
  int n, m, d;
  lli suma = 0;
  vi s;
  cin >> n >> m >> d;
  s = lee(m);
  s.PB(n);

  vi dif, CPB;
  for (int i = 1; i < s.size(); i++) {
    dif.PB(s[i] - s[i - 1]);
    if (i == s.size() - 1) {
      CPB.PB((s[i] - s[i - 1]) / d);
    } else {
      CPB.PB((s[i] - s[i - 1] + d - 1) / d);
    }
    suma = suma + CPB[CPB.size() - 1];
  }
  suma++;
  // Imprime(dif);
  // Imprime(CPB);
  vi resultados;
  for (int i = 1; i < dif.size(); i++) {
    if (i == dif.size() - 1) {
      resultados.PB(((dif[i] + dif[i - 1]) / d) - (CPB[i] + CPB[i - 1]));
      continue;
    }
    resultados.PB(((dif[i] + dif[i - 1] + d - 1 - i / (dif.size() - 1)) / d) -
                  (CPB[i] + CPB[i - 1]));
  }
  // Imprime(resultados);
  ord(resultados);
  int resp = 1;
  while (resultados[resp % resultados.size()] == resultados[0] &&
         resp < resultados.size()) {
    resp++;
  }
  cout << suma + resultados[0] << " " << resp << endl;
  // << "-----------------------------" << endl;

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