#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef map<int, int> mii;
typedef map<string, int> msi;
typedef map<int, vector<int>> miv;

// Funciones vector
#define PB(a) push_back(a);

bool sort_func(lli a, lli b) {
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
double log2(lli a) { return (log(a) / log_2); }

vll c, P_descartadas, coste_min;
vector<vector<long long int>> recetas;

void Imprime(vll vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i] << " ";
  }
  cout << endl;
}

vll lee(lli n) {
  lli el;
  vll vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

lli calcula(lli pocima){
  lli coste=0;
  for (int i=0; i<recetas[pocima].size(); i++){
    if (P_descartadas[recetas[pocima][i]] == 1){
      coste = coste + coste_min[recetas[pocima][i]];
    } else {
      coste = coste + calcula(recetas[pocima][i]);
    }
  }
  if (recetas[pocima].size()==0){
    coste_min[pocima] = c[pocima];
  }
  else{
    coste_min[pocima] = min(coste, c[pocima]);
  }
  P_descartadas[pocima] = 1;
  return(coste_min[pocima]);
}

int solve() {
  c.clear();
  P_descartadas.clear();
  recetas.clear();
  coste_min.clear();
  // Code aquí
  lli n, k;
  cin >> n >> k;
  c = lee(n);
  for (int i = 0; i<n; i++){
    P_descartadas.PB(0);
  }
  lli el;
  for (int i = 0; i < k; i++) {
    cin >> el;
    c[el-1] = 0;
  }
  copia(c, coste_min);
  for (int i = 0; i < n; i++) {
    vll fila;
    lli m;
    cin >> m;
    lli el;
    for (int i = 0; i < m; i++) {
      cin >> el;
      fila.PB(el-1);
    }
    recetas.PB(fila);
  }
  for (int i = 0; i<n; i++){
    if (P_descartadas[i] == 0){
      calcula(i);
    }
  }
  Imprime(coste_min);

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