
//二叉树三种遍历方式的栈实现
void preorder_stack(TreeNode *root)
{
    stack<TreeNode *> stk;
    TreeNode *cur;
    stk.push(root);
    while (!stk.empty())
    {
        cur = stk.top();
        stk.pop();
        if (cur)
        {
            cout << cur->val << endl;
            stk.push(cur->right);//没错 就是先右边 后左边
            stk.push(cur->left);
        }
    }
}

void indorder_stack(TreeNode *root)
{
    TreeNode *cur = root;
    stack<TreeNode *> stk;
    while (cur || !stk.empty())
    {
        while (cur)
        {
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        cout << cur->val << endl;
        if (cur->right)
        {
            cur = cur->right;
        }
        else
        {
            cur = nullptr; //这个太关键了 不然会死循环的我靠
        }
    }
}
//后序遍历 要使用两个栈 其实是一个栈就可以了 最后把res逆转一就 可以了
vector<int> postorderTraversal(TreeNode *root)
{
    stack<TreeNode *> st1;
    stack<TreeNode *> st2;
    vector<int> res;
    if (!root)
        return res;
    st1.push(root);
    while (!st1.empty())
    {
        TreeNode *temp = st1.top();
        st1.pop();
        st2.push(temp);

        if (temp->left)
            st1.push(temp->left);
        if (temp->right)
            st1.push(temp->right);
    }
    while (!st2.empty())
    {
        TreeNode *temp = st2.top();
        st2.pop();
        res.push_back(temp->val);
    }
    return res;
}
