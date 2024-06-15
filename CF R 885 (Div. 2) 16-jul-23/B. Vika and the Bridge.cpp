#include <bits/stdc++.h>
#include <stdlib.h>
#include <iostream>
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
#define borra(vect, n) vect.erase(vect.begin()+n);
#define B begin();
#define E end();
#define copia(v1,v2); copy(v1.begin(), v1.end(), back_inserter(v2));


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

int solve() {
  // Code aquí
  int n,k;
  float minimo;
  cin >> n >> k;
  vector<pii> maxi(k);
  vi ant(k), vect;

  vect = lee(n);
  for (int i = 0; i<n; i++){
    if (maxi[vect[i]-1].first<= i-ant[vect[i]-1]){
      maxi[vect[i]-1].second = maxi[vect[i]-1].first;
      maxi[vect[i]-1].first = i-ant[vect[i]-1];
    } else{
      maxi[vect[i]-1].second = max(maxi[vect[i]-1].second, i-ant[vect[i]-1]);
    }
    ant[vect[i]-1] = i+1;
  }
  for (int i = 0; i<k; i++){
    if (maxi[i].first< n-ant[i]){
      maxi[i].second = maxi[i].first;
      maxi[i].first = n-ant[i];
    } else{
      maxi[i].second = max(maxi[i].second, n-ant[i]);
    }
  }
  minimo = max((maxi[0].first)/2,maxi[0].second);
  for (int i = 1; i<k; i++){
    if (minimo>max((maxi[i].first)/2,maxi[i].second)){
      minimo=max((maxi[i].first)/2,maxi[i].second);
    }
  }
  cout << minimo << endl;
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