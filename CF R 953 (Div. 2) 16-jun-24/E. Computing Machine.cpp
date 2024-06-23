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

int solve(int d) {
  // Code aquí
  int n;
  cin >> n;
  string a, b;
  cin >> a >> b;
  a="11"+a+"11";
  b="00"+b+"00";
  vi unos, suma={0};
  /*
  0 --> Es un 0 siempre
  1 --> Se trata de un 1
  2 --> Si añades el número dos casillas a la izquierda y el de una casilla a la derecha se transforma en 1
  3 --> Si añades el número dos casillas a la derecha y el de una casilla a la izquierda se transforma en 1
  5 --> Si añades el número de la izquierda y el de la derecha se transforma en 1
  6 --> Si añades el número dos casillas a la izquierda y el de dos casillas a la derecha se transforma en 1
  */
  for (int i = 2; i<n+2; i++){
    suma.PB(suma[suma.size()-1]);
    suma[suma.size()-1]++;
    if (a[i] == '1'){
        unos.PB(1);
    } else {
        if (b[i-1] == '1' && b[i+1] == '1'){
            unos.PB(5);
            continue;
        }
        if ((a[i-2] == '0' || b[i-1] == '1') && b[i+1] == '1'){
            unos.PB(2);
            continue;
        }
        if ((a[i+2] == '0' || b[i+1] == '1') && b[i-1] == '1'){
            unos.PB(3);
            continue;
        }
        if (a[i-2] == '0' && a[i+2] == '0'){
            unos.PB(6);
            continue;
        }
        suma[suma.size()-1]--;
        unos.PB(0);
    }
  }
  borra(suma, 0);
  
  //Completa las queries

  int q, l, r, sol;
  cin >> q;
  while(q--){
    d++;
    sol = 0;
    cin >> l >> r;
    l--;
    r--;
    int sol = 0;
    if (l+2<=r-2){
        sol = suma[r-2]-suma[l+1];
    }
    if (unos[r-1] == 2 && l+2<=r-1){
        sol++;
    }
    if (unos[l+1] == 3 && r-2>=l+1){
        sol++;
    }
    if (unos[l+1] == 5 && r-1>=l+1){
        sol++;
    }
    if (unos[r-1] == 5 && r-1>l+1){
        sol++;
    }
    if (unos[l] == 1){
        sol++;
    }
    if (unos[l+1] == 1 && l+1<=r){
        sol++;
    }
    if (unos[r-1] == 1 && r-1>l+1){
        sol++;
    }
    if (unos[r] == 1 && r > l+1){
        sol++;
    }
    cout << sol << endl;
  }
  return d;
}

int main() {
  int T, q = 0;
  cin >> T; // Número de casos
  while (T--) {
    q = solve(q);
  }
  return 0;
}

