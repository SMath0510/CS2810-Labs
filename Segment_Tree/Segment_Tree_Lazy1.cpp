#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

class SegmentTree{
    private :
        ll size;
        vector<ll> T;
        vector<bool> marked;
    public:
        SegmentTree(ll n){
            size = n;
            T.resize(4*n);
            marked.resize(4*n, false);
        }

        void push(int node){
            if(marked[node]){
                T[2*node] = T[2*node + 1] = T[node];
                T[node] = 0;
                marked[node] = false;
                marked[2*node] = marked[2*node + 1] = true;
            }
        }
        void build(vector<ll> &a, ll lx, ll rx, ll node){
            if(lx == rx){
                T[node] = a[lx];
            }
            else{
                ll mx = (lx + rx)/2;
                build(a, lx, mx, 2*node);
                build(a, mx+1, rx, 2*node + 1);
                T[node] = 0;
            }
        }

        ll get(ll node, ll lx, ll rx, ll idx){
            if(lx == rx){
                return T[node];
            }
            push(node);
            ll mx = (lx + rx)/2;
            if(idx <= mx){
                return get(2*node, lx, mx, idx);
            }
            return get(2*node + 1, mx + 1, rx, idx);
        }

        void update(ll node, ll lx, ll rx, ll l, ll r, ll new_value){
            if(l > r){
                return;
            }
            if(lx == l && rx == r){
                T[node] = new_value;
                marked[node] = true;
            }
            else{
                push(node);
                ll mx = (lx + rx)/2;
                update(2*node, lx, mx, l, min(r, mx), new_value);
                update(2*node + 1, mx + 1, rx, max(mx+1, l), r, new_value);
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
            ll k;
            cin>>k; k--;
            cout<<ST.get(1, 0, n-1, k)<<endl;
        }
    }
    
}