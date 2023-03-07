#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

class SegmentTree{
    private:
    ll size;
    vector<ll> ST;
    vector<ll> Store;
    vector<ll> input;
    public:
    SegmentTree(ll size, vector<ll> &inp){
        size = size;
        input = inp;
        // cout<<input.size()<<endl;
        ST.resize(4*size);
        Store.resize(4*size, 0);
    }
    void build(ll l, ll r, ll idx){
        // cout<<l<<" "<<r<<" "<<idx<<endl;
        if(r - l == 1){
            // cout<<"In"<<endl;
            ST[idx] = input[l];
            return;
        }
        ll mid = (l+r)/2;
        build(l, mid, 2*idx);
        build(mid, r, 2*idx +1);
        ST[idx] = ST[2*idx]+ST[2*idx+1];
    }
    ll get(ll l, ll r, ll lx, ll rx, ll idx){
        // cout<<l<<" "<<lx<<" "<<r<<" "<<rx<<endl;
        if(lx > r || rx < l){
            return 0;
        }
        if(rx - lx == 0){
            return 0;
        }
        if(l <= lx && r >= rx){
            if(rx - lx == 1){
                ST[idx] += (Store[idx]);
                Store[idx] = 0;
                return ST[idx];
            }
            ST[idx] += Store[idx]*(rx-lx);
            Store[2*idx] += Store[idx];
            Store[2*idx + 1] += Store[idx];
            Store[idx] = 0;
            return ST[idx];
        }
        if(rx - lx == 1){
            ST[idx] += (Store[idx]);
            Store[idx] = 0;
            return 0;
        }
        ll mid = (lx+rx)/2;
        ll left = get(l, r, lx, mid, 2*idx);
        ll right = get(l, r, mid, rx, 2*idx+1);
        return left+right;
    }
    void print(){
        for(int i = 0; i<ST.size(); i++){
            cout<<ST[i]<<" ";
        }
        cout<<endl;
        for(int i = 0; i<Store.size(); i++){
            cout<<Store[i]<<" ";
        }
        cout<<endl;
    }
    void PointUpdate(ll cidx, ll val, ll lx, ll rx, ll idx){
        if(cidx > rx || cidx < lx){
            return;
        }
        if(rx - lx == 0){
            return;
        }
        if(rx - lx == 1){
            ST[idx] +=(val + Store[idx]);
            Store[idx] = 0;
            return;
        }
        ST[idx] += val;
        ST[idx] += Store[idx]*(rx-lx);
        Store[2*idx] += Store[idx];
        Store[2*idx + 1] += Store[idx];
        Store[idx] = 0;
        ll mid = (lx+rx)/2;
        PointUpdate(cidx, val, lx, mid, 2*idx);
        PointUpdate(cidx, val, mid, rx, 2*idx + 1);
    }
    void RangeUpdate(ll l, ll r, ll val, ll lx, ll rx, ll idx){
        cout<<lx<<" "<<rx<<endl;
        if(r < lx || rx < l){
            return;
        }
        if(rx - lx == 0){
            return;
        }
        if(l <= lx && rx <= r){
            if(rx - lx == 1){
                ST[idx] += (val+Store[idx]);
                Store[idx] = 0;
                return;
            }
            ST[idx] += (val+Store[idx])*(rx-lx);
            Store[2*idx] += (val+Store[idx]);
            Store[2*idx + 1] += (val+Store[idx]);
            Store[idx] = 0;
            return;
        }
        if(rx - lx == 1){
            return;
        }
        ll mid = (lx+rx)/2;
        RangeUpdate(l, r, val, lx, mid, 2*idx);
        RangeUpdate(l, r, val, mid, rx, 2*idx + 1);
    }
};

int main(){
    ll n,q;
    cin>>n>>q;
    vector<ll> v(n);
    for(int i = 0; i<n; i++) cin>>v[i];
    SegmentTree s(n, v);
    s.build(0, n, 1);
    // s.print();
    for(int i = 0; i<q; i++){
        ll type,x,y;
        cin>>type>>x>>y;
        x--;
        if(type == 1){
            s.PointUpdate(x, y - v[x], 0, n, 1);
            // v[x] = y;
        }
        else {
            cout<<s.get(x, y, 0, n, 1)<<endl;
        }
    }
}