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
    int n, m, el, c;
    string num_1, num_2;
    bool posible=true, posible2=false;
    vector<int> a, b;
    cin >> n >> m;
    cin >> num_1;
    for (int i = 0; i < n; i++) {
      el=num_1[i] - '0';
      if (i + m > n) {
        b.push_back(el);
      } else {
        a.push_back(el);
      }
    }
    cin >> num_2;
    for (int i = 0; i < m; i++) {
      el=num_2[i] - '0';
      if (i == 0){
        c=el;
      }
      else{
        if (b[i-1]!=el){
          posible=false;
        }
      }
    }
    if (posible){
      for (int i=0; i<a.size(); i++){
        if (a[i]==c){
          cout << "YES" << endl;
          posible2=true;
          break;
        }
      }
      if (!posible2){
        cout << "NO" << endl;
      }
    }
    else{
      cout << "NO" << endl;
    }
  }
  return 0;
}