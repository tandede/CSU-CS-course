#include <iostream>
#include <string>
#include <stack>
using namespace std;
void LCS(string s1, string s2)
{
    int m = s1.length() + 1;
    int n = s2.length() + 1;
    int** c;
    int** b;
    c = new int* [m];
    b = new int* [m];
    for (int i = 0; i < m; i++)
    {
        c[i] = new int[n];
        b[i] = new int[n];
        for (int j = 0; j < n; j++)
            b[i][j] = 0;
    }
    for (int i = 0; i < m; i++)
        c[i][0] = 0;
    for (int i = 0; i < n; i++)
        c[0][i] = 0;
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (s1[i] == s2[j])
            {
                c[i + 1][j + 1] = c[i][j] + 1;
                b[i + 1][j + 1] = 1;          
            }
            else if (c[i][j + 1] >= c[i + 1][j])
            {
                c[i + 1][j + 1] = c[i][j + 1];
                b[i + 1][j + 1] = 2;          
            }
            else
            {
                c[i + 1][j + 1] = c[i + 1][j];
                b[i + 1][j + 1] = 3;          
            }
        }
    }
    for (int i = 0; i < m; i++)                //���c����
    {
        for (int j = 0; j < n; j++)
        {
            cout << c[i][j] << ' ';
        }
        cout << endl;
    }
    stack<char> same;                   //��LCS�ַ�
    stack<int> same1, same2;             //��LCS�ַ����ַ���1���ַ���2�ж�Ӧ���±꣬������ʾ����
    for (int i = m - 1, j = n - 1; i >= 0 && j >= 0; )
    {
        if (b[i][j] == 1)
        {
            i--;
            j--;
            same.push(s1[i]);
            same1.push(i);
            same2.push(j);
        }
        else if (b[i][j] == 2)
            i--;
        else
            j--;
    }
    cout << s1 << endl;                     //����ַ���1
    for (int i = 0; i < m && !same1.empty(); i++)      //����ַ���1�ı��
    {
        if (i == same1.top())
        {
            cout << 1;
            same1.pop();
        }
        else
            cout << ' ';
    }
    cout << endl << s2 << endl;                //����ַ���2
    for (int i = 0; i < n && !same2.empty(); i++)      //����ַ���2�ı��
    {
        if (i == same2.top())
        {
            cout << 1;
            same2.pop();
        }
        else
            cout << ' ';
    }
    cout << endl << "�����������Ϊ��";
    while (!same.empty())
    {
        cout << same.top();
        same.pop();
    }
    cout << endl << "����Ϊ��" << c[m - 1][n - 1] << endl;
    for (int i = 0; i < m; i++)
    {
        delete[] c[i];
        delete[] b[i];
    }
    delete[]c;
    delete[]b;
}
int main()
{
    string s1 = "ABCPDSFJGODIHJOFDIUSHGD";
    string s2 = "OSDIHGKODGHBLKSJBHKAGHI";
    LCS(s1, s2);
    system("pause");
    return 0;
}