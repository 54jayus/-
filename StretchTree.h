#include <iostream>
using namespace std;
struct node
{
    node *child[2], *parent;
    int val, weight;
    node(int key)
    {
        val = key;
        weight = 1;
        child[0] = child[1] = NULL;
    }
};

class StretchTree
{
public:
    void insert(int key)
    {
        node *cur = root;
        node *father = NULL;
        while (cur != NULL)
        {
            if (key == cur->val)
            {
                cur->weight++;
                splay(cur, NULL);
                return;
            }
            father = cur;
            if (key < cur->val)
                cur = cur->child[0];
            else
                cur = cur->child[1];
        }
        node *p = new node(key);
        p->parent = father;
        if (father == NULL)
            root = p;
        else if (key > father->val)
            father->child[1] = p;
        else
            father->child[0] = p;
        splay(p, NULL);
    }
    bool find(int key)
    {
        return find(root, key);
    }

    int getMinWave()
    {
        int left = 0;
        int right = 0;
        node *temp = root->child[0];
        while (temp != NULL && temp->child[1] != NULL)
            temp = temp->child[1];
        if (temp != NULL)
            left = temp->val;
        temp = root->child[1];
        while (temp != NULL && temp->child[0] != NULL)
            temp = temp->child[0];
        if (temp == NULL)
            return root->val - left;
        right = temp->val;
        left = root->val - left;
        right = right - root->val;
        if (left < right)
            return left;
        else
            return right;
    }
    void preErgodic()
    {
        this->preErodic(this->root);
    }

private:
    node *root;
    void preErodic(node *p)
    {
        if (p == NULL)
            return;
        cout << p->val << " ";
        this->preErodic(p->child[0]);
        this->preErodic(p->child[1]);
    }
    bool find(node *x, int key)
    {
        if (x == NULL)
            return false;
        if (x->val == key)
        {
            splay(x, NULL);
            return true;
        }
        else
        {
            if (x->val < key)
                return find(x->child[1], key);
            else
                return find(x->child[0], key);
        }
    }
    //将结点x调整到以结点y为双亲的位置上
    void splay(node *x, node *y)
    {
        while (x->parent != y)
        {
            if (x->parent->parent == y)                             // x的父节点的父节点为y，直接单旋转调整一次即可
                x->parent->child[0] == x ? turn(x, 1) : turn(x, 0); //单旋
            else if (x->parent->parent->child[0] == x->parent)      // L-形
            {
                if (x->parent->child[0] == x) // LL形
                {
                    turn(x->parent, 1); //父节点右旋一次
                    turn(x, 1);         // x右旋一次
                }
                else // LR形
                {
                    turn(x, 0); //先左旋
                    turn(x, 1); //再右旋
                }
            }
            else // R-形
            {
                if (x->parent->child[1] == x) // RR形
                {
                    turn(x->parent, 0); //父节点左旋一次
                    turn(x, 0);         // x左旋一次
                }
                else
                {               // RL形
                    turn(x, 1); //先右旋
                    turn(x, 0); //再左旋
                }
            }
        }
        if (y == NULL)
            root = x;
    }
    //单旋转,左旋 d=0   右旋 d=1
    void turn(node *x, int d)
    {
        node *y = x->parent;
        y->child[!d] = x->child[d];
        if (x->child[d]) //如果x结点的孩子存在，也应当将孩子的父节点连接到y
            x->child[d]->parent = y;
        x->parent = y->parent;
        if (y->parent) //如果y结点的父节点存在，也应当将父亲的孩子结点连接到x
        {
            if (y == y->parent->child[0])
                y->parent->child[0] = x;
            else
                y->parent->child[1] = x;
        }
        x->child[d] = y;
        y->parent = x;
    }
};
