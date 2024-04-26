/*
*�ļ����ƣ�				SingleLinkList.cpp
*��Ŀ���ƣ�				���Ա�
*�����ߣ�				̷����
*����ʱ�䣺				2023.4.2
*����޸�ʱ�䣺			2023.4.26
*���ܣ�					��Ϊ�������
*�ļ��еĺ����������������û������Ŀ��ƣ����˵���������ʾ����Ĺ������У�
*�������ļ���������ϵ��	��Ҫͷ�ļ�SingleLinkList.h
*�����Ŀ�ĺ���Ҫ���ݽṹ��
	1.Ŀ����ʵ�ֵ������һϵ�в���
	2.��Ҫʹ�õ����ݽṹΪ������
*/

#include"SingleLinkList.h"
#include<cstdlib>
using namespace std;

/*
*�������ƣ��˵�
*������������������ʾ�˵�
*Ԥ����������
*�����б���
*��������������̨��ʾ�˵�
*/
void showMenu()
{
	system("cls");//����

	cout << "��������ʵ�֣�" << endl;
	cout << "1.��ʼ��" << endl;
	cout << "2.��������" << endl;
	cout << "3.��������" << endl;
	cout << "4.��������" << endl;
	cout << "5.��ָ��Ԫ�غ������" << endl;
	cout << "6.��λ��ɾ��Ԫ��" << endl;
	cout << "7.��������" << endl;
	cout << "8.��������Ƿ�Ϊ��" << endl;    
	cout << "0.�˳�" << endl;                    
	cout << endl << "����������ѡ��" << endl;
}

/*������*/
int main(void)
{
	LinkList* plist = NULL;
	while (true)
	{
		begin:
		/*��ʾ�˵�*/
		showMenu();
		/*��ȡ�û�����*/
		int choose;
		cin >> choose;
		/*��ת��Ӧ����*/
		switch (choose)
		{
			/*��ʼ��*/
			case 1:
			{
				if (plist == NULL)
				{
					plist = new LinkList();
					cout << "��ʼ���ɹ�" << endl;
				}
				else
				{
					cout << "�������ٵ�ǰ����";
				}
				break;
			}
			/*��������*/
			case 2:
			{
				if (plist != NULL)
				{
					cout << "����������ĳ��ȣ�";
					int n;
					cin >> n;
					plist->CreateLinkList(n);
				}
				else
				{
					cout << "���ȳ�ʼ��" << endl;
				}
				break;
			}

			/*��������*/
			case 3:
			{
				plist->DestroyLinkList();
				plist = NULL;
				break;
			}

			/*��������*/
			case 4:
			{
				plist->TravalLinkList();
				break;
			}

			/*��ָ��Ԫ�غ������*/
			case 5:
			{
				cout << "������Ҫ�����ֵ��";
				int c;
				cin >> c;
				Node temp;
				temp.data = c;
				temp.next = NULL;
				cout << "������Ҫ�����λ�ã�";
				int pos;
				cin >> pos;
-				plist->InsertLinklList(&temp, pos);
				break;
			}

			/*��λ��ɾ��Ԫ��*/
			case 6:
			{
				cout << "��ǰ����:" << endl;
				plist->TravalLinkList();
				cout << "������Ҫɾ��Ԫ�ص�λ�ã�";
				int pos;
				cin >> pos;
				plist->DeleteLinklist(pos);
				cout << "��ǰ����:" << endl;
				plist->TravalLinkList();
				break;
			}

			/*��������*/
			case 7:
			{
				if (plist != NULL)
				{
					cout << "��ǰ������:" << plist->GetLen() << endl;
				}
				else
				{
					cout << "���ȳ�ʼ��" << endl;
				}
				break;
			}

			/*��������Ƿ�Ϊ��*/
			case 8:
			{
				if (plist != NULL)
				{
					if (plist->IsEmply())
					{
						cout << "����Ϊ��" << endl;
					}
					else
					{
						cout << "����ǿ�" << endl;
					}

				}
				else
				{
					cout << "���ȳ�ʼ��" << endl;
				}
				break;
			}
			/*�˳�����*/
			case 0:
			{
				exit(0);
			}
			
			default:
			{
				cin.clear();
				cin.ignore();
				cout<<"�����������������"<<endl;
				system("pause");
				goto begin;
			}
		}

		//��ͣ��ʾ���
		system("pause");
	}	
}