#define INF (INT_MAX-2)

class Solution {
public:
  int n;
  int dp[305][15];
  
  // index into jobDifficulty and dr is days remaining
  int dfs (int index, int dr, vector <int> &jd) {
    if (index == n && dr == 0) //end of our search with all elements covered and 0 days remaining
      return 0;
    
    if (index == n || dr == 0 || n-index < dr) //if elements are remaining or elements are used up but days are remaining
      return INF;
      
    if (dp[index][dr] != -1) //if already seen this state,return it
      return dp[index][dr];

    int ans = INF;
    int maxele = -INF;
    for(int j = index; j < n; j++) {   
      maxele = max(maxele, jd[j]); //max element from i to j
      ans=min(ans, maxele + dfs(j+1, dr-1, jd)); //minimum of all possible answers
    }
    dp[index][dr] = ans;
    return ans;
  }

    int minDifficulty (vector<int>& jobDifficulty, int d) {
        n = jobDifficulty.size();
        if (n < d)       //not possible
            return -1;
        memset(dp, -1, sizeof(dp));
        int ans= dfs(0, d, jobDifficulty);
        return ans;
    }
};
