#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<utility>
#include<cassert>
#include<climits>
#include<queue>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;


enum ErrorCode
{
    SUCCESS = 0,
    NOMORESPACE,
    EMPTY,
    VALUEERROR,
};


enum BalanceFactor
{
    rr = -2, r, b, l, ll
};


template<typename T>
struct BinaryNode
{
    T value;
    BinaryNode<T> *left_child, *right_child;
    int balance = b;
    unsigned height = 0;
    BinaryNode(T valuer, BinaryNode<T> *left_childr = NULL, BinaryNode<T> *right_childr = NULL):
        value(valuer), left_child(left_childr), right_child(right_childr){}
};

template<typename T>
class BinaryTree
{
    public:
        BinaryTree(){}

        ~BinaryTree()
        {
            if(!root) return;
            queue<BinaryNode<T> *> nodes;
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

        BinaryTree(BinaryTree &a);
        BinaryTree& operator=(const BinaryTree &a);

        // Other functions
        void insert(T &value);
        void remove(const T &value);
        BinaryNode<T>*  search(const T &value)const;

    private:
        BinaryNode<T> *root = NULL;
        unsigned numbers = 0;
        void search_and_destroy(BinaryNode<T> * &sub_root, const T &target, bool &shorter);
        void remove_root(BinaryNode<T> * &sub_roota, bool &shorter);
        void rotater(BinaryNode<T> *node);
        void rotatel(BinaryNode<T> *node);
        void rebalancel(BinaryNode<T> *node);
        void rebalancer(BinaryNode<T> *node);
        void recursive_insert(T &value, BinaryNode<T> *node, bool &taller);
};

template<typename T>
void BinaryTree<T>::insert(T &value)
{
    bool taller = false;
    if(root)
            recursive_insert(value, root, taller);
    else
        root = new BinaryNode<T>(value);
    numbers++;
}

template<typename T>
void BinaryTree<T>::remove(const T &value)
{
    bool shorter = false;
    search_and_destroy(root, value, shorter);
    numbers--;
    return;
}

template <class Record>
void BinaryTree<Record>::search_and_destroy
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
void BinaryTree<Record>::remove_root
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
BinaryNode<T>*  BinaryTree<T>::search(const T &value) const
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
void BinaryTree<T>::rotater(BinaryNode<T> *node)
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
void BinaryTree<T>::rotatel(BinaryNode<T> *node)
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
void BinaryTree<T>::rebalancer(BinaryNode<T> *node)
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
void BinaryTree<T>::rebalancel(BinaryNode<T> *node)
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
void BinaryTree<T>::recursive_insert(T &value, BinaryNode<T> *node, bool &tallera)
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


struct StyleIndex
{
    char name[15];
    double dis;
    int x, y;
    bool valid = false;
};



struct NameIndex
{
    char name[15];
    bool operator <(const NameIndex &a) const
    {
        return strcmp(name, a.name) < 0;
    }
    bool operator ==(const NameIndex &a) const
    {
        return strcmp(name, a.name) == 0;
    }
    bool operator >(const NameIndex &a) const
    {
        return strcmp(name, a.name) > 0;
    }
    bool operator <=(const NameIndex &a) const
    {
        return strcmp(name, a.name) <= 0;
    }
    bool operator >=(const NameIndex &a) const
    {
        return strcmp(name, a.name) >= 0;
    }
    bool operator !=(const NameIndex &a) const
    {
        return strcmp(name, a.name) != 0;
    }
};


struct StyleHead
{
    vector<StyleIndex> style_vector;
    char cooking_style[15];
    unsigned sort_by_distance
    (
        int start, int afterend,
        unsigned k,
        const unsigned &x, const unsigned &y
    );
    bool pos_greater(StyleIndex &a, StyleIndex &b,
                 const int &x, const int &y);
    bool operator <(const StyleHead &a) const
    {
        return strcmp(cooking_style, a.cooking_style) < 0;
    }
    bool operator ==(const StyleHead &a) const
    {
        return strcmp(cooking_style, a.cooking_style) == 0;
    }
    bool operator >(const StyleHead &a) const
    {
        return strcmp(cooking_style, a.cooking_style) > 0;
    }
    bool operator <=(const StyleHead &a) const
    {
        return strcmp(cooking_style, a.cooking_style) <= 0;
    }
    bool operator >=(const StyleHead &a) const
    {
        return strcmp(cooking_style, a.cooking_style) >= 0;
    }
    bool operator !=(const StyleHead &a) const
    {
        return strcmp(cooking_style, a.cooking_style) != 0;
    }
    protected:
        unsigned partition(int start, int afterend, unsigned k,
    const unsigned &x, const unsigned &y);
};


unsigned StyleHead::sort_by_distance
(
    int start, int afterend, unsigned k,
    const unsigned &x, const unsigned &y
)
{
    while(afterend - start <= 1)
    {
        unsigned random_number = rand() % (afterend - start) + start;
        unsigned pivot = random_number;
        pivot = partition(start, afterend, pivot, x, y);
        if(k == pivot)
            return k;
        else if(k < pivot)
            afterend = pivot;
        else
            start = pivot + 1;
    }
    return start;
}


unsigned StyleHead::partition(int start, int afterend, unsigned k,
    const unsigned &x, const unsigned &y)
{
    StyleIndex pivot = style_vector[k];
    style_vector[k] = style_vector[afterend - 1];
    style_vector[afterend - 1] = pivot;
    unsigned store_index = start;
    for(int i = start; i < afterend - 2; i++)
        if(pos_greater(pivot, style_vector[i], x, y))
        {
            StyleIndex temp = style_vector[i];
            style_vector[i] = style_vector[store_index];
            style_vector[store_index] = temp;
        }
    StyleIndex temp = style_vector[afterend-1];
    style_vector[afterend-1] = style_vector[store_index];
    style_vector[store_index] = temp;
    return store_index;
}


//void mysort(int start, int afterend)
//{
//    if(afterend - start <= 1) return;
//    int pivot = list[afterend-1];
//    list[afterend-1] = list[start];
//    list[start] = pivot;
//    int i = start + 1, j = afterend - 1;
//
//    while(i != j)
//    {
//        while(i != j && pivot >= list[i]) i++;
//        while(i != j && pivot < list[j]) j--;
//        int temp = list[i];
//        list[i] = list[j];
//        list[j] = temp;
//    }
//
//    if(list[i] <= pivot)
//    {
//        list[start] = list[i];
//        list[i] = pivot;
//        j++;
//    }
//    else
//    {
//        list[start] = list[i-1];
//        list[i-1] = pivot;
//        i--;
//    }
//    mysort(0, i);
//    mysort(j, afterend);
//    return;
//}


bool StyleHead::pos_greater(StyleIndex &a, StyleIndex &b,
                 const int &x, const int &y)
{
    if(!a.valid)
    {
        a.dis = floor(hypot(x - a.x, y - a.y) * 1000 + 0.5) / 1000;
        a.valid = true;
    }
    if(!b.valid)
    {
        b.dis = floor(hypot(x - b.x, y - b.y) * 1000 + 0.5) / 1000;
        b.valid = true;
    }
    if(a.dis != b.dis)
        return a.dis > b.dis;
    return strcmp(a.name, b.name) > 0;
}


//void name_insert
//(
// BinaryTree<NameIndex> &name_index,
// NameIndex &tmp_index,
// LinkedList<House> houses,
// unsigned pos
//)
//{
//    House entry;
//    scanf("%s%d%d%s", entry.name, &entry.x, &entry.y, entry.cooking_style);
//    memcpy(tmp_index.name, entry.name, sizeof(entry.name));
//    houses.insert(entry, pos);
//    tmp_index.p = &houses[pos] -> value;
//    name_index.insert(tmp_index);
//}


//void name_print(const BinaryTree<NameIndex> &name_index, NameIndex &tmp_index)
//{
//    scanf("%s", tmp_index.name);
//    const auto &p = name_index.search(tmp_index);
//    if(p)
//    {
//        auto &entry = *(p -> value.p);
//        printf("%u %u\n", entry.x, entry.y);
//    }
//    else
//        printf("\n");
//}


void style_insert
(
    BinaryTree<StyleHead> &style_heads,
    StyleIndex &tmp_index
)
{
    StyleHead tmp_head;
    scanf("%s %u %u %s", tmp_index.name, &(tmp_index.x), &(tmp_index.y),
            tmp_head.cooking_style);

    auto p = style_heads.search(tmp_head);

    if(p)
    {
        StyleHead &tmp_head = p -> value;
        tmp_head.style_vector.push_back(tmp_index);
    }
    else
    {
        tmp_head.style_vector.push_back(tmp_index);
        style_heads.insert(tmp_head);
    }
    return;
}


void style_print(const BinaryTree<StyleHead> &style_heads)
{
    int x, y;
    unsigned k;
    StyleHead tmp_head;
    scanf("%d%d%s%u", &x, &y, tmp_head.cooking_style, &k);
    auto p = style_heads.search(tmp_head);
    srand(time(NULL));
    if(p)
    {
        auto &tmp_head = p -> value;
        unsigned size = tmp_head.style_vector.size();
        tmp_head.sort_by_distance(0, size, x, y);
        unsigned limit = min(k, size);
        for(unsigned i = 0; i < limit; i++)
        {
            auto &entry = tmp_head.style_vector[i];
            printf("%s %.3f\n", entry.name, tmp_head.style_vector[i].dis);
        }
        for(unsigned i = 0; i < size; i++)
            tmp_head.style_vector[i].valid = false;
    }
    else
        printf("\n");
}


int main()
{
#ifdef debug
    freopen("testdata.in", "r", stdin);
    freopen("testdata.out", "w", stdout);
#endif

    unsigned m, n;
    BinaryTree<NameIndex> name_index;
    BinaryTree<StyleHead> style_heads;
    NameIndex tmp_index;
    StyleIndex style_tmp_index;
    scanf("%u%u", &m, &n);
    for(unsigned i = 0; i < m; i++)
    {
        //name_insert(name_index, tmp_index, houses, i);
        style_insert(style_heads, style_tmp_index);
    }

    while(n--)
    {
        //name_print(name_index, tmp_index);
        style_print(style_heads);
    }
    return 0;
}

