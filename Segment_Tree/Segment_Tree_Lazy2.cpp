#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e9;

class SegmentTree{
    private :
        ll size;
        vector<ll> T;
        vector<ll> L;
    public:
        SegmentTree(ll n){
            size = n;
            T.resize(4*n);
            L.resize(4*n, 0);
        }

        void push(int node){
            T[2*node] += L[node];
            L[2*node] += L[node];
            T[2*node + 1] += L[node];
            L[2*node + 1] += L[node];
            L[node] = 0;
        }
        void build(vector<ll> &a, ll lx, ll rx, ll node){
            if(lx == rx){
                T[node] = a[lx];
            }
            else{
                ll mx = (lx + rx)/2;
                build(a, lx, mx, 2*node);
                build(a, mx+1, rx, 2*node + 1);
                T[node] = max(T[2*node], T[2*node + 1]);
            }
        }

        ll get(ll node, ll lx, ll rx, ll l, ll r){
            if(l > r){
                return 0;
            }
            if(lx == l && rx == r){
                return T[node];
            }
            push(node);
            ll mx = (lx + rx)/2;
            return max(get(2*node, lx, mx, l, min(r, mx)), get(2*node + 1, mx + 1, rx, max(l, mx+1), r));
        }

        void update(ll node, ll lx, ll rx, ll l, ll r, ll add_value){
            if(l > r){
                return;
            }
            if(lx == l && rx == r){
                T[node] += add_value;
                L[node] += add_value;
            }
            else{
                push(node);
                ll mx = (lx + rx)/2;
                update(2*node, lx, mx, l, min(r, mx), add_value);
                update(2*node + 1, mx + 1, rx, max(mx+1, l), r, add_value);
                T[node] = max(T[2*node], T[2*node + 1]);
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
            ll l, r, add;
            cin>>l>>r>>add;
            l--; r--;
            ST.update(1, 0, n-1, l, r, add);
        }
        else if(cmd == 2){
            ll l, r;
            cin>>l>>r; l--; r--;
            cout<<ST.get(1, 0, n-1, l, r)<<endl;
        }
    }
    
}