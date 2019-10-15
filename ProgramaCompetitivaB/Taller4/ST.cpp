#include <bits/stdc++.h>

using namespace std;
struct SegmentTree{
    vector<int>ST;
    int n;
    void init(int i, int l, int r, vector<int>&a){
        if (l==r){
            ST[i]=a[l];return;
        }
        init(i*2, l, (l+r)/2, a);
        init(i*2+1, (l+r)/2+1, r, a);
        ST[i]=min(ST[2*i], ST[2*i+1]);
    }
    SegmentTree(vector<int>&a){
        n=a.size();
        ST.resize(4*n+5, INT_MAX);
        init(1, 0, n-1, a);
    }
    void update(int i, int l, int r, int pos, int val){
        if (r<pos or l>pos)
            return;
        if (l==pos and r==l){
            ST[i]=val;
            return;
        }
        update(2*i, l, (l+r)/2, pos, val);
        update(2*i+1, (l+r)/2+1, r, pos, val);
        ST[i]=min(ST[2*i], ST[2*i+1]);
    }
    int query(int i, int l, int r, int a, int b){
        if (r<a or l>b)
            return INT_MAX;
        if (l>=a and r<=b)
            return ST[i];
        return min(query(2*i, l, (l+r)/2, a, b), query(2*i+1, (l+r)/2+1, r, a, b));
    }


    int query(int a, int b){
        return query(1, 0, n-1, a, b);
    }
    void update(int pos, int val){
        update(1, 0, n-1, pos, val);
    }
};

/*
    vector<int>v(10, 0);    //Crea un vector v de tamano 10 lleno de 0's
    SegmentTree S(v); //Crea un SegmentTree llamado S con vector inicial v
    S.update(pos, val); //Cambia la posicion pos del arreglo al valor val
    S.query(a, b); //Pregunta del rango [a, b].
*/
int main(){

    return 0;
}
