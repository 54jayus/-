// #include <iostream>
// #include "E:\code\new\StretchTree.h"
// using namespace std;

// /*
// 10
// 23 46 71 15 58 66 12 46 25 89
// */
// StretchTree s;
// int main()
// {
//     int input;
//     int sell = 0;
//     long long int wave_sum = 0;
//     cin >> input;
//     cin >> sell;
//     s.insert(sell);
//     wave_sum += sell;
//     for (int i = 1; i < input; i++)
//     {
//         cin >> sell;
//         if (s.find(sell))
//             continue;
//         s.insert(sell);
//         // cout<<s.getMinWave()<<endl;
//         s.preErgodic();
//         cout<<endl;
//         wave_sum += s.getMinWave();
//     }
//     cout << wave_sum << endl;
//     system("pause");
//     return 0;
// }
