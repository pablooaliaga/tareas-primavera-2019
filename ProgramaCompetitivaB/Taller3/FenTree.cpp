#include <bits/stdc++.h>

using namespace std;

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


int main() {
	ios::sync_with_stdio(0);
	int n; cin >> n;

	FT F = FT(n);
	for(int i=0; i<n; i++) {
		ll a; cin >> a;
		F.update(i+1, a);
	}

	int q; cin >> q;

	for(int i=0; i<q; i++) {
		int t; cin >> t;

		// Indices de 1 a n
		if(t == 1) { // Update
			int p; ll a; cin >> p >> a;
			F.update(p, a);
		} else {     // Query
			int s, f; cin >> s >> f;
			cout << F.query(f) - F.query(s-1) << "\n";
		}
	}


	return 0;
}
