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
#define ord(vect) sort(vect.begin(), vect.end, sort_func);

#define borra_el(vect, el) vect.erase(vect.find(el));
#define borra_range(vect, a, b) vect.erase(a, b);
#define borra(vect, n) vect.erase(vect.begin() + n);
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
vi fibonacci;

int solve() {
  // Code aquí
  int n, k, contador = 0;

  cin >> n >> k;
  if (k > 28){
    cout << 0 << endl;
    return 0;
  }
  for (int a = 0; a<=((n-fibonacci[k-2]*a)/fibonacci[k-1]); a++){
    if (((n-fibonacci[k-2]*a)%fibonacci[k-1])==0){
      contador++;
    }
  }
  cout << contador << endl;

  return 0;
}

int main() {
  fibonacci.PB(0);
  fibonacci.PB(1);
  for (int i =2 ;i<28; i++){
    fibonacci.PB(fibonacci[i-2]+fibonacci[i-1]);
  }
  int T;
  cin >> T; // Número de casos
  while (T--) {
    solve();
  }
  return 0;
}