#include <bits/stdc++.h>
#include <cmath>


using namespace std;

/* PROBLEM
Present, growing plants in a row, maximize the size of the smallest one at day m 
*/

/* INPUT
n->int m->int w->int
n sizes of plants -> [n] longlong 
*/

/* OUTPUT
Single integer, maximum final height of the smallest flower
*/

int binary(long long *flowers, int n, int w, int m, long long res){
    long long dUsed = 0;
    long long penalty[2*n + 1];
    long long nextAdd = 0;

    memset(penalty, 0, sizeof(penalty));

    for(int i=0; i<n; i++){
        nextAdd += penalty[i];
        long long flower = flowers[i] + nextAdd;

        if(flower < res){
            //give more days
            long long diff = (res - flower);
            dUsed += diff;
            if(dUsed > m){
                return 0;
            }
            nextAdd += diff;
            penalty[i+w] -= diff;
        }
    }
    return dUsed <= m;
}

int main(int argc, char const *argv[])
{
    int n,m,w;
    cin >> n;
    cin >> m;
    cin >> w;

    long long flowers[n];
    for(int i=0; i<n; i++){
        cin >> flowers[i];
    }


    long long min=0;
    long long max= pow(10,10);
    long long mid;
    int rc;

    while(min<max){
        //cout << min << endl << max << endl;
        mid = (max+min)/2 + 1;
        rc = binary(flowers, n, w, m, mid);
        if(rc){
            min = mid;
        }
        else{
            max = mid - 1;
        }
    }
    
    cout<<min<<endl;
    return 0;
}