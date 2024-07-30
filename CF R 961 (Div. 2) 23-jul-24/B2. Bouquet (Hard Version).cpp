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

bool sort_func(pair<lli, lli> a, pair<lli, lli> b) {
  if (a.first < b.first) {
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

vll lee(int n) {
  lli el;
  vll vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

int solve() {
  // Code aquí
  lli n, m;
  cin >> n >> m;
  vector<pair<lli, lli>> petals_prov, petals;
  lli el;
  pair<lli, lli> par;
  par.second = 0;
  for (int i = 0; i<n; i++){
    cin >> el;
    par.first = el;
    petals_prov.PB(par);
  }
  for (int i = 0; i<n; i++){
    cin >> el;
    petals_prov[i].second = el;
  }
  ord(petals_prov);
  petals.PB(petals_prov[0]);
  for (int i = 1; i<n; i++){
    if (petals[petals.size()-1].first == petals_prov[i].first){
        petals[petals.size()-1].second += petals_prov[i].second;
    } else {
        petals.PB(petals_prov[i]);
    }
  }

  lli petalos_max = petals[0].first * min((m/petals[0].first), petals[0].second);
  for (int i = 1; i<petals.size(); i++){
    lli suma = 0;
    if (petals[i].first == petals[i-1].first+1){
        //Combean
        //cout << "---COMBO---" << endl;
        lli count_pequeno = 0, count_grande = 0;
        count_pequeno = min(m/petals[i-1].first, petals[i-1].second);
        suma += count_pequeno * petals[i-1].first;
        count_grande = min((m-suma)/petals[i].first, petals[i].second);
        suma += count_grande*petals[i].first;
        count_grande = petals[i].second-count_grande;
        suma+=min(min(m-suma, count_grande), count_pequeno);
    } else {
        suma = petals[i].first * min((m/petals[i].first), petals[i].second);
    }
    //cout << "suma --> " << suma << endl;
    petalos_max = max(petalos_max, suma);
  }
  cout << petalos_max << endl;

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