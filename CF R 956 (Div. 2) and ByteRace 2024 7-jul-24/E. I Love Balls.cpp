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
const lli mod = 1e9 + 7;

lli q_M(lli x, lli p = mod - 2) {
    if (p == 0) {
        return 1;
    }
    //Este fragmento tan solo se ocupa de optimizar la optención del resultado con la propiedad de las potencias a^2b = (a^2)^b
    if (p & 1) { // si es impar
        return q_M(x, p - 1) * x % mod;
    }
    //Aquí podriamos restar 1 a p pero traería problemas cuando el p de la función es par por lo que aprovechamos el truncamiento que hace por default el long long int de c++
    return q_M(x * x % mod, p / 2);
}

int solve() {
  // Code aquí
  lli n, k;
  cin >> n >> k;
  lli tot_n=0, tot_k = 0, el, p, q, bob;
  for (int i = 0; i<k; i++){
    cin >> el;
    tot_k += el;
  }
  for (int i = 0; i<n-k; i++){
    cin >> el;
    tot_n += el;
  }
  if (n!=k){
    lli factor1 = (n-k)/2;
    lli factor2 = (n-k+1)/2;
    p=(((((tot_n%mod)*(((n-k)/2)%mod))%mod)*((n-k+1)%mod))%mod+(((((tot_k%mod)*(((n-k+1)/2)%mod))%mod)*((n-k)%mod))%mod))%mod;
    //En una ecuación modular de la forma qx≡p (mod M) la solución de x siempre será una vez despejada x≡p*q^(M-2) (mod M) 
    //ya que M es un número primo lo que hace que respete la explicación del siguiente enlace:
    //https://www.youtube.com/watch?v=aa8dRPJkzA0&
    //Aplicando la propiedad de la multiplicación de los módulos podemos hayar un número que me sea equivalente a q^(M-2) que obtendremos a partir de la función q_M()
    q=(q_M(((n-k)*(n-k+1))%mod))%mod;
    bob = (p*q)%mod;
    cout << (tot_n+tot_k-bob+mod)%mod << " " << (bob)%mod << endl;
  } else {
    cout << (tot_k+tot_n)%mod << " " << 0 << endl;
  }
  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr); 
  int T, a;
  cin >> T; // Número de casos
  while (T--) {
    a = solve();
    if (a == 2){
        break;
    }
  }
  
  return 0;
}
