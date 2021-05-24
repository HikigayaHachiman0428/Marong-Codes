//时态：考虑未来 只需考虑两个矿井中各两个最近食物，共计4个食物（A,B,C,D),由第一个食物车考虑至最后一辆
//F（i A,B；C,D ）当第i个物品被送入矿井时的考虑

// //处理垄余：
// 1. ABCD数据对调为同一情况 例：F（2,3;1,3）等价于F（1，3；2，3）
// 2. 将i-1所在的矿井视作主井，另外一个视为从井，从而只需要4个量（i,a;b,c）
// 3. 针对PURE FUNCTION 进行记忆化搜索
// 4. 用滚动数组应用食物车信息

// //转移方程:      F（i+1,si-1;b,c)+gain(si,si-1,a)
// F(i,a;b,c)=max{                                   当第i个食物车被输送时考虑第i+1个食物车
//                 F(i+1,b;c)

// //边界：
// 1. F(>n,0-3;0-3,0-3) 时return 0；即超出边界；
// 2. F(1,0;0,0) 为第一个时刻；
// 3. S[0]=0;

#include <iostream>
#include <algorithm>
using namespace std;
char s[300001];
int n;
int f[2][4][4][4];
int gain(int a, int b, int c)
{
    int ans = 0;
    if (a == 1 or b == 1 or c == 1)
        ans++;
    if (a == 2 or b == 2 or c == 2)
        ans++;
    if (a == 3 or b == 3 or c == 3)
        ans++;
    return ans;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {

        cin >> s[i];
        if (s[i] == 'M')
            s[i] = 1;
        if (s[i] == 'F')
            s[i] = 2;
        if (s[i] == 'B')
            s[i] = 3;
    }

    for (int i = n; i > 0; --i)
        for (int a = 0; a <= 3; a++)
            for (int b = 0; b <= 3; b++)
                for (int c = 0; c <= 3; c++)
                {
                    f[i % 2][a][b][c] = max(
                        f[(i + 1) % 2][s[i - 1]][b][c] + gain(s[i], s[i - 1], a),
                        f[(i + 1) % 2][b][s[i - 1]][a] + gain(s[i], b, c));
                }
    cout << f[1][0][0][0];
}