#include <iostream>
using namespace std;
// 按照单位重量的价值量大小降序排列
void Sort(int n, float *w, float *v)
{
    int i, j;
    float temp1, temp2;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n - i; j++) // 冒泡排序
        {
            temp1 = v[j] / w[j];
            temp2 = v[j + 1] / w[j + 1];
            if (temp1 < temp2)
            {
                swap(w[j], w[j + 1]);
                swap(v[j], v[j + 1]);
            }
        }
}
int main()
{
    float w[101]; // 用来表示每个物品的重量
    float v[101]; // 用来表示每个物品的价值量
    float x[101]; // 表示最后放入背包的比例
    int n;        // 物品数
    float M;      // 背包最大容纳重量
    cout << "请输入物品数：" << endl;
    cin >> n;
    cout << "请输入最大容量：" << endl;
    cin >> M;
    // 依次输入每件物品的重量和价值量
    cout << "请依次输入每件物品的重量和价值量：" << endl;
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> v[i];
    // 按照单位重量的价值量大小降序排列
    Sort(n, w, v);
    int i;
    for (i = 1; i <= n; i++)
        x[i] = 0; // 初始值，未装入背包，x[i]=0
    float c = M;  // 更新背包容纳量
    for (i = 1; i <= n; i++)
    {
        if (c < w[i])
            break; // 不能完全装下
        x[i] = 1;
        c = c - w[i];
    }
    if (i <= n)
        x[i] = c / w[i];
    // 输出
    double sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cout << "重量为" << w[i] << "价值量为" << v[i] << "的物品"
             << "放入的比例为" << x[i] << endl;
        sum += x[i] * v[i];
    }
    cout << "总价值为：" << endl
         << sum<<endl;
    system("pause");
    return 0;
}
