struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//这个是最简单的方法了。 多么完美的代码。
TreeNode *createtree(TreeNode *root)
{
    int a;
    cin >> a;
    if (a != -1)
    {
        root = new TreeNode();
        root->val = a;
        root->left = createtree(root->left);
        root->right = createtree(root->right);
    }
    return root;
}

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
        if (cur)//弹出访问的时候压入其子节点，弹出一个 压入两个。
        {
            cout << cur->val << endl;
            stk.push(cur->right);
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

void postorder_stack(TreeNode *root)
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

        //如果当前元素是栈顶的左节点  就跳到右节点去。
        if (!stk.empty() && cur == stk.top()->left)
        {
            cur = stk.top()->right;
        }
        else
        {
            cur = nullptr; //这句太关键了啊。
        }
    }
}
//遍历次数 :2 中序遍历