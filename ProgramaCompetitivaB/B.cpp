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
    Find the minimum of the maximum amount of votes in boxes
*/

/* INPUT
    N amount of cities, B amount of boxes,
    "N" inputs which indicates the amount of population per city
*/

/* OUTPUT
    The minimum maximum of votes in boxes
*/

int main(int argc, char const *argv[])
{
    
    
    int n, b;

    cin >> n;
    cin >> b;

    while(n!=-1 && b!=-1){
        int votes[n];
        for(int w=0; w< n; w++){
            cin >> votes[w];
        }

        int size = sizeof(votes)/sizeof(votes[0]); 
        sort(votes,votes+size);

        int max = votes[n-1];
        int min = 1;
        int resp=(max+min)/2;
        int votCity;
        int auxBoxes;
        int restPeople;
        while(max!=min){
            auxBoxes=b;
            
            for(int c=0; c<n; c++){
                auxBoxes-=votes[c]/resp;
                if(votes[c]%resp > 0){
                    auxBoxes--;
                }
            }
            if(auxBoxes<0){//FAIL
                min=resp+1;
                resp=(min+max)/2;
                
            }
            else{//SUCCESS
                max=resp;
                resp=(min+max)/2;

            }
            
        }

        cout<<max<<endl;
        cin>>n>>b;
    }

    return 0;
}