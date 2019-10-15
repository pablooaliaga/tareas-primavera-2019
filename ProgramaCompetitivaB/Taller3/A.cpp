#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <map>
#include <set>

using namespace std;

/* PROBLEM


*/

/* INPUT

*/

/* OUTPUT

*/
typedef long long ll;

struct FT {
	vector<ll> vec;

	FT(int n) {
		vec.assign(n, 0);
	}

	ll query(int i) {
		ll sum = 0;
	  	for (; i; i -= (i & (-i))) sum += vec[i];
	  	return sum;
	}

	void update(int i, long long x) {
	  	for (; i < vec.size(); i += (i & (-i))) vec[i] += x;
	}
};

struct op{
    int l;
    int r;
    int v;
};

int main(int argc, char const *argv[])
{
    int max = 100001;
    // TODO: Implement this
    int n;
    int k;
    int m;
    cin >> n;
    cin >> m;
    cin >> k;
    FT fop = FT(m+1);
    int arr[n+1];
    op ops[m+1];
    FT sumT = FT(n+1);
    for (int i = 1; i<n+1; i++){
        int n_i;
        cin >> n_i;
        arr[i] = n_i;
    }

    for(int i=1; i<m+1; i++){
        op op_i;
        cin >> op_i.l;
        cin >> op_i.r;
        cin >> op_i.v;
        ops[i] = op_i;
    }
    for(int i=0; i<k; i++){
        int l;
        int r;
        cin >> l;
        cin >> r;
        fop.update(l, 1);
        fop.update(r+1, -1);
    }

    for(int i = 1; i<m+1; i++){
        ll res = fop.query(i);
        op op_i = ops[i];
        sumT.update(op_i.l, op_i.v * res);
        sumT.update(op_i.r + 1, -op_i.v *res);
    }

    for(int i=1; i < n+1; i++){
        ll elem = arr[i] + sumT.query(i);
        cout << elem;
        if(i != n){
            cout << " ";
        }
    }



    return 0;
}