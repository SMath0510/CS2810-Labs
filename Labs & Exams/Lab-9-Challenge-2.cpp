#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, w, c;
    cin >> n >> w >> c;
    
    vector<int> weight(n+1, 0);
    vector<int> cost(n+1, 0);
    
    for(int i = 1; i <= n; i++){
        cin >> cost[i] >> weight[i];
    }
    
    int dp[w+1][w+1];  // stores profit on having capacity w and number of items n
    // max number of items = w
    
    for(int i = 0; i<=w; i++){
        for(int j = 0; j<=w; j++){
            dp[i][j] = 0; // general case 0 profit
        }
    }
    
    for(int i = 1; i <= w; i++){
        for(int j = 1; j <= w; j++){
            for(int k = 1; k <= n; k++){
                
                if(i > weight[k] && dp[i - weight[k]][j-1] != 0) {
                    // If we can take the item, we take it and add to the max cost that we can get using exact i items and total weight j
                    dp[i][j] = max(dp[i][j], dp[i - weight[k]][j-1] + cost[k]); 
                }
                if(i == weight[k] && j == 1) {
                    // Base case : where j = 1, we just checking one item
                    dp[i][j] = max(dp[i][j], dp[i - weight[k]][j-1] + cost[k]);
                }
                
            }
        }
    }
    
    int ans = -1;
    for(int i = 1; i <=w; i++){
        for(int j = c; j <= w; j++){
            ans = max(ans, dp[i][j]); // getting the answer from the dp array
        }
    }
    
    if(ans == 0) ans = -1; // 0 profit can't be a valid case 
    cout << ans << endl;
    return 0;
}
