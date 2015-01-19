// Source: https://oj.leetcode.com/problems/longest-palindromic-substring/

class Solution {
public:
    string longestPalindrome(string s) { //Manacher算法
        string str = "^#"; //添加分隔符
        for (int i = 0; i < s.size(); i++) str += s.substr(i, 1) + "#";
        str += "$";
        
        int n = str.size();
        int p[2100] = {0}; //p[i]为以i为中心的长度
        int mxid = 0, id;  //最远位置及对应中心
        
        for (int i = 1; i < n-1; i++)
        {
            if (mxid > i) //最远距离内，利用镜像位置
                p[i] = min(p[2*id-i], mxid-i);
            else 
                p[i] = 1;
            
            while (str[i+p[i]] == str[i-p[i]]) p[i]++;   //继续匹配
            if (i + p[i] > mxid) mxid = i + p[i], id = i;//更新
        }
        
        int mxlen = 0, mid;
        for (int i = 1; i < n-1; i++)
            if (p[i] > mxlen) mxlen = p[i]-1, mid = i;
        return s.substr((mid-1-mxlen)/2, mxlen);
    }
    
    
    string longestPalindrome2(string s) { //动态规划算法
        
        int n = s.size(), mxlen = 1, st = 0;
        
        bool dp[1001][1001] = {0}; 
        for (int i = 0; i < n; i++)  //长度为1
            dp[i][i] = 1;
        for (int i = 0; i < n-1; i++)//长度为2
            if (s[i] == s[i+1])
                dp[i][i+1] = 1, mxlen = 2, st = i;

        for (int len = 3; len <= n; len++)
            for (int i = 0, j = i + len - 1; j < n; i++, j++)
                if (s[i] == s[j] && dp[i+1][j-1])//首尾相同，中间是回文
                    dp[i][j] = 1, mxlen = len, st = i;
        
        return s.substr(st, mxlen);
    }
};