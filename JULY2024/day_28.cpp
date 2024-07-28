class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        // Create adjacency lists for all nodes
        vector<vector<int>> graph(n + 1);
        for (const vector<int>& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // Queue for breadth-first search (BFS)
        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({1, 0}); // Start from node 1 with distance 0

        // Initialize distances with two slots per node to store the two smallest distances
        vector<vector<int>> distances(n + 1, vector<int>(2, INT_MAX));
        distances[1][0] = 0; // Distance to the starting node is zero

        // Perform BFS
        while (!bfsQueue.empty()) {
            pair<int, int> nodeData = bfsQueue.front();
            bfsQueue.pop();
            int currentNode = nodeData.first;
            int currentDistance = nodeData.second;

            // Explore neighbors
            for (int neighbor : graph[currentNode]) {
                // Record smallest distance
                if (currentDistance + 1 < distances[neighbor][0]) {
                    distances[neighbor][1] = distances[neighbor][0]; // Update second smallest
                    distances[neighbor][0] = currentDistance + 1;    // Update smallest
                    bfsQueue.push({neighbor, currentDistance + 1});
                }
                // Record second smallest distance
                else if (distances[neighbor][0] < currentDistance + 1 &&
                        currentDistance + 1 < distances[neighbor][1]) {
                    distances[neighbor][1] = currentDistance + 1;
                    // No early break needed as we need to explore all paths thoroughly
                    bfsQueue.push({neighbor, currentDistance + 1});
                }
            }
        }

        // Calculate the total time to reach the destination node using the second smallest distance
        int totalTime = 0;
        for (int i = 0; i < distances[n][1]; ++i) {
            totalTime += time;
            // Adjust total time based on traffic signal change interval
            if (i < distances[n][1] - 1 && (totalTime / change) % 2 == 1) {
                totalTime += change - (totalTime % change);  // Wait for the green signal
            }
        }
        return totalTime;
    }
};
