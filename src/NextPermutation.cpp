// Source: https://oj.leetcode.com/problems/next-permutation/

class Solution {
public:
    void nextPermutation(vector<int> &num) {
        if (num.size() == 1) return;
        
        int i = num.size() - 2;
        while(i >= 0 && num[i]>= num[i+1]) i--; //找第一组升序
        
        if (i == -1) //全部降序，已是最大排列
        {
            reverse(num.begin(), num.end());
            return;
        }
        
        int j = num.size() - 1; //找第一个大于num[i]的
        while (num[i] >= num[j]) j--;
        swap(num[i], num[j]); //交换
        
        reverse(num.begin() + i + 1, num.end()); //逆转
    }
};