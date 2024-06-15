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
  int n,k,x;
  cin >> n >> k >> x;

  if (x != 1){
    cout << "YES" << endl;
    cout << n << endl;
    for (int i = 0; i<n; i++) {
      cout << "1 ";
    }
    cout << endl;
  }
  else{
    if (k == 1){
      cout << "NO" << endl;
    }
    else if (k == 2){
      if (n%2 == 0){
        cout << "YES" << endl;
        cout << n/2 << endl;
        for (int i = 0; i<n/2; i++) {
          cout << "2 ";
        }
        cout << endl;
      }
      else{
        cout << "NO" << endl;
      }
    }
    else {
      cout << "YES" << endl;
      cout << n/2 << endl;
      if (n%2 == 0){
        for (int i = 0; i<n/2; i++) {
          cout << "2 ";
        }
        cout << endl;
      }
      else{
        for (int i = 0; i<n/2-1; i++) {
          cout << "2 ";
        }
        cout << "3 " << endl;
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