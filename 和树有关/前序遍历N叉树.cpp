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

//使用一个栈就可以，先把根节点入栈,然后弹出其该节点，但是把其子节点逆序入栈。
//总之就是一弹 一入 。。。。。
class Solution {
    //  vector<int> result;
public:
    /*void dfs(Node *root){
        if(!root) return;
        result.push_back(root->val);
            for(auto p:root->children)
            {   
                preorder(p);
            }
    }*/
    vector<int> preorder(Node* root) {
      /*  dfs(root);
        return result;
        */
    //迭代方式
    if(!root) return {};
    stack<Node*> st;
    Node *cur;
    vector<int> result;
    st.push(root);

    while(!st.empty())
    {
         cur=st.top();          //取栈顶
         st.pop();               //弹出元素
         result.push_back(cur->val);
         reverse(cur->children.begin(),cur->children.end()) ; //
         for(auto p:cur->children)//入栈
         {
                st.push(p);
         }
    }
return result;

    }
};
