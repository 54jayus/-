#pragma once
#include <memory.h>
class DisjointSet
{
public:
    DisjointSet(int num)
    {
        this->size = num;
        this->parent = new int[size];
        memset(parent, -1, sizeof(parent));
    }
    //查找树根
    int simpleFind(int i)
    {
        //找到含元素i的树的根
        while (parent[i] >= 0)
            i = parent[i];
        return i;
    }
    //查找树跟（改进算法——坍塌规则）
    int collapsingFind(int i)
    {
        //找到含元素i的树的根
        int r;
        for (r = parent[i]; r >= 0; r = parent[r])
            ;          //找到树根
        while (i != r) // i以及i以上的所有结点，直接与树根相连接
        {
            int s = parent[i];
            parent[i] = r;
            i = s;
        }
        return r;
    }
    //合并集合(令第二棵树为第一棵树的子树)
    void simpleUnion(int i, int j)
    {
        parent[i] = j;
    }

    //合并集合(改进算法——以树种结点数为合并依据)
    void weightUnion(int i, int j)
    {
        //树中结点多的当爸爸
        //找到各自的树根
        i = simpleFind(i);
        j = simpleFind(j);
        int temp = parent[i] + parent[j];
        if (parent[i] < parent[j]) // i的节点多
        {
            parent[j] = i;
            parent[i] = temp;
        }
        else
        {
            parent[i] = j;
            parent[j] = temp;
        }
    }
    bool isConnect(int root1, int root2)
    {
        return collapsingFind(root1) == collapsingFind(root2);
    }
    ~DisjointSet()
    {
        delete[] parent;
    }

private:
    int size;
    int *parent;
}