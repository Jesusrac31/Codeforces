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

int factorial(int n) {
  int sol = 1;
  for (int i = 1; i <= n; i++) {
    sol = sol * i;
  }
  return sol;
}
int zerostoone(int n) {
  if (n == 0) {
    return 1;
  }
  return n;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, el, one_zero_1 = -1, one_zero_2 = -1, min_1 = -1, min_1pos,
               min_2 = -1, min_2pos, fijos = 0, sum = 2;
    vector<int> a;
    vector<int> intervalo;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> el;
      a.push_back(el);
      if (one_zero_1 == -1) {
        if (el == 1 || el == 0) {
          one_zero_1 = i;
        } else if (min_1 > el || min_1 == -1) {
          min_1 = el;
          min_1pos = i;
        }
      } else if (one_zero_2 != -1) {
        if (min_2 > el || min_2 == -1) {
          min_2 = el;
          min_2pos = i;
        }
      } else {
        if (el == 1 || el == 0) {
          one_zero_2 = i;
        } else {
          intervalo.push_back(el);
        }
      }
    }
    if (min_1 == -1) {
      min_1pos = -1;
    }
    if (min_2 == -1) {
      min_2pos = n;
    }
    sort(intervalo.begin(), intervalo.end());
    for (int i = 0; i < intervalo.size(); i++) {
      if (intervalo[i] == i + sum) {
        fijos++;
      } else {
        break;
      }
    }
    if (fijos == 0) {
      cout << factorial((one_zero_1 - min_1pos - 1) +
                        (min_2pos - one_zero_2 - 1) +
                        (intervalo.size() - fijos))
           << "\n";
      ;

    } else {
      cout << factorial(intervalo.size()) *
                  zerostoone((one_zero_1 - min_1pos - 1) +
                             (min_2pos - one_zero_2 - 1) +
                             (intervalo.size() - fijos))
           << "\n";
    }
    if (T==10000-157){
      Imprime(a);
    }
  }
  return 0;
}