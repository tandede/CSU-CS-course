/*
*�ļ����ƣ�				JosephuesProblem.cpp
*��Ŀ���ƣ�				���Ա�
*�����ߣ�				̷����
*����ʱ�䣺				2023.4.7
*����޸�ʱ�䣺         2023.4.26
*���ܣ�					��Ϊ�������
*�ļ��еĺ�����			�����������û������Ŀ��ƣ�
*�������ļ���������ϵ��	��Ҫͷ�ļ�JosephuesProblem.h
*�����Ŀ�ĺ���Ҫ���ݽṹ��
	1.Ŀ����ʵ��Լɪ������
	2.��Ҫʹ�õ����ݽṹΪѭ��������
*/
#include"JosephuesProblem.h"
using namespace std;

int main()
{
	while(1)
	{int m, n;
	cout << "����������" << endl;
	cin >> n;
	cout << "�밴˳�������λ������" << endl;
	LinkList L = new LNode;
	if (L == NULL) {
		cout << "�ڴ���䲻�ɹ���" << endl;
	}
	else
	{
		L = Creat(n);
	}
	cout << "�������һ����������ֵ" << endl;
	cin >> m;
	cout << "����˳������" << endl;
	Circle(L, m, n);
	cout<<endl;
	system("pause");
	system("cls");
	}
}