// Source: https://oj.leetcode.com/problems/search-for-a-range/

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) { //使用STL函数
        pair<int*, int*> p = equal_range(A, A + n, target);
        vector<int> ans;
        if (p.first == p.second) //没找到
            ans.push_back(-1), ans.push_back(-1);
        else                    //末尾位置为实际最后出现的下一个位置
            ans.push_back(p.first - A), ans.push_back(p.second - A - 1);
        return ans;
    }
    
    vector<int> searchRange2(int A[], int n, int target) {
        int st1 = 0, ed1 = n - 1; //st1为大于或等于target的第一个元素
        while (st1 < ed1)
        {
            int mid = st1 + ((ed1 - st1) >> 1);
            if (A[mid] >= target) ed1 = mid;
            else st1 = mid + 1;
        }
        
        int st2 = 0, ed2 = n - 1; //st2为小于或等于target的最后一个元素
        while (st2 < ed2) 
        {
            int mid = st2 + ((ed2 - st2 + 1) >> 1); //这里避免死循环
            if (A[mid] <= target) st2 = mid;
            else ed2 = mid - 1;
        }
        
        if (A[st1] != target) st1 = st2 = -1; //没找到
        
        vector<int> ans;
        ans.push_back(st1);
        ans.push_back(st2);
        return ans;
    }
};