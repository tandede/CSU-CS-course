/*
 *文件名称：				JosephuesProblem.h
 *项目名称：				线性表
 *创建者：				    谭哲文
 *创建时间：				2023.4.7
 *最后修改时间：            2023.4.26
 *功能：					循环链表类及结点变量结构体的声明
 *文件中的类与结构体：	    结点结构体
 *文件中的独立函数：		约瑟夫函数
 *与其他文件的依赖关系：	具体使用在JosephuesProblem.cpp文件中
 */

#pragma once
#include <iostream>
using namespace std;

typedef struct lnode
{
	int data;
	int num;
	struct lnode *next;
} LNode, *LinkList;

/*
 *函数名称：创建函数
 *功能描述：创建一个大小为n的循环单链表
 *预备条件：无
 *参数列表：指定大小n
 *后置条件：堆区链表创建
 */
LinkList Creat(int n)
{
	LinkList L = NULL;
	LNode *s, *r = NULL;
	int x;
	for (int i = 1; i <= n; i++)
	{
		LNode *s = new LNode;
		cin >> x;
		s->data = x;
		s->num = i;
		if (L == NULL)
			L = s;
		else
			r->next = s;
		r = s;
	}
	if (r != NULL)
		r->next = L;
	return L;
}

/*
 *函数名称：约瑟夫函数
 *功能描述：根据指定数字循环删除结点
 *预备条件：circle的尾指针不能为NULL
 *参数列表：输入参数为初始密码m,循环链表circle,表内结点数
 *后置条件：控制台依次显示退出的人和最后的胜者
 */
void Circle(LinkList &H, int m, int n)
{
	LinkList q, p = H;
	for (int j = 1; j <= n; j++)
	{
		for (int i = 1; i < m; i++)
		{
			p = p->next;
		}
		m = p->data;
		if (p->next == p)
		{
			cout << endl
				 << "最后胜利者为：" << p->num;
		}
		else
			cout << p->num << " ";
		q = p->next;
		p->num = q->num;
		p->data = q->data;
		p->next = q->next;

		free(q);
	}
}