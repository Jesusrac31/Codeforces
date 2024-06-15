#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void Imprime(vector<int> vect){
  for (int i=0; i<vect.size(); i++){
    cout << vect[i]<<" ";
  }
  cout << endl;
}

int main() {
  string b;

  vector<int> vect;
  int T;
  int n;
  int m;
  int el;
  cin >> T;
  for (int i=0; i<T; i++){
    vect = {};
    b = "";
    
    cin >> n >> m;
    m=m-1;
    for (int j = 0; j<n; j++){
      cin >> el;
      el = el-1;
      if (el > m-el){
        el = m-el;
      }
      
      vect.push_back(el);
    }
    for (int j = 0; j<=m; j++){
      b = b+"B";
    }
    for (int j=0; j<n;j++){
      if (b[vect[j]] == 'B'){
        b[vect[j]] = 'A';
      }
      else{
        b[m-vect[j]] = 'A';
      }
    }
    cout << b << "\n";
  }

  return 0;
}