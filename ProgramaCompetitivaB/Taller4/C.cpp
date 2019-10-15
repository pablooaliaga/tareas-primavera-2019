#include <bits/stdc++.h>

using namespace std;
struct SegmentTree{
    vector<long long>ST;
    int n;
    int h;
    long long neutro = 0;

    long long merge(long long left, long long right, int deep){
        int lvl = (h - deep) % 2;
        //if lvl is 0 is bitwise XOR
        if(lvl == 0){
            //cout << "Imprimiendo XOR de " << left << " y " << right << endl;
            return left ^ right;
        }
        //if lvl is 1 is bitwise OR
        else{
            //cout << "Imprimiendo OR de " << left << " y " << right << endl;
            return left | right;
        }
    }

    void init(int i, int l, int r, vector<long long>&a, int deep){
        if (l==r){
            ST[i]=a[l];return;
        }
        init(i*2, l, (l+r)/2, a, deep + 1);
        init(i*2+1, (l+r)/2+1, r, a, deep + 1);
        ST[i]=merge(ST[2*i], ST[2*i+1], deep);
    }
    SegmentTree(vector<long long>&a){
        n=a.size();
        //cout << "El tamaño de nodos es: " << n << endl;
        h=(int) log2f (n);
        //cout << "La altura es: "<< h << endl;
        ST.resize(4*n+5, neutro);
        init(1, 0, n-1, a, 0);
    }
    void update(int i, int l, int r, int pos, int val, int deep){
        if (r<pos or l>pos)
            return;
        if (l==pos and r==l){
            ST[i]=val;
            return;
        }
        update(2*i, l, (l+r)/2, pos, val, deep + 1);
        update(2*i+1, (l+r)/2+1, r, pos, val, deep + 1);
        ST[i]=merge(ST[2*i], ST[2*i+1], deep);
    }
    int query(int i, int l, int r, int a, int b, int deep){
        if (r<a or l>b)
            return neutro;
        if (l>=a and r<=b)
            return ST[i];
        //cout << "a = "<< a << " b= " <<b<<" l= "<<l <<" r= "<<r<<endl;
        //cout << "Doing merge on query" << endl;
        return merge(query(2*i, l, (l+r)/2, a, b, deep + 1), query(2*i+1, (l+r)/2+1, r, a, b, deep + 1), deep);
    }


    int query(int a, int b){
        return query(1, 0, n-1, a, b, 0);
    }
    void update(int pos, int val){
        update(1, 0, n-1, pos, val, 0);
    }
};

int n, m;

int main(int argc, char const *argv[])
{
    cin >> n;
    cin >> m;
    long long aux;

    vector<long long> vec;
    int totalSize = pow(2,n);
    for(int i=0; i<totalSize;i++){
        //copy the nums into vector
        cin >> aux;
        vec.push_back(aux);
    }
    
    SegmentTree st(vec);
    
    int p;
    long long b;
    //then receive queries
    for(int q=0; q<m; q++){
        cin >> p;
        cin >> b;
        st.update(p-1, b);
        cout << st.query(0, totalSize - 1);
        if(q!=m-1){
            cout << endl;
        }
    }
    
    return 0;
}