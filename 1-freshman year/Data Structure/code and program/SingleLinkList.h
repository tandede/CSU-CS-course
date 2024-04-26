/*
*文件名称：				SinglyLinkList.h
*项目名称：				线性表
*创建者：				谭哲文
*创建时间：				2023.4.5
*最后修改时间：			2023.4.26
*功能：					单链表类及结点类的声明
*文件中的类与结构体：	结点类和单链表类
*与其他文件的依赖关系：	具体使用在SinglyLinkList.cpp文件中
*/

#pragma once
#include<iostream>
using namespace std;


typedef int DataType;/* 重命名数据类型 */

/* 定义结点类 */
class Node
{
public:
	DataType data;/* 数据域 */
	Node* next;/* 指针域 */
};

/*
*类名称：		  LinkList
*定义该类的目的：进行单链表的相关操作
*类属性：		  头结点head
*类中函数及功能：
*1.构造函数与析构函数：创建空链表与释放链表空间
*2.创建函数：创建一个链表
*3.插入函数：插入一个元素
*4.删除函数：删除一个元素
*5.查找函数：查找元素或位置
*6.表长函数：获取链表的长度 
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
*函数名称：构造函数
*功能描述：创建一个带头结点的空的单链表，表长存储在头结点中
*预备条件：无
*参数列表：无
*后置条件：堆区链表创建
*/
LinkList::LinkList()
{
	head = new Node;
	head->data = 0;
	head->next = NULL;
	size = 0;/* 初始化表长为0 */
}

/*
*函数名称：析构函数
*功能描述：释放链表所占用的空间
*预备条件：无
*参数列表：无
*后置条件：堆区空间释放
*/
LinkList::~LinkList()
{
	delete head;
}

/*
*函数名称：创建函数
*功能描述：利用头结点尾插法创建链表
*预备条件：无
*参数列表：需要创建的链表长度n
*后置条件：堆区链表创建
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
		cout << "输入第" << i + 1 << "个节点值" << endl;
		cin >> pnew->data;
		ptemp->next = pnew;
		ptemp = pnew;
	}
	cout << "创建完成" << endl;
	return 0;
}

/*
*函数名称：销毁函数
*功能描述：从第一结点开始逐个销毁从而销毁链表
*预备条件：无
*参数列表：无
*后置条件：堆区空间释放
*/
int LinkList::DestroyLinkList()
{
	Node* ptemp;
	if (this->head == NULL) 
	{
		cout << "链表原本就为空" << endl;
		return -1;
	}
	while (this->head)
	{
		ptemp = head->next;
		free(head);
		head = ptemp;
	}
	cout << "销毁链表完成" << endl;
	return 0;
}

/*
*函数名称：遍历函数
*功能描述：从头到尾遍历结点并显示
*预备条件：无
*参数列表：无
*后置条件：控制台显示链表所有元素
*/
int LinkList::TravalLinkList()
{
	Node* ptemp = this->head->next;
	if (this->head == NULL) 
	{
		cout << "链表为空" << endl;
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
*函数名称：插入函数
*功能描述：在指定位置插入一个元素
*预备条件：链表不为空
*参数列表：待插入元素、指定位置的下标
*返回值  ：插入成功输出0，插入失败输出-1
*后置条件：链表元素和长度发生改变
*/
int LinkList::InsertLinklList(Node* data, int pos)
{
		Node* ptemp;
		if (this->head == NULL) 
		{
			cout << "链表为空" << endl;
			return -1;
		}
		if (data == NULL) 
		{
			cout << "插入节点为空" << endl;
			return -1;
		}
		/*头插*/
		if (pos < 2) 
		{
			Node* pnew = new Node;
			pnew->data = data->data;
			pnew->next = this->head->next;
			this->head->next = pnew;
			this->size++;
			cout << "插入成功" << endl;
			return 0;
		}
		/*尾插*/
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
			cout << "插入成功" << endl;
			return 0;
		}
		/*中间后插*/
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
			cout << "插入成功" << endl;
			return 0;
		}
		else
		{
			cout<<"插入失败，输入数据不正确"<<endl;
		}
	
}

/*
*函数名称：删除函数
*功能描述：在指定位置删除一个元素
*预备条件：指定位置不能大于表长也不能小于1
*参数列表：无
*返回值  ：删除成功输出0，删除失败输出-1
*后置条件：控制台显示链表所有元素
*/
int LinkList::DeleteLinklist(int pos)
{
	Node* ptemp;
	Node* ptemp2;
	if (pos > 0 && pos > this->size) {
		cout << "pos不合法" << endl;
		return -1;
	}
	/*头删*/
	if (pos < 2) {
		ptemp = this->head->next;
		this->head->next = ptemp->next;
		free(ptemp);
		this->size--;
		return 0;
	}
	/*尾删*/
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
	/*中间删除*/
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
*函数名称：表长函数
*功能描述：获得链表长度
*预备条件：无
*参数列表：无
*返回值  ：表长
*后置条件：无
*/
int LinkList::GetLen()
{
	return this->size;
}

/*
*函数名称：判空函数
*功能描述：判断链表是否为空
*预备条件：无
*参数列表：无
*返回值  ：为空输出1，不为空输出0
*后置条件：无
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