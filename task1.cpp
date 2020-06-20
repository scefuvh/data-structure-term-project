#include<cstdio>
#include "./include/name_index.h"
#include "./include/binary_search_tree.h"


void name_insert(BinarySearchTree<NameIndex> &name_index)
{
    NameIndex tmp_index;
    std::scanf("%s%d%d%s", tmp_index.name, &tmp_index.x, &tmp_index.y, tmp_index.cooking_style);
    name_index.insert(tmp_index);
}


void name_print(const BinarySearchTree<NameIndex> &name_index)
{
    NameIndex tmp_index;
    std::scanf("%s", tmp_index.name);
    const auto &p = name_index.search(tmp_index);
    if(p)
    {
        const auto &entry = p -> value;
        std::printf("%u %u\n", entry.x, entry.y);
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
    BinarySearchTree<NameIndex> name_index;
    std::scanf("%u%u", &m, &n);
    for(unsigned i = 0; i < m; i++)
        name_insert(name_index);

    while(n--)
        name_print(name_index);
    return 0;
}

