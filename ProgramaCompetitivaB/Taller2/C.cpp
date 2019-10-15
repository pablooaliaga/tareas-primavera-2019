#include <stdio.h>
#include <iostream>

using namespace std;

/* PROBLEM
A-sequence
*/

/* INPUT
first input n -> number of numbers of sequence
sequence of n numbers where 1 <= N <= 1000
*/

/* OUTPUT
YES OR NO, its sequence
*/


int n;
bool es;



int main()
{   
    int test_case = 0;

    while(cin >> n){
        es = true;
        int A[1001] = {} , nums[40];
        
        for(int i=0; i<n ; i++){
            cin >> nums[i];
        }

        A[0] = 1;

        for(int i=0; i<n;i++){
            for(int j = 1000-nums[i]; j>=0 ; j--){
                if(A[j]) A[j+nums[i]] += A[j];
            }   
        }

        int anterior = 0;
        for(int i=0; i<n; i++){
            if(nums[i]< anterior) es=false;
            anterior = nums[i];
            if(A[nums[i]] != 1) es=false;
        }
        
        
        cout << "Case #" << ++test_case << ":" ;
        for(int i=0; i<n;i++){
            cout<<" "<<nums[i];
        }
        cout << endl;
        if(es){
            cout<<"This is an A-sequence."<<endl;
        }
        else{
            cout<<"This is not an A-sequence."<<endl;
        }
    }
    

    // TODO: Implement this
    
    return 0;
}