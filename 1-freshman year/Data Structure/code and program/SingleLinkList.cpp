/*
*文件名称：				SingleLinkList.cpp
*项目名称：				线性表
*创建者：				谭哲文
*创建时间：				2023.4.2
*最后修改时间：			2023.4.26
*功能：					作为程序入口
*文件中的函数：主函数（与用户交互的控制），菜单函数（显示程序的功能序列）
*与其他文件的依赖关系：	需要头文件SingleLinkList.h
*程序的目的和主要数据结构：
	1.目的是实现单链表的一系列操作
	2.主要使用的数据结构为单链表
*/

#include"SingleLinkList.h"
#include<cstdlib>
using namespace std;

/*
*函数名称：菜单
*功能描述：清屏并显示菜单
*预备条件：无
*参数列表：无
*后置条件：控制台显示菜单
*/
void showMenu()
{
	system("cls");//清屏

	cout << "单链表功能实现：" << endl;
	cout << "1.初始化" << endl;
	cout << "2.创建链表" << endl;
	cout << "3.销毁链表" << endl;
	cout << "4.遍历链表" << endl;
	cout << "5.在指定元素后面插入" << endl;
	cout << "6.按位置删除元素" << endl;
	cout << "7.获得链表表长" << endl;
	cout << "8.检查链表是否为空" << endl;    
	cout << "0.退出" << endl;                    
	cout << endl << "请输入您的选择：" << endl;
}

/*主函数*/
int main(void)
{
	LinkList* plist = NULL;
	while (true)
	{
		begin:
		/*显示菜单*/
		showMenu();
		/*读取用户输入*/
		int choose;
		cin >> choose;
		/*跳转相应功能*/
		switch (choose)
		{
			/*初始化*/
			case 1:
			{
				if (plist == NULL)
				{
					plist = new LinkList();
					cout << "初始化成功" << endl;
				}
				else
				{
					cout << "请先销毁当前链表";
				}
				break;
			}
			/*创建链表*/
			case 2:
			{
				if (plist != NULL)
				{
					cout << "请输入链表的长度：";
					int n;
					cin >> n;
					plist->CreateLinkList(n);
				}
				else
				{
					cout << "请先初始化" << endl;
				}
				break;
			}

			/*销毁链表*/
			case 3:
			{
				plist->DestroyLinkList();
				plist = NULL;
				break;
			}

			/*遍历链表*/
			case 4:
			{
				plist->TravalLinkList();
				break;
			}

			/*在指定元素后面插入*/
			case 5:
			{
				cout << "请输入要插入的值：";
				int c;
				cin >> c;
				Node temp;
				temp.data = c;
				temp.next = NULL;
				cout << "请输入要插入的位置：";
				int pos;
				cin >> pos;
-				plist->InsertLinklList(&temp, pos);
				break;
			}

			/*按位置删除元素*/
			case 6:
			{
				cout << "当前链表:" << endl;
				plist->TravalLinkList();
				cout << "请输入要删除元素的位置：";
				int pos;
				cin >> pos;
				plist->DeleteLinklist(pos);
				cout << "当前链表:" << endl;
				plist->TravalLinkList();
				break;
			}

			/*获得链表表长*/
			case 7:
			{
				if (plist != NULL)
				{
					cout << "当前链表长度:" << plist->GetLen() << endl;
				}
				else
				{
					cout << "请先初始化" << endl;
				}
				break;
			}

			/*检查链表是否为空*/
			case 8:
			{
				if (plist != NULL)
				{
					if (plist->IsEmply())
					{
						cout << "链表为空" << endl;
					}
					else
					{
						cout << "链表非空" << endl;
					}

				}
				else
				{
					cout << "请先初始化" << endl;
				}
				break;
			}
			/*退出程序*/
			case 0:
			{
				exit(0);
			}
			
			default:
			{
				cin.clear();
				cin.ignore();
				cout<<"输入错误请重新输入"<<endl;
				system("pause");
				goto begin;
			}
		}

		//暂停显示结果
		system("pause");
	}	
}