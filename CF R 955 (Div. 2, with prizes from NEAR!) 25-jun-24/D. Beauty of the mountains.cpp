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

void Imprime(vi vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i] << " ";
  }
  cout << "\n";
}

void Imprime2d(vector<vi> vect) {
  for (int j = 0; j<vect.size(); j++){
    for (int i = 0; i < vect[j].size(); i++) {
        cout << vect[j][i] << " ";
    }
    cout << "\n";
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

vi lee(int n) {
  int el;
  vi vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

vector<vi> lee2d(int n, int m) {
  int el;
  vector<vi> vect;
  for (int i = 0; i < n; i++) {
    vect.PB({});
    for (int j = 0; j < m; j++) {
        cin >> el;
        vect[i].PB(el);
    }
  }
  return (vect);
}

int solve() {
  // Code aquí
  int n, m, k;
  cin >> n >> m >> k;
  vector<vi> heights;
  heights = lee2d(n,m);
  vector<string> nieve;
  //Lectura de si la montaña está nevada
  string el;
  for (int i = 0; i<n; i++){
    cin >> el;
    nieve.PB(el);
  }
  int recuento=0;
  for(int i = 0; i<n; i++){
    for (int j = 0; j<m; j++){
        if (nieve[i][j] == '0'){
            recuento+=heights[i][j];
        } else {
            recuento-=heights[i][j];
        }
    }
  }

  int parametros = -1;
  int suma;
  for (int i = 0; i<n-k+1; i++){
    suma = 0;
    for (int l = 0; l<k; l++){
        for (int o = 0; o<k; o++){
            if (nieve[i+l][o] == '0'){
                suma++;
            } else {
                suma--;
            }
        }
    }
    suma = abs(suma);
    if (suma != 0){
        if (parametros == -1){
            parametros = suma;
        }
        if (max(parametros,suma)%min(parametros,suma) != 0 && parametros%2 == 1){
            parametros = 1;
            break;
        } else if (parametros%2==0){
            if (parametros-suma != 0){
                parametros = min(min(suma, parametros),abs(parametros-suma));
            }
        }else {
            parametros = min(parametros,suma);
        }
    }
    for (int j = 1; j<m-k+1; j++){
        for (int l = 0; l<k; l++){
            if (nieve[i+l][j-1] == '0'){
                suma--;
            } else {
                suma++;
            }
            if (nieve[i+l][j+k-1] == '0'){
                suma++;
            } else {
                suma--;
            }
        }
        suma = abs(suma);
        if (suma != 0){
            if (parametros == -1){
                parametros = suma;
            }
            if (max(parametros,suma)%min(parametros,suma) != 0 && parametros%2 == 1){
                parametros = 1;
                break;
            } else if (parametros%2==0){
                if (parametros-suma != 0){
                    parametros = min(abs(parametros-suma), parametros);
                    parametros = min(parametros, suma);
                }
            }else {
                parametros = min(parametros,suma);
            }
        }
    }
  }
  if (recuento%parametros == 0 && parametros != -1){
    cout << "YES" << endl;
  } else if (recuento == 0) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr); 
  int T;
  cin >> T; // Número de casos
  while (T--) {
    solve();
  }
  return 0;
}

//Eliminar comentario si el proyecto está terminado (Dinámica empezó el 21/06/2024)