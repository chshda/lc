// Source: https://oj.leetcode.com/problems/single-number-ii/

class Solution {
public:
    int singleNumber(int A[], int n) {
        int one = 0, two = 0, three = 0;
        for (int i = 0; i < n; i++)
        {
            two |= one & A[i];//哪些位出现2次1
            one ^= A[i];      //哪些位出现1次1 
            three = one & two;//哪些位出现3次1
            one &= ~three;    //去掉出现3次1的位
            two &= ~three;    //去掉出现3次1的位
        }
        return one;
    }
    
    int singleNumber2(int A[], int n) {
        int ans = 0;
        for (int i = 0; i < 32; i++) //逐位进行
        {
            int t = 0; //出现3次的数在该位上出现次数为3的倍数
            for (int j = 0; j < n; j++) t += (A[j] >> i) & 1;
            ans |= (t % 3) << i;
        }
        return ans;
    }
};