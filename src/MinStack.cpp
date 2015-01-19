// Source: https://oj.leetcode.com/problems/min-stack/

class MinStack {
public:
    void push(int x) {
        normal.push(x);
        if (minval.empty() || minval.top() >= x) minval.push(x);
    }

    void pop() {
        int top = normal.top();
        normal.pop(); 
        if (top == minval.top())
            minval.pop();
    }

    int top() {
        return normal.top();
    }

    int getMin() {
        return minval.top();
    }
private:
    stack<int> normal;
    stack<int> minval;
};