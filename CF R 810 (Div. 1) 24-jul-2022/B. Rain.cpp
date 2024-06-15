#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void Imprime(vector<int> vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i] << " ";
  }
  cout << endl;
}

int main() {
  int T;
  int n;
  int m;
  vector<int> x;
  vector<int> p;
  vector<int> dias;
  int field;
  int maxi;
  int el;
  string sol;

  cin >> T;
  while (T != 0) {
    T--;
    cin >> n >> m;
    maxi = -1;
    p = {};
    x = {};
    sol = "";
    dias = {};
    for (int i = 0; i < n; i++) {
      cin >> el;
      x.push_back(el - 1);
      if (el > maxi) {
        maxi = el;
      }
      cin >> el;
      p.push_back(el);
      sol += "1";
      dias.push_back(i);
    }
    for (int k = 0; k < maxi; k++) {
      field = 0;
      for (int i = 0; i < n; i++) {
        field = field + max(0, p[i] - abs(x[i] - k));
      }
      if (field > m) {
        for (int i = 0; i < dias.size(); i++) {
          field = field - max(0, p[dias[i]] - abs(x[dias[i]] - k));
          if (field > m) {
            sol[dias[i]] = '0';
            field = field + max(0, p[dias[i]] - abs(x[dias[i]] - k));
            dias.erase(dias.begin()+i);
            i--;
          }
          else{
            field = field + max(0, p[dias[i]] - abs(x[dias[i]] - k));
          }
        }
        if (dias.empty()){
          break;
        }
      }
    }
    cout << sol << "\n";
  }
  return 0;
}