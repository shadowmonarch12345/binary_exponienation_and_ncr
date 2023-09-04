/*
You are given a string s and an integer k.

A k-subsequence is a subsequence of s, having length k, and all its characters are unique, i.e., every character occurs once.

Let f(c) denote the number of times the character c occurs in s.

The beauty of a k-subsequence is the sum of f(c) for every character c in the k-subsequence.

For example, consider s = "abbbdd" and k = 2:

f('a') = 1, f('b') = 3, f('d') = 2
Some k-subsequences of s are:
"abbbdd" -> "ab" having a beauty of f('a') + f('b') = 4
"abbbdd" -> "ad" having a beauty of f('a') + f('d') = 3
"abbbdd" -> "bd" having a beauty of f('b') + f('d') = 5
Return an integer denoting the number of k-subsequences whose beauty is the maximum among all k-subsequences. Since the answer may be too large, return it modulo 109 + 7.

A subsequence of a string is a new string formed from the original string by deleting some (possibly none) of the characters without disturbing the relative positions of the remaining characters.

Notes

f(c) is the number of times a character c occurs in s, not a k-subsequence.
Two k-subsequences are considered different if one is formed by an index that is not present in the other. So, two k-subsequences may form the same string.
 

Example 1:

Input: s = "bcca", k = 2
Output: 4
Explanation: From s we have f('a') = 1, f('b') = 1, and f('c') = 2.
The k-subsequences of s are: 
bcca having a beauty of f('b') + f('c') = 3 
bcca having a beauty of f('b') + f('c') = 3 
bcca having a beauty of f('b') + f('a') = 2 
bcca having a beauty of f('c') + f('a') = 3
bcca having a beauty of f('c') + f('a') = 3 
There are 4 k-subsequences that have the maximum beauty, 3. 
Hence, the answer is 4. 
Example 2:

Input: s = "abbcd", k = 4
Output: 2
Explanation: From s we have f('a') = 1, f('b') = 2, f('c') = 1, and f('d') = 1. 
The k-subsequences of s are: 
abbcd having a beauty of f('a') + f('b') + f('c') + f('d') = 5
abbcd having a beauty of f('a') + f('b') + f('c') + f('d') = 5 
There are 2 k-subsequences that have the maximum beauty, 5. 
Hence, the answer is 2. 
*/

int mod=1e9+7;
    long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
    int nCr(int n, int r){
        // code here
        if(r==0 || r==n) return 1;
        vector<vector<int>> dp(n+1, vector<int>(r+1,0));
        for(int i=0;i<=n;++i){
            for(int j=0;j<=min(i,r);++j){
                if(j==0 || j==i){
                    dp[i][j]=1;
                }
                else{
                    dp[i][j] = (dp[i-1][j-1]%mod+dp[i-1][j]%mod)%mod;
                }
            }
        }
        return dp[n][r];
    }
    int countKSubsequencesWithMaxBeauty(string s, int k) {
        
        map<char,int>m;
        for(int i=0;i<s.size();i++){
            m[s[i]]++;
        }
        
        if(m.size()<k)return 0;
        vector<pair<int ,char>>v;
        map<int,int>mp;
        for(auto it:m){
            mp[it.second]++;
          //  cout<<it.second;
            v.push_back({it.second,it.first});
        }
        sort(v.rbegin(),v.rend());
        long long ans=1;
        int cnt=0;
        int i=0;
       while(true){
            
           /* if(i<k-1){
                ans=((ans%mod)*(m[v[i].second]%mod)%mod);
                mp[v[i].first]--;
            }*/
           
           if(cnt+mp[v[i].first]>=k){
               
            
               int x=nCr(mp[v[i].first],k-cnt)%mod;
               
               int y=binpow(m[v[i].second],k-cnt,mod)%mod;
              
              ans=(((ans%mod)*(y%mod)%mod)*(x))%mod;
               break;
               
           }
                 else {
                     cnt++;
                      ans=((ans%mod)*(m[v[i].second]%mod)%mod);
                     mp[v[i].first]--;
                 }
           i++;
        }
        return ans;
    }