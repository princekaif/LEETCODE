/* 

 Intersection of Two Arrays II


Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must appear as many times as it shows in both arrays and you may return the result in any order.

 

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]
Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
Explanation: [9,4] is also accepted.
 

Constraints:

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000
   

   ==================================================solutions===================

*/
class Solution {
public:
    std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_map<int, int> freq;
        
        // Count frequencies of Aelements in nums1
        for (int num : nums1) {
            freq[num]++;
        }
        
        std::vector<int> result;
        
        // Find intersection of nums1 and nums2 based on frequencies
        for (int num : nums2) {
            if (freq.find(num) != freq.end() && freq[num] > 0) {
                result.push_back(num);
                freq[num]--;
            }
        }
        
        return result;
    }
};