#include <bits/stdc++.h>    
using namespace std;
typedef long long ll;                                //ll funciona como long long


struct SegmentTree{
    vector<pair <ll, ll>>ST;
    int n;
    pair <ll, ll> neutro = {0LL, 0LL};

    pair <ll,ll> merge(pair <ll,ll> left, pair <ll,ll> right){
        pair <ll,ll> res;
        res.first = left.first ; res.second = left.second;
        //primera pasada se saca ambos max
        if(right.first > res.first || right.first > res.second){
            if(res.first > res.second){
                res.second = right.first;
            } else {
                res.first = right.first;
            }
        }
        if(right.second > res.first || right.second > res.second){
            if(res.first > res.second){
                res.second = right.second;
            } else {
                res.first = right.second;
            }
        }
        return res;
    }

    void init(int i, int l, int r, vector<ll>&a){
        if (l==r){
            pair <ll,ll> hoja = {a[l], 0LL};
            //printf("Nueva hoja con hijo: %d\n",(int)hoja.first);
            ST[i]= hoja;
            return;
        }
        init(i*2, l, (l+r)/2, a);
        init(i*2+1, (l+r)/2+1, r, a);
        pair <ll,ll> m = merge(ST[2*i], ST[2*i+1]);
        //printf("Padre con l=%d, y r=%d\n",(int)m.first,(int)m.second);
        ST[i] = m;
    }
    SegmentTree(vector<ll>&a){
        n=a.size();
        ST.resize(4*n+5, neutro);
        init(1, 0, n-1, a);
    }
    void update(int i, int l, int r, int pos, ll val){
        if (r<pos or l>pos)
            return;
        if (l==pos and r==l){
            ST[i].first = val;
            return;
        }
        update(2*i, l, (l+r)/2, pos, val);
        update(2*i+1, (l+r)/2+1, r, pos, val);
        ST[i]=merge(ST[2*i], ST[2*i+1]);
    }
    pair <ll,ll> query(int i, int l, int r, int a, int b){
        if (r<a or l>b)
            return neutro;
        if (l>=a and r<=b)
            //printf("First: %d, Second: %d\n",(int)ST[i].first,(int)ST[i].second);
            return ST[i];
        return merge(query(2*i, l, (l+r)/2, a, b), query(2*i+1, (l+r)/2+1, r, a, b));
    }


    ll query(int a, int b){
        pair <ll,ll> res = query(1, 0, n-1, a, b);
        return res.first + res.second;
    }
    void update(int pos, ll val){
        update(1, 0, n-1, pos, val);
    }
};

int N, Q;
int main(int argc, char const *argv[])
{
    cin >> N;
    
    vector <ll> nums;
    ll aux;
    for(int i=0; i<N; i++){
        cin >> aux;
        nums.push_back(aux);
    }
    SegmentTree st(nums);

    cin >> Q;
    char qt;
    int left;
    int right;
    ll val;
    for(int q=0; q<Q; q++){
        cin >> qt;
        if(qt == 'Q'){
            cin >> left;
            cin >> right;
            cout << st.query(left - 1, right - 1) << endl;
        }
        else if(qt == 'U'){
            cin >> left;
            cin >> val;
            st.update(left-1, val);
        }
    }
    
    return 0;
}