#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Function to perform inorder traversal
void inorder(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    inorder(root->left, result);
    result.push_back(root->val);
    inorder(root->right, result);
}

// Function to swap left and right children of a node
void swapChildren(TreeNode* node) {
    if (node == nullptr) return;
    TreeNode* temp = node->left;
    node->left = node->right;
    node->right = temp;
}

// Function to compute depth of each node and store nodes by depth
void computeDepths(TreeNode* root, vector<vector<TreeNode*>>& nodesByDepth, int currentDepth) {
    if (root == nullptr) return;
    
    // Ensure the vector has enough space for this depth
    if (currentDepth >= nodesByDepth.size()) {
        nodesByDepth.resize(currentDepth + 1);
    }
    
    // Add current node to its depth level
    nodesByDepth[currentDepth].push_back(root);
    
    // Recursively process children
    computeDepths(root->left, nodesByDepth, currentDepth + 1);
    computeDepths(root->right, nodesByDepth, currentDepth + 1);
}

int main() {
    int n;
    cin >> n;
    
    // Create nodes
    vector<TreeNode*> nodes(n + 1);
    for (int i = 1; i <= n; i++) {
        nodes[i] = new TreeNode(i);
    }
    
    // Read children information
    for (int i = 1; i <= n; i++) {
        int left, right;
        cin >> left >> right;
        
        if (left != -1) {
            nodes[i]->left = nodes[left];
        }
        if (right != -1) {
            nodes[i]->right = nodes[right];
        }
    }
    
    // Precompute depths and store nodes by depth
    vector<vector<TreeNode*>> nodesByDepth;
    computeDepths(nodes[1], nodesByDepth, 1);  // Root is at depth 1
    
    int t;
    cin >> t;
    
    // Process each query
    for (int i = 0; i < t; i++) {
        int k;
        cin >> k;
        
        // For each depth that is a multiple of k, swap children of all nodes at that depth
        for (int depth = k; depth < nodesByDepth.size(); depth += k) {
            for (TreeNode* node : nodesByDepth[depth]) {
                swapChildren(node);
            }
        }
        
        // Get inorder traversal
        vector<int> result;
        inorder(nodes[1], result);
        
        // Output result
        for (int val : result) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    // Clean up memory
    for (int i = 1; i <= n; i++) {
        delete nodes[i];
    }
    
    return 0;
}