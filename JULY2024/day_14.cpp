/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 726. Number of Atoms

Given a string formula representing a chemical formula, return the count of each atom.

The atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.

One or more digits representing that element's count may follow if the count is greater than 1. If the count is 1, no digits will follow.

For example, "H2O" and "H2O2" are possible, but "H1O2" is impossible.
Two formulas are concatenated together to produce another formula.

For example, "H2O2He3Mg4" is also a formula.
A formula placed in parentheses, and a count (optionally added) is also a formula.

For example, "(H2O2)" and "(H2O2)3" are formulas.
Return the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.

The test cases are generated so that all the values in the output fit in a 32-bit integer.

 

Example 1:

Input: formula = "H2O"
Output: "H2O"
Explanation: The count of elements are {'H': 2, 'O': 1}.
Example 2:

Input: formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
Example 3:

Input: formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.
 

Constraints:

1 <= formula.length <= 1000
formula consists of English letters, digits, '(', and ')'.
formula is always valid.
*/

class Solution {
    int N;
    int readNum(string &s, int &i) {
        int cnt = 0;
        while (i < N && isdigit(s[i])) cnt = cnt * 10 + (s[i++] - '0');
        return cnt ? cnt : 1;
    }
    map<string, int> dfs(string &s, int &i, bool isInParens = false) {
        map<string, int> m;
        if (isInParens) ++i;
        while (i < N && s[i] != ')') {
            if (s[i] == '(') {
                auto mm = dfs(s, i, true);
                for (auto &p : mm) m[p.first] += p.second;
            } else {
                string symbol = string(1, s[i++]);
                while (i < N && islower(s[i])) symbol += s[i++];
                m[symbol] += readNum(s, i);
            }
        }
        if (isInParens) {
            ++i;
            int cnt = readNum(s, i);
            for (auto &p : m) p.second *= cnt;
        }
        return m;
    }
public:
    string countOfAtoms(string formula) {
        N = formula.size();
        int i = 0;
        auto m = dfs(formula, i);
        string ans;
        for (auto &p : m) ans += p.first + (p.second > 1 ? to_string(p.second) : "");
        return ans;
    }
};
