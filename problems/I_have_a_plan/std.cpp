#include <bits/stdc++.h>
using namespace std;
const int MAX = 200009;
struct fenwick{
    int n;
    vector <long long> tree;
    fenwick(int n){
        this -> n = n;
        tree.assign(n + 1,0);
    }
    long long lowbit(long long x){
        return x & (-x);
    }
    void insert(long long pos,long long x){
        while(pos <= n){
            tree[pos] += x;
            pos += lowbit(pos);
        }
    }
    long long presum(long long pos){
        long long ans = 0;
        while(pos > 0){
            ans += tree[pos];
            pos -= lowbit(pos);
        }
        return ans;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector <long long> a(n + 1),b (n + 1),c(m + 1);
    for(int i = 1;i <= n;i++){
        cin >> a[i] >> b[i];
    }
    for(int i = 1;i <= m;i++){
        cin >> c[i];
    }
    long long S = 0;
    for(int j = 1;j <= m;j++){
        S += c[j];
    }
    set<long long> nums;
    for(int i = 1;i <= n;i++){
       // nums.insert(a[i]);
        nums.insert(a[i] + b[i] * S);
    }
    map<long long,long long> T;
    int tot = 1;
    for(long long val:nums){
        T[val] = tot;
        tot++;
    }
    vector <long long> ans(n + 1);
    vector <pair<long long,long long>> P(n + 1);
    for(int i = 1;i <= n;i++){
        P[i].first = a[i];
        P[i].second = i;
    }
    sort(P.begin() + 1,P.end());
    fenwick F(n);
    for(int l = 1,r = 1;l <= n && r <= n;){
        while(r <= n){
            if(P[r].first == P[l].first){
                r++;
            }
            else{
                break;
            }
        }
        r--;
        for(int i = l;i <= r;i++){
            long long R = P[i].first + b[P[i].second] * S;
            F.insert(T[R],1);
        }
        for(int i = l;i <= r;i++){
            long long R = P[i].first + b[P[i].second] * S;
            ans[P[i].second] = F.presum(T[R]) - 1;
        }
        l = r + 1;
        r = l;
    }
    for(int i = 1;i <= n;i++){
        cout << ans[i] << '\n';
    }

}