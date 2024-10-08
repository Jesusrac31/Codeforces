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
typedef vector<unsigned long long int> vll;
typedef unsigned long long int lli;
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

//vll factoriales = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200, 1307674368000, 20922789888000, 355687428096000, 6402373705728000, 121645100408832000, 2432902008176640000, 14197454024290336768, 17196083355034583040, 8128291617894825984, 10611558092380307456, 7034535277573963776, 16877220553537093632, 12963097176472289280, 12478583540742619136, 11390785281054474240, 9682165104862298112, 4999213071378415616, 12400865694432886784, 3400198294675128320, 4926277576697053184, 6399018521010896896, 9003737871877668864, 1096907932701818880, 4789013295250014208, 2304077777655037952, 18376134811363311616, 15551764317513711616, 7538058755741581312, 10541877243825618944, 2673996885588443136, 9649395409222631424, 1150331055211806720, 17172071447535812608, 12602690238498734080, 8789267254022766592, 15188249005818642432, 18284192274659147776, 9994050523088551936, 13175843659825807360, 10519282829630636032, 6711489344688881664, 6908521828386340864, 6404118670120845312, 2504001392817995776, 162129586585337856, 9727775195120271360, 3098476543630901248};
vll potencias = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488};

int solve() {
  // Code aquí
  long long int n, k;
  lli sol = 0;
  vi bits;
  cin >> n >> k;
  cout << n << endl;
  while(n!=0){
    bits.PB(n%2);
    n/=2;
  }
  cout << bits.size() << endl;
  //Imprime(bits);
  for (int i = bits.size()-1; i>=0; i--){
    //cout << sol << " ";
    if (bits[i] == 0){
      continue;
    }
    if (i<=k){
      //Terminado, el resto de combinaciones forman un subarray
      lli ultimo = 0;
      for (int j = 0; j<=i; j++){
        ultimo += potencias[j]*bits[j];
      }
      cout << sol << " " << ultimo << " finish ";
      sol+=(((ultimo%1000000007)*((ultimo+1)%1000000007))%1000000007)/2;
      sol = sol%1000000007;
      break;
    } else if (i == k+1){
      cout << "+1 ";
      sol += (potencias[i]-1)*potencias[i]/2;
      sol = sol%1000000007;
    } else {
      lli sumando = 1;
      for (int j = 0; j<=k+1; j++){
        cout  << ((sumando%(lli)1000000007)*(((potencias[k-j]%(lli)1000000007)*((potencias[k+1-j]-1)%(lli)1000000007))%(lli)1000000007))%(lli)1000000007 << " ";
        //sol+=(factoriales[i-k-2+j]*potencias[k+1-j]*(potencias[k+1-j]-1))/(2*factoriales[j]*factoriales[i-k-2]);
        sol += ((sumando%(lli)1000000007)*(((potencias[k-j]%(lli)1000000007)*((potencias[k+1-j]-1)%(lli)1000000007))%(lli)1000000007))%(lli)1000000007;
        //sol += ((((((factoriales[i-k-2+j]%1000000007)*(potencias[k+1-j]%1000000007))%1000000007)*((potencias[k+1-j]-1)%1000000007))%1000000007)/(2*((factoriales[j]%1000000007)*(factoriales[i-k-2]%1000000007))%1000000007))%1000000007;
        sol = sol%1000000007;
        sumando = sumando * (i-k-1+j);
        sumando = sumando/(j+1);
      }
      cout << " reduced ";
    }
    k--;
  }
  cout << endl << "sol: " << sol << endl;

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