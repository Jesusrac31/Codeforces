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

vll lee(lli n) {
  lli el;
  lli tot=0;
  vll vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    tot+=el;
    vect.PB(el);
  }
  vect.PB(tot);
  return (vect);
}

int solve() {
  // Code aquí
  lli n, tot;
  cin >> n;
  vll a, b, c;
  a = lee(n);
  b = lee(n);
  c = lee(n);
  tot=a[n];
  a.pop_back();
  b.pop_back();
  c.pop_back();

  if (tot%3 != 0){
    tot/=3;
    tot++;
  } else {
    tot/=3;
  }

  lli sum_a = 0, sum_b = 0, sum_c = 0;
  int la=n, lb=n, lc=n, ra=0, rb=0, rc=0;

  for (int i = 0; sum_a<tot || sum_b<tot || sum_c<tot; i++){
    sum_a+=a[i];
    sum_b+=b[i];
    sum_c+=c[i];
    if (sum_a >= tot){
        la = min(la,i);
    }
    if (sum_b >= tot){
        lb = min(lb,i);
    }
    if (sum_c >= tot){
        lc = min(lc,i);
    }
  }
  sum_a = 0; 
  sum_b = 0; 
  sum_c = 0;
  for (int i = n-1; sum_a<tot || sum_b<tot || sum_c<tot; i--){
    sum_a+=a[i];
    sum_b+=b[i];
    sum_c+=c[i];
    if (sum_a >= tot){
        ra = max(ra,i);
    }
    if (sum_b >= tot){
        rb = max(rb,i);
    }
    if (sum_c >= tot){
        rc = max(rc,i);
    }
  }
  lli recuento_ab=0, recuento_ac=0, recuento_ba=0, recuento_bc=0, recuento_ca=0, recuento_cb=0;

  for (int i = 0; i<n; i++){
    if (i>la){
        if (i<rb){
            recuento_ab+=c[i];
            //cout << "ab" << endl;
        }
        if (i<rc){
            recuento_ac+=b[i];
            //cout << "ac" << endl;
        }
    }
    if (i>lb){
        if (i<ra){
            recuento_ba+=c[i];
            //cout << "ba" << endl;
        }
        if (i<rc){
            recuento_bc+=a[i];
            //cout << "bc" << endl;
        }
    }
    if (i>lc){
        if (i<ra){
            recuento_ca+=b[i];
            //cout << "ca" << endl;
        }
        if (i<rb){
            recuento_cb+=a[i];
            //cout << "cb" << endl;
        }
    }
  }
  //cout << la << " " << ra << " " << lb << " " << rb << " " << lc << " " << rc << endl;
  //cout << recuento_ab << " " << recuento_ac << " " << recuento_ba << " " << recuento_bc << " " << recuento_ca << " " << recuento_cb << endl;

  if (recuento_ab >= tot){
    cout << 1 << " " << la+1 << " " << rb+1 << " " << n << " " << la+2 << " " << rb << endl;
  } else if (recuento_ac >= tot){
    cout << 1 << " " << la+1 << " " << la+2 << " " << rc << " " << rc+1 << " " << n << endl;
  } else if (recuento_ba >= tot){
    cout << ra+1 << " " << n << " " << 1 << " " << lb+1 << " " << lb+2 << " " << ra << endl;
  } else if (recuento_bc >= tot){
    cout << lb+2 << " " << rc << " " << 1 << " " << lb+1 << " " << rc+1 << " " << n << endl;
  } else if (recuento_ca >= tot){
    cout << ra+1 << " " << n << " " << lc+2 << " " << ra << " " << 1 << " " << lc+1 << endl;
  } else if (recuento_cb >= tot){
    cout << lc+2 << " " << rb << " " << rb+1 << " " << n << " " << 1 << " " << lc+1 << endl;
  } else {
    cout << -1 << endl;
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
