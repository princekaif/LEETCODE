
/**
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  2058. Find the Minimum and Maximum Number of Nodes Between Critical Points!!!!!!!!!!!!!!!!!!!!!!!!!!!!

A critical point in a linked list is defined as either a local maxima or a local minima.

A node is a local maxima if the current node has a value strictly greater than the previous node and the next node.

A node is a local minima if the current node has a value strictly smaller than the previous node and the next node.

Note that a node can only be a local maxima/minima if there exists both a previous node and a next node.

Given a linked list head, return an array of length 2 containing [minDistance, maxDistance] where minDistance is the minimum distance between any two distinct critical points and maxDistance is the maximum distance between any two distinct critical points. If there are fewer than two critical points, return [-1, -1].

 

Example 1:


Input: head = [3,1]
Output: [-1,-1]
Explanation: There are no critical points in [3,1].
Example 2:


Input: head = [5,3,1,2,5,1,2]
Output: [1,3]
Explanation: There are three critical points:
- [5,3,1,2,5,1,2]: The third node is a local minima because 1 is less than 3 and 2.
- [5,3,1,2,5,1,2]: The fifth node is a local maxima because 5 is greater than 2 and 1.
- [5,3,1,2,5,1,2]: The sixth node is a local minima because 1 is less than 5 and 2.
The minimum distance is between the fifth and the sixth node. minDistance = 6 - 5 = 1.
The maximum distance is between the third and the sixth node. maxDistance = 6 - 3 = 3.
Example 3:


Input: head = [1,3,2,2,3,2,2,2,7]
Output: [3,3]
Explanation: There are two critical points:
- [1,3,2,2,3,2,2,2,7]: The second node is a local maxima because 3 is greater than 1 and 2.
- [1,3,2,2,3,2,2,2,7]: The fifth node is a local maxima because 3 is greater than 2 and 2.
Both the minimum and maximum distances are between the second and the fifth node.
Thus, minDistance and maxDistance is 5 - 2 = 3.
Note that the last node is not considered a local maxima because it does not have a next node.
 

Constraints:

The number of nodes in the list is in the range [2, 105].
1 <= Node.val <= 105

-------------------------------------------------------------------------------------------------------------------------------------

[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ S O L U T I O N S ]]]]]]]]]]]]]]]]]]]]]]]]]]
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
   
        // Pointers to track the current and previous nodes in the list
        ListNode* previous = head;
        ListNode* current = head->next;

        // Variables to keep track of the positions of the first and last critical points
        int firstCriticalPosition = 0, lastCriticalPosition = 0;
        int index = 1; // Current index within the linked list

        // Initialize the answer with the maximum value for distance calculations
        vector<int> answer(2, INT_MAX);
      
        // Iterate through the linked list to find critical points
        while (current->next) {
            // Check for a critical point, which is either a local minimum or maximum
            bool isCritical = current->val < min(previous->val, current->next->val) || 
                              current->val > max(previous->val, current->next->val);

            if (isCritical) {
                if (lastCriticalPosition == 0) {
                    // This is the first critical point encountered
                    firstCriticalPosition = index;
                } else {
                    // Update the shortest distance between any two critical points
                    answer[0] = min(answer[0], index - lastCriticalPosition);
                    // Update the distance between the first and the current critical point
                    answer[1] = index - firstCriticalPosition;
                }
                // Update the position of the last critical point 
                lastCriticalPosition = index;
            }
            ++index; // Move to the next index
            previous = current; // Move the previous pointer forward
            current = current->next; // Move the current pointer forward
        }
        // If no critical points or only one critical point was found, return {-1, -1}
        if (firstCriticalPosition == lastCriticalPosition) {
            return {-1, -1};
        }
        // Return the distances between critical points
        return answer;
    
    }
};
