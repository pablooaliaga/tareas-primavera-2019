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

int i, j;
int n;

//max sum is 16 + 15 == 31 -> so we should have a prime number array to 31.
int primes[32] = {0,1,1,1,0,1,0,1,0,0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1};
                //0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31

bool verify(vector<int> lista){
    for(i=0; i<=lista.size(); i++){
        if(!primes[(lista[i%lista.size()]+lista[(i+1)%lista.size()])]) return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    int cases = 0;
    while(cin >> n){

        vector<int> lista;
        for(int i=1; i<=n ; i++){
            lista.push_back(i);
        }
        sort(lista.begin()+1, lista.end());

        cout << "Case "<< ++cases <<":"<<endl;
        do{
            if (verify(lista)){
                for(i=0; i<lista.size()-1; i++){
                    cout << lista[i] << " ";
                }
                cout << lista[lista.size()-1] << endl;
            }

        }while(next_permutation(lista.begin()+1, lista.end()));
        cout << endl;
        

    }   
    
    return 0;
}