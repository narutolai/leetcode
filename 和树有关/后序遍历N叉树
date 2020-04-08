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
//使用两个栈就行了，
//过程就是把s1的栈顶元素弹出压倒s2中去，但是把其子节点压回s1中去。在把s2的元素依次出栈就行了。
class Solution {
public:
    vector<int> postorder(Node* root) {
        stack<Node*> st1;
        stack<Node*> st2;
        vector<int> res;
        if(!root) return res;
        st1.push(root);
        while(!st1.empty())
        {
            Node *temp=st1.top();
            st1.pop();
            st2.push(temp);

            for(auto child:temp->children)
             st1.push(child);
        }
        while(!st2.empty())
        {
            Node *temp=st2.top();
            st2.pop();
            res.push_back(temp->val);
        }
        return res;
    }
};
