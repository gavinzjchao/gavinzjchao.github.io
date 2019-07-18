/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
	  // stack store in-order nodes from root to left most(the space is height of tree)
    BSTIterator(TreeNode* root) {
			while (root) {
				s.push(root);
				root = root->left;
			}
        
    }
    
    /** @return the next smallest number */
    int next() {
			int res = 0;
			if (!s.empty()) {
				TreeNode *cur = s.top();
				res = cur->val;
				s.pop();

				if (cur->right) {
					cur = cur->right;
					while (cur) {
						s.push(cur);
						cur = cur->left;
					}
				}
			}

			return res;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
			return !s.empty();
    }

		stack<TreeNode*> s;
};


/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

