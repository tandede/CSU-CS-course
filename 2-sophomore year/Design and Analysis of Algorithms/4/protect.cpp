#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 1510;

int n;
int h[N], e[N], ne[N], idx, w[N];
int f[N][3];
bool st[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u)
{
    f[u][2] = w[u];

    int sum = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        dfs(j);
        f[u][0] += min(f[j][1], f[j][2]);
        f[u][2] += min(min(f[j][0], f[j][1]), f[j][2]);
        sum += min(f[j][1], f[j][2]);
    }

    f[u][1] = 1e9;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        f[u][1] = min(f[u][1], sum - min(f[j][1], f[j][2]) + f[j][2]);
    }
}

int main()
{
    cout << "Sample Input:" << endl;
    cin >> n;

    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++)
    {
        int id, cost, cnt;
        cin >> id >> cost >> cnt;
        w[id] = cost;
        while (cnt--)
        {
            int ver;
            cin >> ver;
            add(id, ver);
            st[ver] = true;
        }
    }

    int root = 1;
    while (st[root])
        root++;

    dfs(root);
    cout << "Sample Out:" << endl;
    cout << min(f[root][1], f[root][2]) << endl;

    system("pause");
    return 0;
}
