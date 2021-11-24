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
////使用两个栈就行了，
//过程就是把s1的栈顶元素弹出压倒s2中去，但是把其子节点压回s1中去。在把s2的元素依次出栈就行了
    //后续遍历
    vector<int> postorder(Node *root)
    {
        stack<Node *> st1;
        stack<Node *> st2;
        vector<int> res;
        if (!root)
            return res;
        st1.push(root);
        while (!st1.empty())
        {
            Node *temp = st1.top();
            st1.pop();
            st2.push(temp);

            for (auto child : temp->children)
                st1.push(child);
        }
        while (!st2.empty())
        {
            Node *temp = st2.top();
            st2.pop();
            res.push_back(temp->val);
        }
        return res;
    }
    //前序遍历
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
            //为什么要reverse() 不能直接从最后一个往前遍历的吗
            reverse(cur->children.begin(), cur->children.end()); //
            for (auto p : cur->children)                         //入栈
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
};

//注意N叉树没有中序遍历  因为没有这个概念。
//前序要逆转 ，后续用两栈 弹出就是遍历时。