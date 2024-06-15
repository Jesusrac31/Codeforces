#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
  int q;
  cin >> q; 
  while (q--){
    int n, el;
    bool zeros, fin=false;
    string sol="YES";
    cin >> n;
    vector<int> a;
    for (int i = 0; i<n; i++){
      cin >> el;
      if (i==0){
        zeros = el%10 == 0 || el%10 == 5;
      }
      a.push_back(el);
      if ((el%10 == 0 || el%10 == 5)&& zeros){
        if (el%10 == 5){
          a[i] +=5;
        }
        zeros = true;
      }
      else if (!zeros){
        zeros=false;
        if ((a[i]%10)%2==1){
          a[i]+=a[i]%10;
        }
      }
      else{
        sol = "NO";
        fin = true;
      }
    }
    if (!fin){
      int coef = -1;
      if (zeros){
        for (int i = 0; i<a.size(); i++){
          if (coef!=a[i]){
            if (coef == -1){
              coef = a[i];
            }
            else{
              sol = "NO";
              break;
            }
          }
        }
      }
      else{
        if ((a[0]/10)%2==1){
          if (a[0]%10==6){
            coef = 1;
          }
          else{
            coef = 0;
          }
        }
        else{
          if (a[0]%10==6){
            coef = 0;
          }
          else{
            coef = 1;
          }
        }
        for (int i = 0; i<a.size(); i++){
          if ((a[i]/10)%2==1){
            if (a[i]%10==6){
              if (coef == 0){
                sol = "NO";
                break;
              }
            }
            else{
              if (coef == 1){
                sol = "NO";
                break;
              }
            }
          }
          else{
            if (a[i]%10==6){
              if (coef == 1){
                sol = "NO";
                break;
              }
            }
            else{
              if (coef == 0){
                sol = "NO";
                break;
              }
            }
          }
        }
      }
    }
    cout << sol << endl;
  }

  return 0;
}