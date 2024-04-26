/*
 *�ļ����ƣ�				JosephuesProblem.h
 *��Ŀ���ƣ�				���Ա�
 *�����ߣ�				    ̷����
 *����ʱ�䣺				2023.4.7
 *����޸�ʱ�䣺            2023.4.26
 *���ܣ�					ѭ�������༰�������ṹ�������
 *�ļ��е�����ṹ�壺	    ���ṹ��
 *�ļ��еĶ���������		Լɪ����
 *�������ļ���������ϵ��	����ʹ����JosephuesProblem.cpp�ļ���
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
 *�������ƣ���������
 *��������������һ����СΪn��ѭ��������
 *Ԥ����������
 *�����б�ָ����Сn
 *��������������������
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
 *�������ƣ�Լɪ����
 *��������������ָ������ѭ��ɾ�����
 *Ԥ��������circle��βָ�벻��ΪNULL
 *�����б��������Ϊ��ʼ����m,ѭ������circle,���ڽ����
 *��������������̨������ʾ�˳����˺�����ʤ��
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
				 << "���ʤ����Ϊ��" << p->num;
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