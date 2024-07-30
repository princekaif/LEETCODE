class Solution {
public:
    int minimumDeletions(string s) {
        int deletionsRequired = 0; // Tracks the number of deletions required
        int countB = 0;           // Counts the number of 'b's encountered

        // Iterate over each character in the string
        for (char& c : s) {
            if (c == 'b') {
                // When a 'b' is found, increment the count of 'b's
                ++countB;
            } else {
                // If we encounter an 'a', decide whether to delete this 'a' or 
                // any 'b' encountered so far to get a sorted string 'aa...bb...'
                // The min function chooses the smaller of deletion an 'a' or any previous 'b'
                deletionsRequired = std::min(deletionsRequired + 1, countB);
            }
        }

        // Return the minimum number of deletions required to sort the string
        return deletionsRequired;
    }
};
