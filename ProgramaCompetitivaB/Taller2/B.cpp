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

int n;

//max sum is 16 + 15 == 31 -> so we should have a prime number array to 31.
int primes[32] = {0,1,1,1,0,1,0,1,0,0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1};
                //0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31

void armar(int *lista,int k, int n){
    if(k==n && primes[lista[0] + lista[n-1]]){
        //list ready print
        for(int i=0; i<n-1 ; i++){
            cout << lista[i] << " ";
        }
        cout << lista[n-1] << endl;
    }

    for(int i=2; i<=n; i++){
        bool used = false;
        for(int j=0; j<k; j++){
            if(lista[j]==i){
                used = true;
                break;
            }
        }
        if(!used){
            if(primes[lista[k-1] + i]){

                lista[k] = i;
                armar(lista, k+1, n);
            }
        } 
    }
    return;


}

int main(int argc, char const *argv[])
{
    int cases = 0;
    while(cin >> n){
        cases++;
        if(cases > 1) cout << endl;
        int lista[n] = {};
        lista[0] = 1;

        cout << "Case "<< cases <<":"<<endl;
        armar(lista, 1, n);
        
        

    }   
    
    return 0;
}