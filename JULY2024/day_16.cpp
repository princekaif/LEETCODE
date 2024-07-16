/**2096. Step-By-Step Directions From a Binary Tree Node to Another

You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n. You are also given an integer startValue representing the value of the start node s, and a different integer destValue representing the value of the destination node t.

Find the shortest path starting from node s and ending at node t. Generate step-by-step directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific direction:

'L' means to go from a node to its left child node.
'R' means to go from a node to its right child node.
'U' means to go from a node to its parent node.
Return the step-by-step directions of the shortest path from node s to node t.

 

Example 1:


Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
Output: "UURL"
Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.
Example 2:


Input: root = [2,1], startValue = 2, destValue = 1
Output: "L"
Explanation: The shortest path is: 2 → 1.
 

Constraints:

The number of nodes in the tree is n.
2 <= n <= 105
1 <= Node.val <= n
All the values in the tree are unique.
1 <= startValue, destValue <= n


------------------
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    void getPath(TreeNode *cur, int targetValue, string &path, string &ans) {
        if (!cur)
            return;
        if (cur->val == targetValue)
            ans = path;
        path.push_back('L');
        getPath(cur->left, targetValue, path, ans);
        path.back() = 'R';
        getPath(cur->right, targetValue, path, ans);
        path.pop_back();
    }

    string getDirections(TreeNode *root, int startValue, int destValue) {
        string tmpPath, startPath, destPath;
        getPath(root, startValue, tmpPath, startPath);
        getPath(root, destValue, tmpPath, destPath);
        // Find the first point at which the paths diverge
        auto [itr1, itr2] = mismatch(startPath.begin(), startPath.end(),
                                     destPath.begin(), destPath.end());
        return string(startPath.end() - itr1, 'U') +
               string(itr2, destPath.end());
    }
};
