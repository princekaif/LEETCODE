/*
2392. Build a Matrix With Conditions

Hint
You are given a positive integer k. You are also given:

a 2D integer array rowConditions of size n where rowConditions[i] = [abovei, belowi], and
a 2D integer array colConditions of size m where colConditions[i] = [lefti, righti].
The two arrays contain integers from 1 to k.

You have to build a k x k matrix that contains each of the numbers from 1 to k exactly once. The remaining cells should have the value 0.

The matrix should also satisfy the following conditions:

The number abovei should appear in a row that is strictly above the row at which the number belowi appears for all i from 0 to n - 1.
The number lefti should appear in a column that is strictly left of the column at which the number righti appears for all i from 0 to m - 1.
Return any matrix that satisfies the conditions. If no answer exists, return an empty matrix.

 

Example 1:


Input: k = 3, rowConditions = [[1,2],[3,2]], colConditions = [[2,1],[3,2]]
Output: [[3,0,0],[0,0,1],[0,2,0]]
Explanation: The diagram above shows a valid example of a matrix that satisfies all the conditions.
The row conditions are the following:
- Number 1 is in row 1, and number 2 is in row 2, so 1 is above 2 in the matrix.
- Number 3 is in row 0, and number 2 is in row 2, so 3 is above 2 in the matrix.
The column conditions are the following:
- Number 2 is in column 1, and number 1 is in column 2, so 2 is left of 1 in the matrix.
- Number 3 is in column 0, and number 2 is in column 1, so 3 is left of 2 in the matrix.
Note that there may be multiple correct answers.
Example 2:

Input: k = 3, rowConditions = [[1,2],[2,3],[3,1],[2,3]], colConditions = [[2,1]]
Output: []
Explanation: From the first two conditions, 3 has to be below 1 but the third conditions needs 3 to be above 1 to be satisfied.
No matrix can satisfy all the conditions, so we return the empty matrix.
 

Constraints:

2 <= k <= 400
1 <= rowConditions.length, colConditions.length <= 104
rowConditions[i].length == colConditions[i].length == 2
1 <= abovei, belowi, lefti, righti <= k
abovei != belowi
lefti != righti

*/
class Solution {
 public:
  vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions,
                                  vector<vector<int>>& colConditions) {
    const vector<int> rowOrder = topologicalSort(rowConditions, k);
    if (rowOrder.empty())
      return {};

    const vector<int> colOrder = topologicalSort(colConditions, k);
    if (colOrder.empty())
      return {};

    vector<vector<int>> ans(k, vector<int>(k));
    vector<int> nodeToRowIndex(k + 1);

    for (int i = 0; i < k; ++i)
      nodeToRowIndex[rowOrder[i]] = i;

    for (int j = 0; j < k; ++j) {
      const int node = colOrder[j];
      const int i = nodeToRowIndex[node];
      ans[i][j] = node;
    }

    return ans;
  }

 private:
  vector<int> topologicalSort(const vector<vector<int>>& conditions, int n) {
    vector<int> order;
    vector<vector<int>> graph(n + 1);
    vector<int> inDegrees(n + 1);
    queue<int> q;

    // Build the graph.
    for (const vector<int>& condition : conditions) {
      const int u = condition[0];
      const int v = condition[1];
      graph[u].push_back(v);
      ++inDegrees[v];
    }

    // Perform topological sorting.
    for (int i = 1; i <= n; ++i)
      if (inDegrees[i] == 0)
        q.push(i);

    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      order.push_back(u);
      for (const int v : graph[u])
        if (--inDegrees[v] == 0)
          q.push(v);
    }

    return order.size() == n ? order : vector<int>();
  }
};
