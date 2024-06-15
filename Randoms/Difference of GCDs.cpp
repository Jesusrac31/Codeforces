#include <iostream>
#include <vector>
using namespace std;

void Imprime(vector<long long int> vect){
  for (int i=0; i<vect.size(); i++){
    cout << vect[i]<<" ";
  }
  cout << endl;
}

int main() {
  long long int l;
  long long int r;
  long long int n;
  vector<long long int> a;

  bool posible;
  
  int T;
  cin >> T;
  for (int i=0; i<T; i++){
    a = {};
    posible = true;
    cin >> n >> l >> r;
    for (int j = 0; j<n; j++){
      a.push_back(r-(r%(j+1)));
      if (a[j] < l){
        posible = false;
        break;
      }
    }
    if (posible){
      cout << "YES" << endl;
      Imprime(a);
    }
    else{
      cout << "NO" << endl;
    }
  }
  return(0);
}