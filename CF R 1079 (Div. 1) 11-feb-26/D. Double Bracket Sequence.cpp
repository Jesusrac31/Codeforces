#include<bits/stdc++.h>
using namespace std;
 
#define int long long

template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";//Quita esto si no quieres los corchetes o cambia lo que quieras poner
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
 
const int INF = 1'000'000'007;
 
void solve(){
	int n;
	cin >> n;
	string s;
	cin >> s;
 
	vector<int> stay(n);
 
	auto delete_cbs = [&](char open, char close){
		vector<int> st;
		for (int i = 0; i < n; i++){
			if (s[i] == close){
				if (!st.empty() && s[st.back()] == open){
					st.pop_back();
				}
				else{
					st.push_back(i);
				}
			}
			else if (s[i] == open){
				st.push_back(i);
			}
		}
		for (int x : st){
			stay[x] = 1;
		}
	};
    #ifdef FELIX
        cout << s << endl;
    #endif
    
    // Pone stay[i] a 1 si el caracter i está ya balanceado
	delete_cbs('(', ')');
	delete_cbs('[', ']');

    #ifdef FELIX
        cout << "Transform delete_cbs: " << endl;
        cout << s << endl;
        cout << stay << endl;
    #endif
 
	int last_open = 0;
	int cnt_open = 0, cnt_close = 0;
	int ans = 1;
 
	for (int i = 0; i < n; i++){
		if (!stay[i]){
			continue;
		}
		if (s[i] == '(' || s[i] == '['){
			cnt_open++;
			last_open = 1;
		}
		else{
			cnt_close++;
			if (last_open){
				ans = 0;
			}
			last_open = 0;
		}
	}
	if (cnt_open % 2 == 0 || cnt_close % 2 == 0){
		ans = 0;
	}
	ans += (cnt_open + cnt_close) / 2;
	cout << ans << '\n';
}
 
signed main() {
#ifdef FELIX
	auto _clock_start = chrono::high_resolution_clock::now();
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
 
	int t = 1;
	cin >> t;
	for (int i = 1; i<=t; i++){
        #ifdef FELIX
            cout << "Test: " << i << endl;
        #endif
		solve();
        #ifdef FELIX
            cout << "------------------" << endl;
        #endif
	}
 
#ifdef FELIX
	cout << "Executed in " << chrono::duration_cast<chrono::milliseconds>(
		chrono::high_resolution_clock::now()
			- _clock_start).count() << "ms." << endl;
#endif
	return 0;
}