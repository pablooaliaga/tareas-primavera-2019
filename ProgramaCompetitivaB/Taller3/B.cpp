
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
CVJETICI
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
    //inicializamos el arbolito
    int max = 100001;
    ll flowers[max] = {};
    FT ftree = FT(max);
    int d;
    cin >> d;
    int l;
    int r;
    int deltaL;
    int deltaR;
    ll nuevos;

    //iterar en los dias
    for(int j=0; j<d; j++){
        
        nuevos=0;
        cin >> l;
        cin >> r;

        //query, se pregunta si hay horizontales en el punto y si hay flowers
        deltaL = ftree.query(l) - flowers[l];
        if(deltaL > 0){
            flowers[l] += deltaL;
            nuevos += deltaL;
        }
        deltaR = ftree.query(r) - flowers[r];
        if(deltaR > 0){
            flowers[r] += deltaR;
            nuevos += deltaR;
        }
        
        cout<<nuevos<<endl;
        ftree.update(l+1,1);
        ftree.update(r, -1);


    }


    return 0;
}