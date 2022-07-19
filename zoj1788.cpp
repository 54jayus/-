// https://zoj.pintia.cn/problem-sets/91827364500/problems/91827365287
#include <iostream>
#include <queue>
using namespace std;
#include <memory.h>
class QuadTree
{
public:
    string value;
    QuadTree *child[4];
    QuadTree()
    {
        value = "0";
        child[0] = child[1] = child[2] = child[3] = NULL;
    }
    bool operator==(const QuadTree &p) const
    {
        if (value == p.value)
            return true;
        else
            return false;
    }
};
QuadTree *root;
char MAP[520][520];
string ans;
int N, a[2500];
//输入数据初始化
void init()
{
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> MAP[i][j];
    ans = "";
}

QuadTree *DFS(int r, int c, int len)
{
    bool flag = true;
    QuadTree *temp = new QuadTree;
    if (len == 1)
    {
        temp->value += MAP[r][c];
        return temp;
    }
    len /= 2;
    temp->child[0] = DFS(r, c, len);
    temp->child[1] = DFS(r, c + len, len);
    temp->child[2] = DFS(r + len, c, len);
    temp->child[3] = DFS(r + len, c + len, len);
    // value=="00"说明该区域全为0，设置为叶子节点
    // value=="01"说明该区域全为1，设置为叶子节点
    for (int i = 1; i < 4; i++)
        if (!(*temp->child[0] == *temp->child[i]))
        {
            flag = false;
            break;
        }
    //如果四个节点完全相同，则删除四个节点，用父节点代替
    if (flag)
    {
        temp->value = temp->child[0]->value;
        for (int i = 0; i < 4; i++)
        {
            delete temp->child[i];
            temp->child[i] = NULL;
        }
    }
    // value="1"说明该区域该能在分，该节点有四个孩子节点
    else
        temp->value = "1";
    return temp;
}
void funtion(char bin[])
{
    int sum = 0;
    //得到4位二进制对应的十进制
    for (int i = 0; i < 4; i++)
        sum = 2 * sum + bin[i];
    // hex：以十六进制的形式输出（字母为小写）
    // uppercase：以大写形式输出字母
    cout << hex << uppercase << sum;
}

void print()
{
    char str[5];
    QuadTree *temp;
    queue<QuadTree *> q;
    q.push(root);
    //层次遍历四分树
    while (!q.empty())
    {
        temp = q.front();
        q.pop();
        ans += temp->value; //将层次遍历的value值加入至ans中
        // cout << temp->value << endl;
        //如果第一个子节点不为空，说明该节点非叶子节点，必定存在四个子节点
        if (temp->child[0] != NULL)
        {
            for (int i = 0; i < 4; i++)
                q.push(temp->child[i]);
        }
        delete temp;
    }
    //如果层序遍历后得到的字符串不满足4位二进制数一组
    if (ans.size() % 4 != 0)
    {
        int i = ans.size() % 4;
        // i为余数，i==1则前补三个0，i==2则前补两个0，i==1则前补一个0
        ans.insert(0, 4 - i, '0'); // insert三个参数 pos：前插的位置    n：插入的个数   c：插入的字符
    }
    for (int i = 0; i < ans.size(); i += 4)
    {
        for (int j = 0; j < 4; j++)
            str[j] = ans[i + j] - '0';
        funtion(str);
    }

    cout << endl;
}
int main()
{
    int input;
    cin >> input;
    while (input--)
    {
        init();
        root = DFS(0, 0, N);
        print();
    }
    system("pause");
    return 0;
}

//nXn的二维数组