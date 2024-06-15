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
  cin >> T;
  while (T--) {
    int n, x, changes = -1, el, min, max;
    cin >> n >> x;
    max = -x - 1;
    for (int i = 0; i < n; i++) {
      cin >> el;
      for (int j = min; j <= max; j++) {
        if (j + x < el) {
          min++;
        }
        if (j- x > el){
          max = j-x-1;
          break;
        }
      }
      cout << min << " " << max << " " << el << endl;
      if (max + x < el || min - x > el) {
        cout << "yes" << endl;
        changes++;
        min = el - x;
        max = el + x;
      }
    }
    cout << changes << endl;
  }

  return 0;
}