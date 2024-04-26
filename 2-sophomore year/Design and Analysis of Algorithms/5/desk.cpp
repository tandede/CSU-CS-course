#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
    struct
    {
        int start;
        int end;
    } a[100];
    int i, j;
    int n, m, min, num, temp, used[100] = {0};
    cout << "Sample Input:\n";
    cin >> m >> n;
    for (i = 0; i < n; i++)
        cin >> a[i].start >> a[i].end;
    min = 0;
    num = 0;
    while (num < n)
    {
        temp = 0;
        for (i = 0; i < n; i++)
            if (used[i] == 0 && a[i].start >= temp)
            {
                temp = a[i].end;
                used[i] = 1;
                num++;
            }
        min++;
    }
    cout << "Sample Out:\n";
    cout << min << endl;
    system("pause");
}