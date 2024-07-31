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

void Imprime(vector<pair<int, set<int>>> vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i].first << " --> [";
    copy(vect[i].second.begin(), vect[i].second.end(), ostream_iterator<int>(cout, ", "));
    cout << "]\n";
  }
  cout << "\n";
}

void Imprime_letras (vector<pair<int, vi>> vect){
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i].first << " --> [";
    for (int j = 0; j<vect[i].second.size(); j++){
        cout << vect[i].second[j] << ", ";
    }
    cout << "]\n";
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

// Necesitaremos también un traductor de letras a números a partir de una función
// A --> 0
// Z --> 25
int CharToInt(char a){
    int num = a - '0';
    return (num-17);
}

vector<pair<int, vi>> Init_letras(char x, int k){
    vector<pair<int, vi>> letras;
    pair<int, vi> par_letras;
    par_letras.first = 0;
    par_letras.second = {};
    for (int i = 0; i<18; i++){
      letras.PB(par_letras);
    } 
    letras[CharToInt(x)].first = k;
    letras[CharToInt(x)].second.PB(0);

    return letras;
}

vector<pair<int, set<int>>> Init_contadores(char x, int k){
    vector<pair<int, set<int>>> contadores;
    pair<int, set<int>> par_contadores;

    par_contadores.first = k;
    par_contadores.second = {CharToInt(x)};

    contadores.PB(par_contadores);

    return contadores;
}

int Limit (int x, int limit){
    if (x>limit){
        x = limit;
    }
    return x;
}

bool Debugging = false;

int solve() {
  // Code aquí
  if (Debugging){
    cout << "----------------START----------------" << endl;
  }
  int n, c, k;
  cin >> n >> c >> k;
  string word;
  cin >> word;

  if (Debugging){
    cout << k << endl;
    cout << word << endl;
  }

  // Para este algoritmo necesitaremos recorrer todas las posibles cadenas a la vez almacenando en una lista las que tienen cada letra.
  vector<pair<int, vi>> letras = Init_letras(word[word.size()-1], k);
  // Necesitamos una lista para los contadores desde la que se haga referencia a la anterior
  vector<pair<int, set<int>>> contadores = Init_contadores(word[word.size()-1], k);

  // Durante el recorrido 
  int turno = 1;
  for (int i = n-2; i>=0; i--){
    if (Debugging){
        cout << "\nTurno: " << turno << endl;
    }
    // Reseteamos contador de la letra y todos sus adyascentes
    letras[CharToInt(word[i])].first = turno + k;
    for (int j = 0; j<letras[CharToInt(word[i])].second.size(); j++){
        contadores[letras[CharToInt(word[i])].second[j]].first = turno+k;
    }

    // Comprobamos si alguna letra acaba de elminarse para comprobar si las listas con dicha letra necesitan reemplazo
    int index_letra_eliminada = CharToInt(word[Limit(i+k, n-1)]);

    if (Debugging){
        cout << "Letra inspeccion: " <<  word[Limit(i+k, n-1)] << endl;
        cout << "Contador letra eliminada: " << letras[index_letra_eliminada].first << endl;
    }

    if (letras[index_letra_eliminada].first == turno) {
        if (Debugging){
            cout << "ALARM!!!\nCantidad de listas: " << letras[index_letra_eliminada].second.size() << endl;
        }
        for (int j = 0; j<letras[index_letra_eliminada].second.size(); j++){
            if (Debugging){
                cout << "Contador lista " << j << ": " << contadores[letras[index_letra_eliminada].second[j]].first << endl;
            }
            if (contadores[letras[index_letra_eliminada].second[j]].first == turno){
                //Inicia proceso de añadir nuevos elementos
                if (Debugging){
                    cout << endl << "Reemplazando..." << endl << endl;
                }
                bool primero = true;
                pair<int, set<int>> copia;
                for (int a = 0; a<letras.size(); a++){
                    if (letras[a].first > turno){
                        if (Debugging){
                            cout << "Index_letra: " << a << endl;
                        }

                        if (primero){
                            copia = contadores[letras[index_letra_eliminada].second[j]];
                            contadores[letras[index_letra_eliminada].second[j]].second.insert(a);

                            letras[a].second.PB(letras[index_letra_eliminada].second[j]);

                            contadores[letras[index_letra_eliminada].second[j]].first = letras[a].first;
                            primero = false;
                        } else {
                            contadores.PB(copia);
                            contadores[contadores.size()-1].second.insert(a);

                            for (auto b = contadores[contadores.size()-1].second.begin(); b!=contadores[contadores.size()-1].second.end(); b++){
                                letras[*b].second.PB(contadores.size()-1);
                            }

                            contadores[contadores.size()-1].first = letras[a].first;
                        }
                    }
                }
                if (Debugging){
                    cout << "\nContadores:\n";
                    Imprime(contadores);
                    cout << "\nLetras:\n";
                    Imprime_letras(letras);
                }
            }
        }
    }
    turno++;
  }

  // Ahora tenemos en la lista de contadores los posibles caminos que podemos hacer y el tamaño de la lista de enlaces a letras es el tamaño, debemos buscar el más chico.
  int minimo = 20; // Número mayor a 18
  if (Debugging){
    cout << "Listas: " << contadores.size() << endl;
  }
  for (int i = 0; i<contadores.size(); i++){
    if (minimo > contadores[i].second.size()){
        minimo = contadores[i].second.size();
    }
  }
  cout << minimo << endl;

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