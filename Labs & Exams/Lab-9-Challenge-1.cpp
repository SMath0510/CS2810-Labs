#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin >> n;
    int matrix[n][n];
    
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cin >> matrix[i][j];
        }
    }
    
    int numQueries;
    cin >> numQueries;
    for(int i = 1; i <= numQueries; i++){
        
        int gridIndex, antiClockwise, shiftIndex;
        cin >> gridIndex >> antiClockwise >> shiftIndex;
        
        if(2*gridIndex != n-1){
            for(int i= 1; i<=shiftIndex; i++){
                
                if(antiClockwise == 1){
                    /* Rotating anti Clockwise */
                    
                    int stored = matrix[gridIndex][gridIndex]; // storing one reference element
                    
                    for(int i = gridIndex; i< n-1-gridIndex; i++){
                        matrix[gridIndex][i] = matrix[gridIndex][i+1];
                    }
                    for(int i = gridIndex; i< n-1-gridIndex; i++){
                        matrix[i][n-1-gridIndex] = matrix[i+1][n-1-gridIndex];
                    }
                    for(int i = n-1-gridIndex; i>gridIndex; i--){
                        matrix[n-1-gridIndex][i] = matrix[n-1-gridIndex][i-1];
                    }
                    for(int i = n-1-gridIndex; i>gridIndex; i--){
                        matrix[i][gridIndex] = matrix[i-1][gridIndex];
                    }
                    
                    matrix[gridIndex+1][gridIndex] = stored; // placing the reference element where it belongs
                }
                else{
                    /* Rotating clockwise */
                    
                    int stored = matrix[gridIndex][gridIndex]; // storing one reference element
                    
                    for(int i = gridIndex; i< n-1-gridIndex; i++){
                        matrix[i][gridIndex] = matrix[i+1][gridIndex];
                    }
                    for(int i = gridIndex; i< n-1-gridIndex; i++){
                        matrix[n-1-gridIndex][i] = matrix[n-1-gridIndex][i+1];
                    }
                    for(int i = n-1-gridIndex; i>gridIndex; i--){
                        matrix[i][n-1-gridIndex] = matrix[i-1][n-1-gridIndex];
                    }
                    for(int i = n-1-gridIndex; i>gridIndex; i--){
                        matrix[gridIndex][i] = matrix[gridIndex][i-1];
                    }
                    
                    matrix[gridIndex][gridIndex+1] = stored; // placing the element where it belongs
                }
            }
        }
    }
    
    /* Printing the matrix */
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
