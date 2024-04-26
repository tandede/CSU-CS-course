/*
*文件名称：				JosephuesProblem.cpp
*项目名称：				线性表
*创建者：				谭哲文
*创建时间：				2023.4.7
*最后修改时间：         2023.4.26
*功能：					作为程序入口
*文件中的函数：			主函数（与用户交互的控制）
*与其他文件的依赖关系：	需要头文件JosephuesProblem.h
*程序的目的和主要数据结构：
	1.目的是实现约瑟夫问题
	2.主要使用的数据结构为循环单链表
*/
#include"JosephuesProblem.h"
using namespace std;

int main()
{
	while(1)
	{int m, n;
	cout << "请输入人数" << endl;
	cin >> n;
	cout << "请按顺序输入各位的密码" << endl;
	LinkList L = new LNode;
	if (L == NULL) {
		cout << "内存分配不成功！" << endl;
	}
	else
	{
		L = Creat(n);
	}
	cout << "请给定第一个报数上限值" << endl;
	cin >> m;
	cout << "出列顺序如下" << endl;
	Circle(L, m, n);
	cout<<endl;
	system("pause");
	system("cls");
	}
}