/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution
{
public:
    //后续遍历
    vector<int> postorder(Node *root)
    {
        stack<Node *> st1;
        vector<int> res;
        if (!root)
            return res;
        st1.push(root);
        while (!st1.empty())
        {
            Node *temp = st1.top();
            st1.pop();
            res.push_back(temp->val);

            for (auto child : temp->children)
                st1.push(child);
        }
        reverse(res.begin(), res.end());
        return res;
    }
    //前序遍历 前序后序 都只要使用一个栈和一个vector就行了
    vector<int> preorder(Node *root)
    {
        if (!root)
            return {};
        stack<Node *> st;
        Node *cur;
        vector<int> result;
        st.push(root);

        while (!st.empty())
        {
            cur = st.top(); //取栈顶
            st.pop();       //弹出元素
            result.push_back(cur->val);

            reverse(cur->children.begin(), cur->children.end());
            for (auto p : cur->children)
            {
                st.push(p);
            }
        }
        return result;
    }
    //层次遍历
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        queue<TreeNode *> qu;
        qu.push(root);
        TreeNode *cur;
        vector<vector<int>> result;
        if (!root)
            return result;
        while (!qu.empty())
        {
            int n = qu.size();
            vector<int> temp;
            for (int i = 0; i < n; i++)
            {
                cur = qu.front();
                qu.pop();
                temp.push_back(cur->val);

                if (cur->left)
                    qu.push(cur->left);
                if (cur->right)
                    qu.push(cur->right);
            }
            result.push_back(temp);
        }
        return result;
    }
    //二叉树的中序遍历 其实也是一个stack 和一个vec就搞定了
    vector<int> midOrder(TreeNode *root)
    {
        stack<TreeNode *> stk;
        TreeNode *cur = root;

        while (!skt.empty())
        {
            while (cur)
            {
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            res.push_back(cur->val);
            if (cur->right)
            {

                cur = cur->right;
            }
            else
            {
                cur = nullptr;
            }
        }
    }
};

//注意N叉树没有中序遍历  因为没有这个概念。
//前序要逆转 ，后续用两栈 弹出就是遍历时。