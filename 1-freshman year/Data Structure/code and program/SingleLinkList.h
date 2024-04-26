/*
*�ļ����ƣ�				SinglyLinkList.h
*��Ŀ���ƣ�				���Ա�
*�����ߣ�				̷����
*����ʱ�䣺				2023.4.5
*����޸�ʱ�䣺			2023.4.26
*���ܣ�					�������༰����������
*�ļ��е�����ṹ�壺	�����͵�������
*�������ļ���������ϵ��	����ʹ����SinglyLinkList.cpp�ļ���
*/

#pragma once
#include<iostream>
using namespace std;


typedef int DataType;/* �������������� */

/* �������� */
class Node
{
public:
	DataType data;/* ������ */
	Node* next;/* ָ���� */
};

/*
*�����ƣ�		  LinkList
*��������Ŀ�ģ����е��������ز���
*�����ԣ�		  ͷ���head
*���к��������ܣ�
*1.���캯���������������������������ͷ�����ռ�
*2.��������������һ������
*3.���뺯��������һ��Ԫ��
*4.ɾ��������ɾ��һ��Ԫ��
*5.���Һ���������Ԫ�ػ�λ��
*6.����������ȡ����ĳ��� 
*/

class LinkList
{
public:
	LinkList();
	~LinkList();
	int CreateLinkList(int size);
	int DestroyLinkList();
	int TravalLinkList();
	int InsertLinklList(Node* data, int n);
	int DeleteLinklist(int n);
	int GetLen();
	bool IsEmply();
private:
	Node* head;
	int size;
};

/*
*�������ƣ����캯��
*��������������һ����ͷ���Ŀյĵ��������洢��ͷ�����
*Ԥ����������
*�����б���
*��������������������
*/
LinkList::LinkList()
{
	head = new Node;
	head->data = 0;
	head->next = NULL;
	size = 0;/* ��ʼ����Ϊ0 */
}

/*
*�������ƣ���������
*�����������ͷ�������ռ�õĿռ�
*Ԥ����������
*�����б���
*���������������ռ��ͷ�
*/
LinkList::~LinkList()
{
	delete head;
}

/*
*�������ƣ���������
*��������������ͷ���β�巨��������
*Ԥ����������
*�����б���Ҫ������������n
*��������������������
*/
int LinkList::CreateLinkList(int n)
{
	if (n < 0) {
		printf("error\n");
		return -1;
	}
	Node* ptemp = NULL;
	Node* pnew = NULL;
	this->size = n;
	ptemp = this->head;
	for (int i = 0; i < n; i++)
	{
		pnew = new Node;
		pnew->next = NULL;
		cout << "�����" << i + 1 << "���ڵ�ֵ" << endl;
		cin >> pnew->data;
		ptemp->next = pnew;
		ptemp = pnew;
	}
	cout << "�������" << endl;
	return 0;
}

/*
*�������ƣ����ٺ���
*�����������ӵ�һ��㿪ʼ������ٴӶ���������
*Ԥ����������
*�����б���
*���������������ռ��ͷ�
*/
int LinkList::DestroyLinkList()
{
	Node* ptemp;
	if (this->head == NULL) 
	{
		cout << "����ԭ����Ϊ��" << endl;
		return -1;
	}
	while (this->head)
	{
		ptemp = head->next;
		free(head);
		head = ptemp;
	}
	cout << "�����������" << endl;
	return 0;
}

/*
*�������ƣ���������
*������������ͷ��β������㲢��ʾ
*Ԥ����������
*�����б���
*��������������̨��ʾ��������Ԫ��
*/
int LinkList::TravalLinkList()
{
	Node* ptemp = this->head->next;
	if (this->head == NULL) 
	{
		cout << "����Ϊ��" << endl;
		return -1;
	}
	while (ptemp)
	{
		cout << ptemp->data << "->";
		ptemp = ptemp->next;
	}
	cout << "NULL" << endl;
	return 0;
}

/*
*�������ƣ����뺯��
*������������ָ��λ�ò���һ��Ԫ��
*Ԥ������������Ϊ��
*�����б�������Ԫ�ء�ָ��λ�õ��±�
*����ֵ  ������ɹ����0������ʧ�����-1
*��������������Ԫ�غͳ��ȷ����ı�
*/
int LinkList::InsertLinklList(Node* data, int pos)
{
		Node* ptemp;
		if (this->head == NULL) 
		{
			cout << "����Ϊ��" << endl;
			return -1;
		}
		if (data == NULL) 
		{
			cout << "����ڵ�Ϊ��" << endl;
			return -1;
		}
		/*ͷ��*/
		if (pos < 2) 
		{
			Node* pnew = new Node;
			pnew->data = data->data;
			pnew->next = this->head->next;
			this->head->next = pnew;
			this->size++;
			cout << "����ɹ�" << endl;
			return 0;
		}
		/*β��*/
		if (pos == this->size) 
		{
			ptemp = this->head;
			while (ptemp->next != NULL) {
				ptemp = ptemp->next;
			}
			Node* pnew = new Node;
			pnew->data = data->data;
			pnew->next = NULL;
			ptemp->next = pnew;
			this->size++;
			cout << "����ɹ�" << endl;
			return 0;
		}
		/*�м���*/
		if(pos>=2&&pos<=this->size)  {
			ptemp = this->head;
			for (int i = 1; i < pos; i++) {
				ptemp = ptemp->next;
			}
			Node* pnew = new Node;
			pnew->data = data->data;
			pnew->next = ptemp->next;
			ptemp->next = pnew;
			this->size++;
			cout << "����ɹ�" << endl;
			return 0;
		}
		else
		{
			cout<<"����ʧ�ܣ��������ݲ���ȷ"<<endl;
		}
	
}

/*
*�������ƣ�ɾ������
*������������ָ��λ��ɾ��һ��Ԫ��
*Ԥ��������ָ��λ�ò��ܴ��ڱ�Ҳ����С��1
*�����б���
*����ֵ  ��ɾ���ɹ����0��ɾ��ʧ�����-1
*��������������̨��ʾ��������Ԫ��
*/
int LinkList::DeleteLinklist(int pos)
{
	Node* ptemp;
	Node* ptemp2;
	if (pos > 0 && pos > this->size) {
		cout << "pos���Ϸ�" << endl;
		return -1;
	}
	/*ͷɾ*/
	if (pos < 2) {
		ptemp = this->head->next;
		this->head->next = ptemp->next;
		free(ptemp);
		this->size--;
		return 0;
	}
	/*βɾ*/
	if (pos == this->size) {
		ptemp = this->head;
		for (int i = 1; i < this->size; i++) {
			ptemp = ptemp->next;
		}
		ptemp2 = ptemp->next;
		ptemp->next = NULL;
		free(ptemp2);
		this->size--;
		return 0;
	}
	/*�м�ɾ��*/
	else
	{
		ptemp = this->head;
		for (int i = 1; i < pos; i++) {
			ptemp = ptemp->next;
		}
		ptemp2 = ptemp->next;
		ptemp->next = ptemp2->next;
		free(ptemp2);
		this->size--;
		return 0;
	}
}

/*
*�������ƣ�������
*�������������������
*Ԥ����������
*�����б���
*����ֵ  ����
*������������
*/
int LinkList::GetLen()
{
	return this->size;
}

/*
*�������ƣ��пպ���
*�����������ж������Ƿ�Ϊ��
*Ԥ����������
*�����б���
*����ֵ  ��Ϊ�����1����Ϊ�����0
*������������
*/
bool LinkList::IsEmply()
{
	if (this->head == NULL) {
		return true;
	}
	else {
		return false;
	}
}