#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int m, k, d, t;
  cin >> t;
  for (int jesus=0; jesus<t;jesus++){
    cin >> m;
    k=log10(m);
    d=m-pow(10,k);
    cout << d << "\n";
  }
  return 0;
}