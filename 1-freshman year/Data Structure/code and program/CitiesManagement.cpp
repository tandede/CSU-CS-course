/*
*�ļ����ƣ�				CitiesManagement.cpp
*��Ŀ���ƣ�				���Ա�
*�����ߣ�				̷����
*����ʱ�䣺				2023.4.6
*����޸�ʱ�䣺			2023.4.26
*���ܣ�					��Ϊ�������
*�ļ��еĺ����������������û������Ŀ��ƣ����˵���������ʾ����Ĺ������У�
*�������ļ���������ϵ��	��Ҫͷ�ļ�Citiesmanagement.h
*�����Ŀ�ĺ���Ҫ���ݽṹ��
    1.Ŀ����ʵ�ֳ��е������һϵ�в���
    2.��Ҫʹ�õ����ݽṹΪ������
*/

#include "Citiesmanagement.h"
using namespace std;

/*
 *�������ƣ��˵�����
 *������������������ʾ�˵�
 *Ԥ����������
 *�����б���
 *��������������̨��ʾ�˵�
 */
void menu()
{
    system("cls");
    cout << "******** ������Ϣ����ϵͳ *****" << endl;
    cout << "********* 1. ��ӳ��� *********" << endl;
    cout << "********* 2. ɾ������ *********" << endl;
    cout << "********* 3. �޸ĳ��� *********" << endl;
    cout << "********* 4. ��ѯ���� *********" << endl;
    cout << "********* 5. �����ѯ *********" << endl;
    cout << "********* 6. �˳����� *********" << endl;
    cout << "*******************************" << endl;
}

int main()
{
begin:
    int select;
    CityList *cityList = new CityList();
    while (1)
    {
        menu();
        cout << "���������ѡ��";
        cin >> select;

        switch (select)
        {
        case 1:
            cityList->addCity();
            break;
        case 2:
            cityList->delCity();
            break;
        case 3:
            cityList->updateCity();
            break;
        case 4:
            cityList->showCity();
            break;
        case 5:
            cityList->length();
            break;
        default:
        {
            cin.clear();
            cin.ignore();
            cout << "�����������������" << endl;
            system("pause");
            goto begin;
        }
        }
        system("pause");
    }
}