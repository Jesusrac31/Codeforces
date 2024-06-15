#include <iostream>
#include <vector>
using namespace std;

void Imprime(vector<vector<int>> vect){
  for (int j = 0; j<vect.size(); j++){
    for (int i=0; i<vect[j].size(); i++){
      cout << vect[j][i]<<" ";
    }
    cout << endl;
  }
}

int main() {
  bool posible=true;
  int l;
  int r;
  int el;
  vector<int> vect;
  vector<vector<int>> arbol;
  vector<int> element;
  bool fin_arbol;
  int num = 0;
  int q;
  int n;
  cin >> n >> q;
  for (int j=0; j<n; j++){
    cin >> el;
    vect.push_back(el);
  }
  //Buscamos posición de 1 y de n;
  int pos_1 = -1;
  int pos_2 = -1;
  for (int i = 0; i<n; i++){
    if (vect[i]==1){
      pos_1 = i;
    }
    else if (vect[i] == n){
      pos_2 = i;
    }
  }
  if (min(pos_1,pos_2)==-1){
    posible = false;
  }

element.push_back(pos_1);
element.push_back(pos_2);
arbol.push_back(element);
  
  while (true){
    element = {};
    fin_arbol=false;
    for (int i = 0; i<n; i++){
      if (vect[i]==pos_1){
        pos_1 = i;
      }
      else if (vect[i] == pos_2){
        pos_2 = i;
      }
    }
    for (int i = 0; i<arbol.size(); i++){
      if (arbol[i][0] == pos_1 && arbol[i][1] == pos_2){
        fin_arbol=true;
        break;
      }
    }
    if (fin_arbol){
      break;
    }
    element.push_back(pos_1);
    element.push_back(pos_2);
    arbol.push_back(element);
  }
  Imprime(arbol);
  
  for (int i = 0; i<q; i++){
    cin >> l >> r;

    if (posible){
      posible = false;
      for (int j = 0; j<arbol.size(); j++){
        if (arbol[j][0] == pos_1 && arbol[j][1] == pos_2){
          posible=true;
          num = j;
          break;
        }
      }    
    }
    
    if (posible){
      cout << num << endl;
    }
    else{
      cout << -1 << endl;
    }
  }
  return 0;
}