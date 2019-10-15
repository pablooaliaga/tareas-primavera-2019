#include <bits/stdc++.h>    
using namespace std;
typedef long long ll;                                //ll funciona como long long

struct SegmentTreeLazy{
                                                    //Todos los push son para empujar updates
    vector<ll>ST;                                    //Arbol
    vector<ll>UPD;                                    //Arbol de updates
    int n;                                            //largo del arreglo inicial
    ll neutro1, neutro2;                            //valores neutros
    ll mergeThem(ll a, ll b){                        //funcion de mezcla
        return a+b;
    }
    void init(int i, int l, int r, vector<ll>&arr){    //inicializa el segment tree
        if (l==r){                                    //caso bacan
            ST[i]=arr[l];
            return;
        }
        init(2*i, l, (l+r)/2, arr);                    //Casos no bacanes
        init(2*i+1, (l+r)/2+1, r, arr);
        ST[i]=mergeThem(ST[2*i], ST[2*i+1]);
    }
    SegmentTreeLazy(vector<ll>&arr){                //constructor
        neutro2=0LL;
        neutro1=0LL;
        n=arr.size();
        ST.resize(4*n+5, 0LL);
        UPD.resize(4*n+5, neutro2);
        init(1, 0, n-1, arr);
    }
    void update(ll &pos, ll val){                    //update para el pusheo
        pos+=val;
    }
    void push(int i, int l, int r){                    //funcion de pusheo
        update(ST[i], UPD[i] * (r - l + 1));        //update en el rango [l, r]
        if (l!=r){
            update(UPD[2*i], UPD[i]);
            update(UPD[2*i+1], UPD[i]);
        }
        UPD[i]=neutro2;
    }
    void update(int i, int l, int r, int a, int b, ll val){    //update el rango [a, b] con val
        if (l>b or r<a){                                    //Caso fuera
            push(i, l, r);
            return;
        }
        if (a<=l && r<=b){                                    //Caso dentro
            update(UPD[i], val);
            push(i, l, r);
            return;
        }
        push(i, l, r);                                        //Caso interseccion
        update(2*i, l, (l+r)/2, a, b, val);
        update(2*i+1, (l+r)/2+1, r, a, b, val);
        ST[i]=mergeThem(ST[2*i], ST[2*i+1]);
    }
    void update(int a, int b, ll valor){                    //update simbolicamente publico
        if (a>b){                                            //Caso ciclico
            update(1, 0, n-1, 0, b, valor);
            update(1, 0, n-1, a, n-1, valor);
        }
        else                                                //Caso no ciclico
            update(1, 0, n-1, a, b, valor);
    }
    ll get(int i, int l, int r, int a, int b){                //responder queries    
        if (a>r or l>b)                                        //Caso fuera
            return neutro1;
        push(i, l, r);
        if (a<=l and r<=b)                                    //Caso dentro
            return ST[i];
        return mergeThem(get(2*i, l, (l+r)/2, a, b), get(2*i+1, (l+r)/2+1, r, a, b));    //Caso interseccion
    }
    ll get(int a, int b){                                    //Responder queries simbolicamente publico
        if (a>b)                                            //Caso ciclico
            return mergeThem(get(1, 0, n-1, 0, b), get(1, 0, n-1, a, n-1));
        return get(1, 0, n-1, a, b);                        //Caso no ciclico
    }
};

int test_cases;
int N, C;
int type,p,q;
long long v;

int main(int argc, char const *argv[])
{
    cin >> test_cases;
    for(int t=0; t<test_cases;t++){
        cin >> N;
        cin >> C;
        //create the array of size N 
        vector<long long> nums(N,0);
        SegmentTreeLazy st(nums);

        for(int c=0; c<C; c++){
            cin>>type;
            cin>>p;
            cin>>q;
            if(type==0){
                //update
                cin>>v;
                st.update(p-1,q-1,v);
                
                
            }
            else{

                //query
                cout<<st.get(p-1,q-1);
                if(c!=C-1) cout<<endl;
            }
            /*
            for(int i=0; i<N; i++){
                 cout << st.get(i,i) << " ";
            }
            cout << endl;*/
        }
    if(t!=test_cases -1) cout<<endl;
    }
    return 0;
}