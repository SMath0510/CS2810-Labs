#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

class SegmentTree{
    private :
        ll size;
        vector<ll> T;
    
    public:
        SegmentTree(ll n){
            size = n;
            T.resize(4*n);
        }

        void build(vector<ll> &a, ll lx, ll rx, ll node){
            if(lx == rx){
                T[node] = a[lx];
            }
            else{
                ll mx = (lx + rx)/2;
                build(a, lx, mx, 2*node);
                build(a, mx+1, rx, 2*node + 1);
                T[node] = T[2*node] + T[2*node + 1];
            }
        }

        ll sum(ll node, ll lx, ll rx, ll l, ll r){
            if(l > r){
                return 0;
            }
            if(lx == l && rx == r){
                return T[node];
            }
            ll mx = (lx + rx)/2;
            return sum(2*node, lx, mx, l, min(r, mx)) + sum(2*node + 1, mx + 1, rx, max(l, mx+1), r);
        }

        void update(ll node, ll lx, ll rx, ll idx, ll new_val){
            if(lx == rx){
                T[node] = new_val;
            }
            else{
                ll mx = (lx + rx)/2;
                if(idx <= mx){
                    update(2*node, lx, mx, idx, new_val);
                }
                else{
                    update(2*node + 1, mx + 1, rx, idx, new_val);
                }
                T[node] = T[2*node] + T[2*node + 1];
            }
        }
};

int main(){
    ll n, q;
    cin>>n>>q;
    vector<ll> a(n);
    for(ll i = 0; i<n; i++) cin>>a[i];
    SegmentTree ST(n);
    ST.build(a, 0, n-1, 1);
    while (q--) {
        ll cmd;
        cin>>cmd;
        if(cmd == 1){
            ll idx, new_val;
            cin>>idx>>new_val; idx--;
            ST.update(1, 0, n-1, idx, new_val);
        }
        else if(cmd == 2){
            ll l, r;
            cin>>l>>r; l--; r--;
            cout<<ST.sum(1, 0, n-1, l, r)<<endl;
        }
    }
    
}