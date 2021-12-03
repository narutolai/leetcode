#ifndef __STL_RBTREE_H
#define __STL_RBTREE_H
/*
 * 红黑树是一种被广泛使用的平衡二叉搜索树
 * 每一个节点不是红色就是黑色
 * 根节点为黑色
 * 如果节点为红色则器子节点必须为黑色
 */
typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

//红黑树基本节点
struct __rb_tree_node_base
{
    typedef __rb_tree_color_type color_type;
    typedef __rb_tree_node_base *base_ptr;

    color_type color;
    base_ptr parent; //父指针
    base_ptr left;   //左指针
    base_ptr right;  //右指针

    static base_ptr minimum(base_ptr x)
    {
        while (x->left != 0)
            x = x->left;
        return x;
    }
    static base_ptr maximum(base_ptr x)
    {
        while (x->right != 0)
            x = x->right;
        return x;
    }
};

//真正使用的节点
template <class T>
struct __rb_tree_node : public __rb_tree_node_base
{
    //定义一种类型
    typedef __rb_tree_node<T> *link_type;
    T value_field; //节点值具体的对象吧
};

/*
rb-tree的迭代器很特殊，因为节点是有两层的，base和继承使用的，所以其迭代器也有两层
对rb_tree进行中序遍历会得到一个有序数组，所以begin()就是最小元素，最左侧节点
*/
//基层迭代器
struct __rb_tree_base_iterator
{
    //类型声明
    typedef __rb_tree_node_base::base_ptr base_ptr;
    typedef bidirectional_iterator_tag iterator_category;

    typedef ptrdiff_t difference_type;

    base_ptr node; //指向容器

    //这个就是++操作就是比当前节点值更大首个元素
    void increment()
    {
        if (node->right != 0) //如果当前节点有右子节点，那么++就是右节点的最左节点
        {
            node = node->right;
            while (node->left != 0)
                node = node->left;
        }
        else
        { //如果没有右节点 找其父节点
            base_ptr y = node->parent;
            //如果当前节点就是右节点 上溯 直到其不为右节点
            while (node == y->right)
            {
                node = y;
                y = y->parent;
            } /*
                    y
                node
            */
            if (node->right != y)
                node = y;
        }
    }
    //--操作的重载 比当前节点值小的首个元素
    void decrement()
    {
        //当node为header时 即end()时
        if (node->color == __rb_tree_red && node->parent->parent == node)
            node = node->right;
        else if (node->left != 0) //如果有左子节点 则左节点的最右边就是最小的
        {
            base_ptr y = node->left;
            while (y->right != 0)
                y = y->right;
            node = y;
        }
        else //既非根节点也无左子节点
        {
            base_ptr y = node->parent;
            while (node == y->left) //上溯 直到本身不为左子节点
            {
                node = y;
                y = y->parent;
            }
            node = y; //此时父节点就是答案
        }
    }
};

//RB-tree的正规迭代器
template <class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator
{
    typedef Value value_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef __rb_tree_iterator<Value, Value &, Value *> iterator;
    typedef __rb_tree_iterator<Value, const Value &, const Value *> const_iterator;
    typedef __rb_tree_iterator<Value> *link_type;

    __rb_tree_iterator() {}
    __rb_tree_iterator(link_type x) { node = x; }
    __rb_tree_iterator(const iterator &it) { node = it.node; }
    reference operator*() const { return link_type(node)->value_field; }
    pointer operator->() const { return &(operator*()); }

    self &operator++()
    {
        increment();
        return *this;
    }
    self operator++(int)
    {
        self tmp = *this;
        increment();
        return tmp;
    }
    self &operator--()
    {
        decrement();
        return *this;
    }
    self operator--(int)
    {
        self tmp = *this;
        decrement();
        return tmp;
    }
};
/*
为了实现方便 rb_TREE是有一个header()节点指向root节点的
rb-tree的数据结构
*/
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
class rb_tree
{
protected:
    typedef void *void_pointer;
    typedef __rb_tree_node_base *base_ptr;
    typedef __rb_tree_node<Value> rb_tree_node;
    typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
    typedef __rb_tree_black color_type;

public:
    typedef Key key_type;
    typedef Value value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef rb_tree_node *link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    link_type get_node() { return rb_tree_node_allocator::allocate(); }
    void put_node(link_type p) { rb_tree_node_allocator::deallocate(p); }

    link_type create_node(const value_type &x)
    {
        //配置空间
        link_type tmp = get_node();
        try
        { //构造内容
            construct(&tmp->value_field, x);
        }
        catch (const std::exception &e)
        {
            put_node(tmp);
            std::cerr << e.what() << '\n';
        }
        return tmp;
    }
    //复制一个节点
    link_type clone_node(link_type x)
    {
        link_type tmp = create_node(x->value_field);
        tmp->color = c->color;
        tmp->left = 0;
        tmp->right = 0;
        return tmp;
    }

    void destroy_node(link_type p)
    {
        destroy(&p->value_field);
        put_node(p);
    }

protected:
    //rb_tree仅仅有的三个成员
    size_type node_count; //节点数量
    link_type header;     //不是根节点 而是头节点，，这是一个实现上的技巧
    Compare key_compare;  //节点间的大小比较准则，应该会是个function object

    //以下6个函数用来方便取得节点x的成员
    static link_type &left(link_type x) { return (link_type &)(x->left); }
    static link_type &right(link_type x) { return (link_type &)(x->right); }
    static link_type &parent(link_type x) { return (link_type &)(x->parent); }
    static reference &value(link_type x) { return x->value_field; }
    static const Key &key(link_type x) { return (KeyOfValue)(value(x)); }
    static color_type &color(link_type x) { return (color_type &)(x->color); }

    //以下6个函数用来方便取得节点x的成员
    static link_type &left(base_ptr x) { return (link_type &)(x->left); }
    static link_type &right(base_ptr x) { return (link_type &)(x->right); }
    static link_type &parent(base_ptr x) { return (link_type &)(x->parent); }
    static reference &value(base_ptr x) { return ((link_type)x)->value_field; }
    static const Key &key(base_ptr x) { return (KeyOfValue)(value(link_type(x))); }
    static color_type &color(base_ptr x) { return (color_type &)(link_type(x)->color); }

    //求极大值和极小值
    static link_type minimum(link_type x)
    {
        return (link_type)__rb_tree_node_base::minimum(x);
    }
    static link_type maximum(link_type x)
    {
        return (link_type)__rb_tree_node_base::maximum(x);
    }

public:
    //终于在这里定义了迭代器
    typedef __rb_tree_iterator<value_type, reference, pointer> iterator;

private:
    iterator __insert(base_ptr x, base_ptr y, const value_type &v);
    link_type __copy(link_type x, link_type p);
    void __erase(link_type x);
    void init()
    {
        header = get_node(); //产生一个空节点 令header指向它
        //令header为红色 用来区分header和root root是黑色,在iterator.operator++
        color(header) = __rb_tree_red;
        root() = 0;
        leftmost() = header; //令其左节点为自己 令其右节点为自己
        rightmost() = header;
    }

public:
    rb_tree(const Compare &comp = Compare()) : node_count(0), key_compare(comp) { init(); }
    ~rb_tree()
    {
        clear();
        put_node();
    }
    //rb_tree<Key,Value,KeyOfValue,Compare,Alloc>&operator=()
public:
    Compare key_compare() const { return key_compare; }
    iterator begin() { return leftmost(); }
    //end为header
    iterator end() { return header; }
    bool empty() const { return node_count == 0; }
    size_type size() const { return node_count; }
    size_type max_size() const { return size_type(-1); }
    //header 和 root互为双放的父节点， header的左节点指向最小 右节点指向最大

    //rb-tree的元素操作
}

#endif