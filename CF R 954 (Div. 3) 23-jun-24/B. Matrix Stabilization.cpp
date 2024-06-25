//Librerías incluidas en #include<bitstdc++.h>
#include<algorithm>
#include<array>
#include<atomic>
#include<bitset>
#include<ccomplex>
#include<cerrno>
#include<cfenv>
#include<cfloat>
#include<chrono>
#include<cinttypes>
#include<ciso646>
#include<climits>
#include<clocale>
#include<cmath>
#include<complex>
#include<condition_variable>
#include<csetjmp>
#include<csignal>
#include<cstdalign>
#include<cstdarg>
#include<cstdbool>
#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctgmath>
#include<ctime>
#include<cwchar>
#include<cwctype>
#include<deque>
#include<exception>
#include<forward_list>
#include<fstream>
#include<functional>
#include<future>
#include<initializer_list>
#include<iomanip>
#include<ios>
#include<iosfwd>
#include<iostream>
#include<istream>
#include<iterator>
#include<limits>
#include<list>
#include<locale>
#include<map>
#include<memory>
#include<mutex>
#include<new>
#include<numeric>
#include<ostream>
#include<queue>
#include<random>
#include<ratio>
#include<regex>
#include<scoped_allocator>
#include<set>
#include<sstream>
#include<stack>
#include<stdexcept>
#include<streambuf>
#include<string>
#include<system_error>
#include<thread>
#include<tuple>
#include<type_traits>
#include<typeindex>
#include<typeinfo>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<valarray>
#include<vector>
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

void Imprime(vector<vi> vect) {
  for (int i = 0; i < vect.size(); i++) {
    for (int j = 0; j < vect[i].size(); j++) {
        cout << vect[i][j] << " ";
    }
    cout << endl;
  }
}

void Imprime_set(set<int> s) {
  copy(s.begin(), s.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
}

int maximo_comun_divisor(int a, int b) {
  int temporal; // Para no perder b
  while (b != 0) {
    temporal = b;
    b = a % b;
    a = temporal;
  }
  return a;
}

int minimo_comun_multiplo(int a, int b) {
  return (a * b) / maximo_comun_divisor(a, b);
}

bool isNumeric(string const &str) {
  auto it = str.begin();
  while (it != str.end() && isdigit(*it)) {
    it++;
  }
  return !str.empty() && it == str.end();
}

vector<vi> lee(int n, int m) {
  int el;
  vi vect;
  vector<vi> matriz;
  for (int i = 0; i < n; i++) {
    for (int i = 0; i < m; i++) {
        cin >> el;
        vect.PB(el);
    }
    matriz.PB(vect);
    vect.clear();
  }
  return(matriz);
}


int solve() {
  // Code aquí
  int n, m;
  cin >> n >> m;
  vector<vi> matriz;
  matriz = lee(n,m);
  for (int i = 0; i<n*m; i++){
    int maxi = 0;
    bool cambia = false;
    if (i/m!= 0){ // Mira arriba
        if (matriz[i/m][i%m] > matriz[i/m-1][i%m]){
            maxi = max(maxi,matriz[i/m-1][i%m]);
            cambia = true;
        } else {
            continue;
        }
    }
    if (i/m!= n-1){ // Mira abajo
        if (matriz[i/m][i%m] > matriz[i/m+1][i%m]){
            maxi = max(maxi,matriz[i/m+1][i%m]);
            cambia = true;
        } else {
            continue;
        }
    }
    if (i%m!= 0){ // Mira izquierda
        if (matriz[i/m][i%m] > matriz[i/m][i%m-1]){
            maxi = max(maxi,matriz[i/m][i%m-1]);
            cambia = true;
        } else {
            continue;
        }
    }
    if (i%m!= m-1){ // Mira derecha
        if (matriz[i/m][i%m] > matriz[i/m][i%m+1]){
            maxi = max(maxi,matriz[i/m][i%m+1]);
            cambia = true;
        } else {
            continue;
        }
    }
    if (cambia){
        matriz[i/m][i%m] = maxi;
    }
  }
  Imprime(matriz);

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