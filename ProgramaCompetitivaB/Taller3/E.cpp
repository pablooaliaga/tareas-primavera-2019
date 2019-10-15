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



int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        int n;
        cin >> n;
        vector<vector<ll>> tuplas;

        FT ftree = FT(n+1);        

        for(int k=1; k < n+1;k++){

            ll elem;
            cin >> elem;
            vector<ll> vec;
            vec.push_back(elem);
            vec.push_back(k);
            tuplas.push_back(vec);

            //inicializador
            ftree.update(k, 1);
        }
        sort(tuplas.begin(), tuplas.end());

        


        ll inv = 0;
        for(int k=0; k <n; k++){
            int pos = (int) tuplas[k][1];
            ftree.update(pos, -1);
            inv += ftree.query(pos);
        }
        
        cout << inv << endl;

    }
    // TODO: Implement this
    
    return 0;
}