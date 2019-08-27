/*
  A palindrome string is a string which reads the same forward and backward. If a palindrome string is of odd length l,
  then (l+1)/2th character (1 index based) is said to be the centre of the palindrome. You are given a string A. 
  Return an array X of integers where X[i] = (number of odd length palindrome subsequence of A with A[i] as the centre) 
  modulo 1000000007. A subsequence of A is a string which can be derived from A by deleting some of its character. 

Constraints:
  1 <= length(A) <= 1000
  Every character of A will be a lowercase English letter 'a' - 'z'.

Example :
   A : xyzx
   Returns X as [1, 2, 2, 1]
*/
// solution source : https://www.codechef.com/viewsolution/26120510

vector<int> solve(string &s)
{
  const int n = s.size();
  const int mod = 1e9 + 7;
  
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0)); // numbers with prefix and suffix lenght

  for (int prefLen = 1; prefLen <= n; prefLen++)
  {
    for (int suffLen = 1; suffLen <= n && prefLen + suffLen <= n; suffLen++)
    {
      int temp = ((dp[prefLen - 1][suffLen] + dp[prefLen][suffLen - 1]) % mod - dp[prefLen -1][suffLen - 1] + mod) % mod;
      dp[prefLen][suffLen] = (dp[prefLen][suffLen] + temp) % mod;

      const auto lastPrefChar = s[prefLen - 1];
      const auto firstSuffChar = s[n - suffLen];

      if(lastPrefChar == firstSuffChar)
      {
        int temp = 1 + // Match consisting of just firstSuffChar and lastPrefChar.
                   dp[prefLen -1][suffLen - 1]; // All other matches that match firstSuffChar and lastPrefChar.
        dp[prefLen][suffLen] = (dp[prefLen][suffLen]  + temp) % mod;
      }
    }
  }

  // Now that we have dp, we can calculate ans for each of the n positions.
  vector<int> ans;
  
  for (int prefLen = 0; prefLen < n; prefLen++)
  {
    const int suffLen = n - 1 - prefLen;
    ans.push_back(1 + // Matches where both subsequences from prefix and suffix are empty.
                   dp[prefLen][suffLen] // All other subsequences centred around current pos.
                 );
  }
    
  return ans;
}
