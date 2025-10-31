#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int largestRectangleArea(vector<int> &heights)
{
    int n = heights.size();
    vector<int> nsr(n);
    vector<int> nsl(n);
    stack<int> s;

    // nextSmallerLeft
    nsl[0] = -1;
    s.push(0); // pushing index of 1st element
    for (int i = 1; i < n; i++)
    {
        int curr = heights[i];
        while (!s.empty() && curr <= heights[s.top()])
        {
            s.pop();
        }
        nsl[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }

    // Empty Stack
    while (!s.empty())
    {
        s.pop();
    }

    // nextSmallerRight
    nsr[n - 1] = n;
    s.push(n - 1); // pushing index of last element
    for (int i = n-2; i >= 0; i--)
    {
        int curr = heights[i];
        while (!s.empty() && curr <= heights[s.top()])
        {
            s.pop();
        }
        nsr[i] = s.empty() ? n : s.top();
        s.push(i);
    }

    // maxArea
    int maxArea = 0;
    for (int i = 0; i < n; i++)
    {
        int ht = heights[i];
        int width = nsr[i] - nsl[i] - 1;
        int area = ht * width;

        maxArea = max(area, maxArea);
    }
    cout << maxArea;
}
int main()
{
    vector<int> heights = {0,9,5,7,3,2,8,6,4,1};   
    largestRectangleArea(heights);
    return 0;
}