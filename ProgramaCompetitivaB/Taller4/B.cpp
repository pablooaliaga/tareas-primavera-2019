#include <bits/stdc++.h>

typedef struct {
    int n;
    int frec;
} mypair;
typedef struct{
    mypair extrIzq;
    mypair node;
    mypair extrDer; 
} mynode;


using namespace std;
struct SegmentTree{

    vector<mynode>ST;
    mypair pn = {0, 0};
    mynode nn = {pn,pn,pn};

    int n;

    mynode merge(mynode p, mynode s){
        mypair a = p.extrIzq;
        mypair b = p.node;
        mypair c = p.extrDer;
        mypair d = s.extrIzq;
        mypair e = s.node;
        mypair f = s.extrDer;
        if(a.n == f.n){
            mypair n = {a.n, a.frec + f.frec};
            mynode node = {n,n,n};
            return node;
        }

        if(a.n == d.n){
            mypair izq = {a.n, a.frec+ d.frec};
            if(izq.frec >= e.frec){
                mynode node = {izq, izq, f};
                return node;
            }
            else{
                mynode node = {izq, e, f};
                return node;
            }
        }

        if(c.n == f.n){
            mypair der = {c.n, c.frec + f.frec};
            if(der.frec >= b.frec){
                mynode node = {a, der, der};
                return node;
            }
            else{
                mynode node = {a, b, der};
                return node;
            }
        }

        if(c.n == d.n){
            mypair k = {c.n, c.frec + d.frec};
            int max_frec = max(max(b.frec, e.frec), k.frec);
            if(max_frec == b.frec){
                mynode node = {a, b, f};
                return node;
            }
            if(max_frec == e.frec){
                mynode node = {a, e, f};
                return node;
            }
            else{
                mynode node = {a, k, f};
                return node;
            }
        }       
        else{
            if(b.frec >= e.frec){
                mynode node = {a,b,f};
                return node;
            }
            else{
                mynode node = {a, e, f};
                return node;

            }
        }  
    }
    void init(int i, int l, int r, vector<int>&a){
        if (l==r){
            int num = a[l];
            mypair mp = {num, 1};
            mynode mn = {mp,mp,mp};
            ST[i]=mn;return;
        }
        init(i*2, l, (l+r)/2, a);
        init(i*2+1, (l+r)/2+1, r, a);
        ST[i]=merge(ST[2*i], ST[2*i+1]);
    }
    SegmentTree(vector<int> &a){
        n = a.size();
        ST.resize(4*n+5, nn);
        init(1, 0, n-1, a);
    }
    mynode query(int i, int l, int r, int a, int b){
        if (r<a or l>b)
            return nn;
        if (l>=a and r<=b)
            return ST[i];
        return merge(query(2*i, l, (l+r)/2, a, b), query(2*i+1, (l+r)/2+1, r, a, b));
    }


    int myquery(int a, int b){
        return query(1, 0, n-1, a, b).node.frec;
    }
};

/* PROBLEM

*/

/* INPUT

*/

/* OUTPUT

*/




int n, q, aux, l,r;


int main(int argc, char const *argv[])
{
    cin >> n;
    cin >> q;
    vector<int> nums;
    
    for(int i=0; i<n; i++){
        cin >> aux;
        nums.push_back(aux);
    }
    SegmentTree st(nums);

    for(int i=1; i<st.ST.size(); ++i) {
        cout << i << ": ";

        cout << st.ST[i].extrIzq.n << " " << st.ST[i].extrIzq.frec << " " << st.ST[i].node.n << " " << st.ST[i].node.frec << " "<< st.ST[i].extrDer.n << " " << st.ST[i].extrDer.frec << endl;

    }

    for(int j=0; j<q; j++){
        cin >> l;
        cin >> r;
        cout << st.myquery(l-1,r-1)<<endl;
        

    }
    int z;
    cin >> z;
    return 0;
}