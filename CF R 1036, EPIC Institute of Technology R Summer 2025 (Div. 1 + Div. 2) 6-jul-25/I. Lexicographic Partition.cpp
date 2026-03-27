#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vt vector

vt<int> solve(const vt<int>& b, vt<vt<int>>& inv) {
    int n = b.size();
    if (inv[1].size() > 1) return {};

    vt<int> a(n);
    stack<array<int,5>> s;
    if (inv[2].size() > 1) {
        a[0] = 1;
        s.push({0, n-1, 2, n, 1});
    } else {
        a[0] = n;
        s.push({0, n-1, 1, n-1, 1});
    }

    while (!s.empty()) {
        auto tp = s.top(); 
        s.pop();
        int l = tp[0], r = tp[1], leftNum = tp[2], rightNum = tp[3], ok = tp[4];
        if (l == r) continue;
        if(b[l+1]!=b[l]+1) return {};
        int num = b[l] + 1;
        if (num >= inv.size()) return {};

        vt<int> nxt;
        while (inv[num].size() && inv[num].back() > l) {
            nxt.push_back(inv[num].back());
            inv[num].pop_back();
        }
        if (nxt.size()==0) return {};  
        if(!ok && nxt.size()!=1) return {};
        if (nxt.size() == 1) {
            if (num+1 < inv.size() && inv[num+1].size() > 1 && inv[num+1][inv[num+1].size()-2] > l) {
                a[nxt[0]] = leftNum++;
            } else {
                a[nxt[0]] = rightNum--;
            }
            s.push({l+1, r, leftNum, rightNum, 1});
        } else {
            rightNum -= nxt.size();
            int nx = rightNum + 1;
            reverse(nxt.begin(), nxt.end());
            int curLeft = leftNum;
            for (int i = 0; i < (int)nxt.size(); ++i) {
                int pos = nxt[i];
                a[pos] = nx++;
                int nextInd = (i+1 < (int)nxt.size() ? nxt[i+1] - 1 : r);
                int sz = nextInd - pos - 1;
                s.push({pos, nextInd, curLeft, curLeft + sz, 0});
                curLeft += sz + 1;
            }
        }
    }

    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vt<int> x(n);
        for (int i = 0; i < n; ++i) cin >> x[i];

        vt<vt<int>> inv(n+3);
        for (int i = 0; i < n; ++i) inv[x[i]].push_back(i);

        auto a = solve(x, inv);
        if (a.empty()) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (int v : a) cout << v << ' ';
            cout << "\n";
        }
    }
    return 0;
}
// https://codeforces.com/contest/2124/problem/I
