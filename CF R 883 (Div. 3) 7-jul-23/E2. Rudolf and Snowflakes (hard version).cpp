#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef pair<int, int> pii;
typedef map<int, int> mii;
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

set<lli> posibles;

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

bool print;

int solve(int T) {
  // Code aquí
  lli n;
  cin >> n;
  if (print && T == 10000-150){
    cout << n << endl;
  }
  if (posibles.count(n) == 1) {
    cout << "YES" << endl;
  } 
  else {
    long double val = ((lli)sqrt(4*n-3)-1)/2;
    long long int val_int = (4*n-3);
    if (pow(round(val)*2+1,2) == val_int && val >=2){
      //cout << val_int << " " << val << endl;
      cout << "YES" << endl;
    } 
    else {
      cout << "NO" << endl;
    }
  }
  if (T == 10000-1 && 1000015000057 == n){
    print=false;
  }
  return 0;
}

int main() {
  int T;
  lli valor, val;
  for (lli k = 2; k < 1000000; k++) {
    valor = k*k;
    val = (k*k*k-1)/(k-1);
    for (lli i = 3; (pow(k, i) - 1) / (k - 1) < 1000000000000000000; i++) {
      /*if (k==662815 && i == 4){
        cout << val<< endl;
      }*/
      posibles.insert(val);
      valor = valor*k;
      val = valor + val;
    }
  }
  //cout << posibles.size() << endl;
  cin >> T; // Número de casos
  while (T--) {
    solve(T);
  }
  return 0;
}