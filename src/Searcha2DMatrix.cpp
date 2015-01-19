// Source: https://oj.leetcode.com/problems/search-a-2d-matrix/

class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) { //二分搜素
        if (matrix.empty() || matrix[0].empty()) return false;
        
        int m = matrix.size(), n = matrix[0].size();
        int st = 0, ed = m * n - 1;
        while (st <= ed)
        {
            int mid = st + ((ed - st) >> 1), tem = matrix[mid/n][mid%n]; //下标变换
            if (tem == target) return true;
            else if(tem > target) ed = mid - 1;
            else st = mid + 1;
        }
        return false;
    }
};