#include <bits/stdc++.h>
using namespace std;

struct SegmentTree{
    vector<long long>ST;
    int n;
    void init(int i, int l, int r, vector<long long>&a){
        if (l==r){
            ST[i]=a[l];return;
        }
        init(i*2, l, (l+r)/2, a);
        init(i*2+1, (l+r)/2+1, r, a);
        //computes the sum
        ST[i]=ST[2*i] + ST[2*i+1];
    }
    SegmentTree(vector<long long>&a){
        n=a.size()+1;
        ST.resize(4*n+5, 0);
        init(1, 0, n-1, a);
    }
    void update(int i, int l, int r, int pos, long long val){
        if (r<pos or l>pos)
            return;
        if (l==pos and r==l){
            ST[i]+=val;
            return;
        }
        update(2*i, l, (l+r)/2, pos, val);
        update(2*i+1, (l+r)/2+1, r, pos, val);
        //computes the sum
        ST[i]=ST[2*i] + ST[2*i+1];
    }
    long long query(int i, int l, int r, int a, int b){
        if (r<a or l>b)
            return 0;
        if (l>=a and r<=b)
            return ST[i];
        return query(2*i, l, (l+r)/2, a, b) + query(2*i+1, (l+r)/2+1, r, a, b);
    }


    long long query(int a, int b){
        return query(1, 0, n-1, a, b);
    }
    void update(int pos, long long val){
        update(1, 0, n-1, pos, val);
    }
};



/* PROBLEM
Computes the sum of an array
*/

/* INPUT

*/

/* OUTPUT

*/
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
        SegmentTree st(nums);

        for(int c=0; c<C; c++){
            cin>>type;
            cin>>p;
            cin>>q;
            if(type==0){
                //update
                cin>>v;
                for(int r=p; r<=q; r++){
                    st.update(r, v);
                }
            }
            else{
                //query
                cout<<st.query(p,q);
                if(c!=C-1) cout<<endl;
            }
        }
    }
    return 0;
}