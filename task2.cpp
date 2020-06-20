#include<cstdio>
#include<cmath>
#include "./include/binary_search_tree.h"
#include "./include/style_class.h"
#define min(x, y) ((x) < (y) ? (x) : (y))


void style_insert(BinarySearchTree<StyleHead> &style_heads)
{
    StyleIndex tmp_index;
    StyleHead tmp_head;
    std::scanf("%s %u %u %s", tmp_index.name, &(tmp_index.x), &(tmp_index.y),
            tmp_head.cooking_style);
    auto p = style_heads.search(tmp_head);
    if(p)
    {
        StyleHead &head_ref = p -> value;
        head_ref.style_vector.push_back(tmp_index);
    }
    else
    {
        tmp_head.style_vector.push_back(tmp_index);
        style_heads.insert(tmp_head);
    }
    return;
}


void style_print(const BinarySearchTree<StyleHead> &style_heads)
{
    int x, y;
    unsigned k;
    StyleHead tmp_head;
    scanf("%d%d%s%u", &x, &y, tmp_head.cooking_style, &k);
    auto p = style_heads.search(tmp_head);
    if(p)
    {
        StyleHead &head_ref = p -> value;
        unsigned size = head_ref.style_vector.size();
        unsigned limit = min(k, size);
        for(unsigned i = 0; i < size; i++)
        {
            StyleIndex &index_ref = head_ref.style_vector[i];
            index_ref.dis = floor(hypot(x - index_ref.x, y - index_ref.y) * 1000 + 0.5) / 1000;
        }
        head_ref.pick_kth_nearest(0, size, limit - 1);
        head_ref.sort(0, limit);
        for(unsigned i = 0; i < limit; i++)
        {
            auto &entry = head_ref.style_vector[i];
            std::printf("%s %.3f\n", entry.name, head_ref.style_vector[i].dis);
        }
    }
    else
        std::printf("\n");
}


int main()
{
#ifdef debug
    freopen("testdata.in", "r", stdin);
    freopen("testdata.out", "w", stdout);
#endif

    unsigned m, n;
    BinarySearchTree<StyleHead> style_heads;
    std::scanf("%u%u", &m, &n);
    for(unsigned i = 0; i < m; i++)
        style_insert(style_heads);
    while(n--)
        style_print(style_heads);
    return 0;
}

