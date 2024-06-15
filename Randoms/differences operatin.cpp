#include <iostream>
#include <vector>
using namespace std;

void Imprime(vector<int> vect){
  for (int i=0; i<vect.size(); i++){
    cout << vect[i]<<" ";
  }
  cout << endl;
}

bool ordena(vector<int> vect){
  bool bien;
  bool pasar;
  for (int i=1; i<vect.size(); i++){
    pasar = true;
    vect[i] = vect[i]-vect[i-1];
    for (int j=1; j<vect.size(); j++){
      if (vect[j]<0){
        pasar = false;
      }
    }
    if (vect[i-1]==0){
      pasar = false; 
    }
    if (pasar){
      if (i==1){
        bien = true;
        for (int j=vect.size(); j>0; j--){
          if (vect[j]>0){
            bien = false;
          }
        }
        if (bien){
          return(true);
        }
      }
      bien=ordena(vect);
      if (bien){
        return(true);
      }
    }
    vect[i] = vect[i]+vect[i-1];
  }
  return(false);
}

int main() {
  bool posible;
  int el;
  vector<int> vect;
  int T;
  int n;
  cin >> T;
  for (int i = 0; i<T; i++){
    cin >> n;
    vect = {};
    for (int j=0; j<n; j++){
      cin >> el;
      vect.push_back(el);
    }
    posible = ordena(vect);
    if (posible){
      cout << "YES" << endl;
    }
    else{
      cout << "NO" << endl;
    }
  }
  
  return (0);
}