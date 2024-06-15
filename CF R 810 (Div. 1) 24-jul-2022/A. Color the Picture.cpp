#include <algorithm>
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
  int k_num;
  int suma;
  int el;
  vector<int> k;
  bool posible;

  cin >> T;
  for (int p = 0; p < T; p++) {
    k = {};
    suma = 0;
    posible = false;
    cin >> n >> m >> k_num;
    for (int i = 0; i < k_num; i++) {
      cin >> el;
      k.push_back(el);
    }
    sort(k.begin(), k.end());
    for (int i = 0; i < k.size(); i++) {
      if (k[i] / m >= 2) {
        suma = suma + k[i] / m;
      }
      if (suma > n) {
        if (k[i] / m > 2) {
          suma = n;
        } else {
          suma = suma - 2;
        }
      }
      if (suma == n) {
        posible = true;
        break;
      }
    }
    suma = 0;
    for (int i = 0; i < k.size(); i++) {
      if (k[i] / n >= 2) {
        suma = suma + k[i] / n;
      }
      if (suma > m) {
        if (k[i] / n > 2) {
          suma = m;
        } else {
          suma = suma - 2;
        }
      }
      if (suma == m) {
        posible = true;
        break;
      }
    }
    if (posible) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }
  return 0;
}