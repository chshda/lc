// Source: https://oj.leetcode.com/problems/compare-version-numbers/

class Solution {
public:
    void f(string &a, string &b)
    {
        if (b.find_first_of('.') != -1) 
            a = b.substr(0, b.find_first_of('.')),
            b = b.substr(b.find_first_of('.') + 1, b.size());
        else 
            a = b, b = "";
    }
    
    int compareVersion(string version1, string version2) {
        while (!version1.empty() && !version2.empty())
        {
            string a1, a2;
            f(a1, version1);
            f(a2, version2);

            int n1 = atoi(a1.c_str()), n2 = atoi(a2.c_str());
            if (n1 > n2) return 1;
            if (n1 < n2) return -1;
        }
        
        if (!version1.empty())
        {
            while (!version1.empty())
            {
                string a; 
                f(a, version1);
                int n = atoi(a.c_str());
                if (n > 0) return 1;
            }
            return 0;
        }
        
        if (!version2.empty())
        {
            while (!version2.empty())
            {
                string a; 
                f(a, version2);
                int n = atoi(a.c_str());
                if (n > 0) return -1;
            }
            return 0;
        }
        return 0;
    }
};