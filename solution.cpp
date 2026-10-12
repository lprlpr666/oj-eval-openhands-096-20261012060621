#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

struct NodeInfo {
    int depth;
    int parent;
};

// Global map to store node information
unordered_map<int, NodeInfo> nodeMap;

// Parse the extended binary tree from preorder traversal
// Returns the index of next element to process
int parseTree(const vector<int>& preorder, int index, int depth, int parent) {
    if (index >= preorder.size()) {
        return index;
    }
    
    int value = preorder[index];
    index++;
    
    if (value == -1) {
        // Null node, don't store anything
        return index;
    }
    
    // Store node information
    nodeMap[value] = {depth, parent};
    
    // Parse left subtree
    index = parseTree(preorder, index, depth + 1, value);
    
    // Parse right subtree
    index = parseTree(preorder, index, depth + 1, value);
    
    return index;
}

// Check if two nodes are cousins
bool areCousins(int x, int y) {
    if (nodeMap.find(x) == nodeMap.end() || nodeMap.find(y) == nodeMap.end()) {
        return false; // One or both nodes don't exist
    }
    
    NodeInfo infoX = nodeMap[x];
    NodeInfo infoY = nodeMap[y];
    
    return (infoX.depth == infoY.depth) && (infoX.parent != infoY.parent);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Read number of queries
    int q;
    cin >> q;
    
    // Read queries
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        queries.push_back({x, y});
    }
    
    // Read the entire remaining line as tree data
    vector<int> preorder;
    string line;
    
    // Read all remaining numbers (tree preorder traversal)
    while (cin >> line) {
        stringstream ss(line);
        int num;
        ss >> num;
        preorder.push_back(num);
    }
    
    // Parse the tree and build node information map
    parseTree(preorder, 0, 0, -1); // Root has depth 0 and parent -1
    
    // Answer queries
    for (const auto& query : queries) {
        if (areCousins(query.first, query.second)) {
            cout << 1 << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
    
    return 0;
}