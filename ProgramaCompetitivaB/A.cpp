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
    Separar vacas lo mas lejos posible
*/

/* INPUT
    t the number of test cases
    Line 1: Two space-separated integers: N and C
    Lines 2..N+1: Line i+1 contains integer stall localtion, xi
*/

/* OUTPUT
    For each test cases compute the largest minimum distance between stables
*/

int main(int argc, char const *argv[])
{

    int t;
    cin>>t;

    for(int i=0; i<t; i++){
        int c, n;
        cin>>n;
        cin>>c;

        int arr[n];
        for(int j=0; j<n; j++){
            cin>>arr[j];
        }

        int size = sizeof(arr)/sizeof(arr[0]); 
        sort(arr,arr+size);
        
        int max = arr[n-1] - arr[0];
        int min = 1; 
        int res = max;
        
        if(c == 2){
            return max;
        }

        int auxRes, auxVacas, posAnterior;
        auxRes = max/2;
        while(max!=min){
            auxVacas = c-1;
            posAnterior=0;

            for(int k=1; k<n; k++){
                if(arr[k]-arr[posAnterior] >= auxRes){
                    posAnterior=k;
                    auxVacas--;
                }

                if(auxVacas==0){
                    min=auxRes;
                    auxRes = (max+min+1)/2;
                    break;
                } //SUCESS

                if(k==n-1){
                    max=auxRes-1;
                    auxRes= (max+min+1)/2;
                    break;
                }
            }
            
        }
        cout << max << endl;
    }
    
    return 0;
}