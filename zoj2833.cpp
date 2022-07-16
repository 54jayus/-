// https://zoj.pintia.cn/problem-sets/91827364500/problems/91827366332
/*Sample Input:
3 5
M 1 2
Q 1
Q 3
M 2 3
Q 2
5 10
M 3 2
Q 4
M 1 2
Q 4
M 3 2
Q 1
M 3 1
Q 5
M 4 2
Q 4

Sample Output:
Case 1:
2
1
3

Case 2:
1
1
3
1
4
*/
#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <fstream>
using namespace std;
class DisjointSet
{
public:
    DisjointSet(int num)
    {
        this->size = num;
        this->parent = new int[num];
        for (int i = 0; i < this->size; i++)
        {
            parent[i] = -1;
        }
    }
    int find(int i)
    {
        while (parent[i] >= 0)
            i = parent[i];
        return i;
    }
    void Union(int i, int j)
    {
        if (isFriend(i, j))
            return;
        i = find(i);
        j = find(j);
        int temp = parent[i] + parent[j];
        if (parent[i] > parent[j])
        {
            parent[i] = j;
            parent[j] = temp;
        }
        else
        {

            parent[j] = i;
            parent[i] = temp;
        }
    }
    int getFriendNums(int i)
    {
        i = find(i);
        return -parent[i];
    }
    ~DisjointSet()
    {
        delete[] parent;
    }
    bool isFriend(int i, int j)
    {
        return find(i) == find(j);
    }

private:
    int size;
    int *parent;
};
int main()
{
    int questino_num, people_num;
    int time = 0;
    char flag;
    // ofstream ofs;
    // ofs.open("2833output.txt");
    while (scanf("%d%d", &people_num, &questino_num)!=EOF)
    {
        if(time)
			printf("\n");
		time++;
        printf("Case %d:\n", time);
        // ofs << "Case " << time << ":"<<endl;
        DisjointSet set(people_num);
        while (questino_num)
        {
            scanf(" %c", &flag);
            int people1, people2;
            if (flag == 'M')
            {
                scanf("%d%d", &people1, &people2);
                set.Union(people1 - 1, people2 - 1);
            }
            else if (flag == 'Q')
            {
                scanf("%d", &people1);
                printf("%d\n", set.getFriendNums(people1 - 1));
                // ofs << set.getFriendNums(people1 - 1)<<endl;
            }
            questino_num--;
        }
        
    }
    system("pause");
    return 0;
}
