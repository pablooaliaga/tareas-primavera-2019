#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

typedef struct {
    ll S;
    ll maxpref;
    ll maxsuf;
    ll total;
} mynode;

struct SegmentTree{
    vector<mynode>ST;
    int n;
    mynode neutro = {-INT_MAX, -INT_MAX, -INT_MAX, -INT_MAX};

    mynode merge(mynode left, mynode right){
        ll S = max({left.S, right.S, left.maxsuf + right.maxpref});
        ll T = left.total + right.total;
        ll Pref = max({left.maxpref, left.total + right.maxpref});
        ll Suf = max({right.maxsuf, right.total + left.maxsuf});
        
        mynode newnode = {S, Pref, Suf, T};
        return newnode;
    }

    void init(int i, int l, int r, vector<ll>&a){
        if (l==r){
            mynode hoja = {a[l], a[l], a[l], a[l]};
            ST[i]=hoja;return;
        }
        init(i*2, l, (l+r)/2, a);
        init(i*2+1, (l+r)/2+1, r, a);
        ST[i]=merge(ST[2*i], ST[2*i+1]);
    }
    SegmentTree(vector<ll>&a){
        n=a.size();
        ST.resize(4*n+5);
        init(1, 0, n-1, a);
    }

    mynode query(int i, int l, int r, int a, int b){
        if (r<a or l>b)
            return neutro;
        if (l>=a and r<=b)
            return ST[i];
        return merge(query(2*i, l, (l+r)/2, a, b), query(2*i+1, (l+r)/2+1, r, a, b));
    }


    ll query(int a, int b){
        return query(1, 0, n-1, a, b).S;
    }
};

int N, M;
int main(int argc, char const *argv[])
{
    cin >> N;
    vector<ll> vec;
    ll aux;
    for(int n=0; n<N; n++){
        cin >> aux;
        vec.push_back(aux);
    }

    SegmentTree st(vec);

    int l,r;
    cin >> M;
    for(int m=0; m<M; m++){
        cin >> l;
        cin >> r;
        cout << st.query(l-1,r-1);
        if(m!=M-1){
            cout << endl;
        }
    }
    return 0;
}