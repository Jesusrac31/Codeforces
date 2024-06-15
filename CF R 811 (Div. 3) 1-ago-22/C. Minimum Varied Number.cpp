#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--){
    int s;
    int num=0, suma = 0;
    cin >> s;
    if (s<10){
      cout << s << endl;
    }
    else{
      for (int i = 9; i>0; i--){
        num += i*pow(10,abs(i-9));
        suma +=i;
        if (suma+i>s){
          cout << s-suma << num << endl;
          break;
        }
      }
    }
  }

  return 0;
}