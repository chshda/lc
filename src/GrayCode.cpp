// Source: https://oj.leetcode.com/problems/gray-code/

class Solution {
public:
    vector<int> grayCode(int n) {
        int m = (1 << n);
        vector<int> v;
        if (n == 0)
        {
            v.push_back(0); return v;
        }
        for (int i = 0; i < m; i++)
        {
            vector<int> t(n, 0), t2(n, 0); 
            for (int j = i, id = 0; j; j >>= 1, id++) t[id] = j & 1;
            t2[n-1] = t[n-1];                                       //最高位不变
            for (int j = n - 2; j >= 0; j--) t2[j] = t[j] ^ t[j+1]; //该位和高一位的异或
            int s = 0;
            for (int j = n - 1; j >= 0; j--) s = s * 2 + t2[j];
            v.push_back(s);
        }
        return v;
    }
};