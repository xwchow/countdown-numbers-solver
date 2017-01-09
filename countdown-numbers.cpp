#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, target;
vector<int> arr;

string concat(string &a, string &b, char op){
    return "(" + a + " " + string(1, op) + " " + b + ")";
}

map<ll, string> all_values(int L, int R){
    map<ll, string> mp;
    if (L == R) {
        mp[arr[L]] = to_string(arr[L]);
        return mp;
    }

    for (int mid = L; mid < R; mid++){
        auto mpA = all_values(L, mid);
        auto mpB = all_values(mid + 1, R);
        for (auto &x : mpA){
            for (auto &y : mpB){
                mp[x.first + y.first] = concat(x.second, y.second, '+');
                mp[x.first - y.first] = concat(x.second, y.second, '-');
                mp[x.first * y.first] = concat(x.second, y.second, '*');
                if (y.first && x.first % y.first == 0)
                    mp[x.first / y.first] = concat(x.second, y.second, '/');
            }
        }
    }
    return mp;
}

bool read_input(){
    cin >> n;
    if (!n) return false;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    cin >> target;
    return true;
}

void solve(){
    sort(arr.begin(), arr.end());
    do {
        auto mp = all_values(0, n-1);
        if (mp.count(target)){
            cout << mp[target] << endl;
            return;
        }
    } while (next_permutation(arr.begin(), arr.end()));
    cout << "NO POSSIBLE WAY" << endl;
}

int main(){
    while (read_input()){
        solve();
    };


    return 0;
}
