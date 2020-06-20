#include<queue>
template<typename T>
BinaryNode<T>::BinaryNode(T valuer, BinaryNode<T> *left_childr, BinaryNode<T> *right_childr):
        value(valuer), left_child(left_childr), right_child(right_childr){}


template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    if(!root) return;
    std::queue<BinaryNode<T> *> nodes;
    nodes.push(root);
    while(!nodes.empty())
    {
        auto p = nodes.front();
        nodes.pop();
        if(p -> left_child)
            nodes.push(p -> left_child);
        if(p -> right_child)
            nodes.push(p -> right_child);
        delete p;
    }
    return;
}


template<typename T>
void BinarySearchTree<T>::insert(T &value)
{
    bool taller = false;
    if(root)
            recursive_insert(value, root, taller);
    else
        root = new BinaryNode<T>(value);
    numbers++;
}

template<typename T>
void BinarySearchTree<T>::remove(const T &value)
{
    bool shorter = false;
    search_and_destroy(root, value, shorter);
    numbers--;
    return;
}

template <class Record>
void BinarySearchTree<Record>::search_and_destroy
(
BinaryNode<Record> * &sub_root,
const Record &target,
bool &shortera
)
{
    bool &shorter = shortera;
    if(sub_root == NULL || sub_root -> value == target)
        remove_root(sub_root, shorter);
    else if(target < sub_root -> value)
    {
        search_and_destroy(sub_root -> left_child, target, shorter);
        /* Much in common with the insertion function.
         * But do notice that removal needs to keep
         * the shorter true when the balance factor of
         * sub_root is not balanced after changing.
         */
        if(shorter)
        {
            sub_root -> balance--;
            if(sub_root -> balance == rr)
                rebalancer(sub_root);
            if(sub_root -> balance != b)
                shorter = false;
        }
    }
    else
    {
        search_and_destroy(sub_root -> right_child, target, shorter);
        if(shorter)
        {
            sub_root -> balance++;
            if(sub_root -> balance == ll)
                rebalancel(sub_root);
            if(sub_root -> balance != b)
                shorter = false;
        }
    }
}

template<class Record>
void BinarySearchTree<Record>::remove_root
(
BinaryNode<Record> * &sub_roota,
bool &shortera
)
{
    bool &shorter = shortera;
    auto &sub_root = sub_roota;
    if(sub_root == NULL) return;
    BinaryNode<Record> *to_delete = sub_root;
    if(sub_root -> right_child == NULL)
    {
        sub_root = sub_root -> left_child;
        delete to_delete;
        shorter = true;
    }
    else if(sub_root -> left_child == NULL)
    {
        sub_root = sub_root -> right_child;
        delete to_delete;
        shorter = true;
    }
    else
    {
        to_delete = sub_root -> left_child;
        while(to_delete -> right_child)
            to_delete = to_delete -> right_child;
        auto temp = to_delete -> value;
        sub_root -> value = temp;
        /* Switch the node to be removed into the
         * to_delete node. So we can harness the
         * search_and_destroy function to change
         * balance factors.
         *
         * Note: since our rotation function does not
         * actually move the unbalanced node,
         * we can not change the value after removal
         * as the value to be replaced may be
         * moved away through rotation
         *
         * Of course to reduce the calls by 1 and
         * avoid exiting right away we just search
         * the left subress of sub_root.
         */
        search_and_destroy(sub_root -> left_child, temp, shorter);
        if(shorter)
        {
            sub_root -> balance--;
            if(sub_root -> balance == rr)
                rebalancer(sub_root);
            if(sub_root -> balance != b)
                shorter = false;
        }
    }
    return;
}

template<typename T>
BinaryNode<T>*  BinarySearchTree<T>::search(const T &value) const
{
    auto p = root;
    while(p && p -> value != value)
    {
        if(value < p -> value)
            p = p -> left_child;
        else
            p = p -> right_child;
    }
    return p;
}

template<typename T>
void BinarySearchTree<T>::rotater(BinaryNode<T> *node)
{
    auto future_node = node -> left_child;
    auto T1 = node -> right_child;
    auto T2 = future_node -> right_child;
    auto T3 = future_node -> left_child;
    T temp = node -> value;

    node -> value = future_node -> value;
    future_node -> value = temp;
    node -> right_child = future_node;
    node -> left_child = T3;
    future_node -> right_child = T1;
    future_node -> left_child = T2;
}

template<typename T>
void BinarySearchTree<T>::rotatel(BinaryNode<T> *node)
{
    auto future_node = node -> right_child;
    auto T1 = node -> left_child;
    auto T2 = future_node -> left_child;
    auto T3 = future_node -> right_child;
    T temp = node -> value;

    node -> value = future_node -> value;
    future_node -> value = temp;
    node -> left_child = future_node;
    node -> right_child = T3;
    future_node -> left_child = T1;
    future_node -> right_child = T2;
}


template<typename T>
void BinarySearchTree<T>::rebalancer(BinaryNode<T> *node)
{
    if(node -> right_child -> balance == l)
    {
        auto temp = node -> right_child -> left_child -> balance;
        rotater(node -> right_child);
        rotatel(node);
        switch(temp)
        {
            case r:
                node -> right_child -> balance = b;
                node -> left_child -> balance = l;
                break;
            case l:
                node -> right_child -> balance = r;
                node -> left_child -> balance = b;
                break;
            case b:
                node -> right_child -> balance = b;
                node -> left_child -> balance = b;
                break;
            default:
                break;
        }
        node -> balance = b;

    }
    else if(node -> right_child -> balance == b)
    {
        node -> balance = l;
        node -> right_child -> balance = r;
        rotatel(node);
    }
    else
    {
        node -> balance = b;
        node -> right_child -> balance = b;
        rotatel(node);
    }
}

template<typename T>
void BinarySearchTree<T>::rebalancel(BinaryNode<T> *node)
{
    if(node -> left_child -> balance == r)
    {
        auto temp = node -> left_child -> right_child -> balance;
        rotatel(node -> left_child);
        rotater(node);
        switch(temp)
        {
            case r:
                node -> right_child -> balance = b;
                node -> left_child -> balance = l;
                break;
            case l:
                node -> right_child -> balance = r;
                node -> left_child -> balance = b;
                break;
            case b:
                node -> right_child -> balance = b;
                node -> left_child -> balance = b;
                break;
            default:
                break;
        }
        node -> balance = b;
    }
    else if(node -> left_child -> balance == b)
    {
        node -> balance = r;
        node -> left_child -> balance = l;
        rotater(node);
    }
    else
    {
        node -> balance = b;
        node -> left_child -> balance = b;
        rotater(node);
    }
}


template<typename T>
void BinarySearchTree<T>::recursive_insert(T &value, BinaryNode<T> *node, bool &tallera)
{
    bool &taller = tallera;
    if(node -> value < value)
    {
        if(node -> right_child)
            recursive_insert(value, node -> right_child, taller);
        else
        {
            node -> right_child = new BinaryNode<T>(value);
            taller = true;
        }

        /* When taller is false, there is no need to
         * change anything.
         * When taller is true, it means the right
         * subress grows. So we should change the
         * balance factor and re-balance if needed.
         */
        if(taller)
        {
            node -> balance--;
            if(node -> balance == rr)
                rebalancer(node);
            if(node -> balance == b)
                taller = false;
        }
    }

    else
    {
        if(node -> left_child)
            recursive_insert(value, node -> left_child, taller);
        else
        {
            node -> left_child = new BinaryNode<T>(value);
            taller = true;
        }
        /* When taller is false, there is no need to
         * change anything as no height of both subtree
         * is influenced.
         *
         * When taller is true, it means the left
         * subress grows. So we should change the
         * balance factor and re-balance if needed.
         *
         * When the balance factor after changing
         * falls to b, it means the height of the
         * whole subtree is not influenced. Thus
         * the height of its ancestor tree is not
         * influenced as well.
         */
        if(taller)
        {
            node -> balance++;
            if(node -> balance == ll)
                rebalancel(node);
            if(node -> balance == b)
                taller = false;
        }
    }
    return;
}
