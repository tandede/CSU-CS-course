/*
*�ļ����ƣ�				Citiesmanagement.h
*��Ŀ���ƣ�				���Ա�
*�����ߣ�				̷����
*����ʱ�䣺				2023.4.6
*����޸�ʱ�䣺			2023.4.26
*���ܣ�					�������ݵĳ�ʼ���ͳ��������Ϣ�Ĵ洢�ͼ���
*�ļ��е�����ṹ�壺   ��γ������ṹ�壬������
*�ļ��еĶ���������     ��Ӻ�������������³��У���ɾ������������ɾ�����������г��У���
                        ���º������޸����г��������Ϣ������ʾ��������ʾ�������������г��У�
                        ��Χ������ͳ��һ�����뷶Χ�ڵ����г��У�
*�������ļ���������ϵ��	����ʹ����Citiesmanagement.cpp�ļ���
*/
#pragma once
#include <iostream>
#include <string>
using namespace std;

// ������������
/**
 * ���е����ԣ�
 *  name��������
 *  area�����е����
 *  peopleCount�������˿ڵ�����
 *  top�����е�����
 *  x��x�����
 *  y��y�����
 */
class City
{
public:
    string name;
    double area;
    int peopleCount;
    int top;
    int x;
    int y;
    string feature;
    City *next;
};

class CityList
{
public:
    CityList();
    void addCity();
    int showCity();
    int delCity();
    int updateCity();
    void length();

private:
    City *head;
};
inline CityList::CityList()
{
    head = new City;
    head->next = NULL;
}

/*
 *�������ƣ���Ӻ���
 *�������������������һ���³��н��
 *Ԥ������������Ϊ��
 *�����б���������
 *��������������Ԫ�غͳ��ȷ����ı�
 */
void CityList::addCity()
{
    City *newCity = new City();
    City *temp = this->head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    cout << "----------- ���һ������ ----------" << endl;
    cout << "�������������";
    cin >> newCity->name;
    cout << "�����������ƽ��ǧ�ף���";
    cin >> newCity->area;
    cout << "�������˿���(����)��";
    cin >> newCity->peopleCount;
    cout << "���������X����:";
    cin >> newCity->x;
    cout << "���������y����:";
    cin >> newCity->y;
    cout << "��������еȼ���[1-5]:";
    cin >> newCity->top;
    while (newCity->top > 5 || newCity->top < 1)
    {
        cin.clear();
        cin.ignore();
        cout << "���еȼ��������,���������룺";
        cin >> newCity->top;
    }
    cout << endl;
    cout << "�����������ɫ��";
    cin >> newCity->feature;
    newCity->next = NULL;
    temp->next = newCity;
    cout << "��ӳɹ�!" << endl;
}

/*
 *�������ƣ���������
 *������������ͷ��β������㲢��ʾ
 *Ԥ����������
 *�����б���
 *��������������̨��ʾ�������г���
 */
int CityList::showCity()
{
    City *temp = head->next;
    if (temp == NULL)
    {
        cout << "����Ϊ�գ��޷����!" << endl;
        return -1;
    }
    cout << "---------- �������ɳ����嵥 ---------" << endl;
    while (temp != NULL)
    {
        cout << "��������" << temp->name << endl;
        cout << "�����˿ڣ����ˣ���" << temp->peopleCount << endl;
        cout << "���������ƽ��ǧ�ף���" << temp->area << endl;
        cout << "���еȼ���" << temp->top << endl;
        cout << "����X���꣺" << temp->x << endl;
        cout << "����Y���꣺" << temp->y << endl;
        cout << "������ɫ��" << temp->feature << endl;
        cout << "------------------------------" << endl;
        temp = temp->next;
    }
    return 0;
}

/*
 *�������ƣ�ɾ������
 *������������ָ��λ��ɾ��һ�����г���
 *Ԥ��������ָ��λ�ò��ܴ��ڱ�Ҳ����С��1
 *�����б���
 *����ֵ  ��ɾ���ɹ����0��ɾ��ʧ�����-1
 *��������������Ԫ�غͳ��ȷ����ı�
 */
int CityList::delCity()
{
    if (this->head->next == NULL)
    {
        cout << "��������Ϊ�գ�������ӳ��С�����" << endl;
        return -1;
    }
    cout << "------------------------------" << endl;
    string cityName;
    char choose;
    cout << "��������Ҫɾ���ĳ�������";
    cin >> cityName;
    // �ҵ�Ҫɾ�����е�ǰһ������
    City *ctemp = head;
    while (ctemp->next->name != cityName)
    {
        ctemp = ctemp->next;
        if (ctemp->next == NULL)
        {
            cout << "û�д˳���" << endl;
            return -1;
        }
    }
    City *temp = head;      // ɾ�����е�ǰһ������
    City *del = head->next; // ɾ������
    cout << "�㽫ɾ���ĳ�����Ϣ��" << endl;
    cout << "��������" << del->name << endl;
    cout << "�����˿ڣ����ˣ���" << del->peopleCount << endl;
    cout << "���������ƽ��ǧ�ף���" << del->area << endl;
    cout << "���еȼ���" << del->top << endl;
    cout << "����X���꣺" << del->x << endl;
    cout << "����Y���꣺" << del->y << endl;
    cout << "������ɫ��" << del->feature << endl;
    cout << "------------------------------" << endl;
    cout << "��ȷ��Ҫɾ��[Y-N]��";
    cin >> choose;
    if (choose == 'Y')
    {
        temp->next = del->next;
        free(del);
        cout << "ɾ���ɹ�" << endl;
        return 0;
    }
    else
    {
        cout << "ɾ��ȡ��" << endl;
        return -1;
    }
}

/*
 *�������ƣ����º���
 *�����������޸�ָ��λ�õĳ�����Ϣ
 *Ԥ������������Ϊ��
 *�����б���
 *����ֵ  ��ɾ���ɹ����0��ɾ��ʧ�����-1
 *������������Ӧ���н������ݸı�
 */
int CityList::updateCity()
{
    if (this->head->next == NULL)
    {
        cout << "��������Ϊ�գ�������ӳ��С�����" << endl;
        return -1;
    }
    cout << "<--- �������޸ĳ�����Ϣ����! --->" << endl;
    string name;
    cout << "��������Ҫ�޸ĳ��е����֣�";
    cin >> name;
    City *ctemp = head;
    while (ctemp->name != name)
    {
        ctemp = ctemp->next;
        if (ctemp == NULL)
        {
            cout << "û�д˳��У����˳��˹��ܡ�����" << endl;
            return -1;
        }
    }
    cout << "----------- �޸ĳ�����Ϣ ----------" << endl;
    cout << "�������������";
    cin >> ctemp->name;
    cout << "�����������ƽ��ǧ�ף���";
    cin >> ctemp->area;
    cout << "�������˿���(����)��";
    cin >> ctemp->peopleCount;
    cout << "���������X����:";
    cin >> ctemp->x;
    cout << "���������y����:";
    cin >> ctemp->y;
    cout << "��������еȼ���[1-5]:";
    cin >> ctemp->top;
    while (ctemp->top > 5 || ctemp->top < 1)
    {
        cout << "���еȼ��������,���������룺";
        cin >> ctemp->top;
    }
    cout << "�����������ɫ��";
    cin >> ctemp->feature;
    cout << "******** �޸���Ϣ�ɹ� ********" << endl;
    return 0;
}

/*
 *�������ƣ���Χ����
 *����������ͳ��һ�����뷶Χ�ڵ����г���
 *Ԥ������������Ϊ��
 *�����б���
 *����������������
 */
void CityList::length()
{
    if (this->head->next == NULL)
    {
        cout << "��������Ϊ�գ�������ӳ��С�����" << endl;
        return;
    }
    City *cityList = head->next;
    cout << "********* ������Χ֮�ڵĳ��� *********" << endl;
    int x, y, D;
    cout << "���������꣺" << endl;
    cout << "x =";
    cin >> x;
    cout << "y =";
    cin >> y;
    cout << "��������� D��";
    cin >> D;
    cout << "����Ϊ�㷵�ط��ϳ��У�" << endl;
    cout << "----------*************----------" << endl;
    int ads = 0;
    while (cityList != NULL)
    {
        if (((cityList->x - x) * (cityList->x - x)) + ((cityList->y - y) * (cityList->y - y)) <= D * D)
        {
            ads++;
            cout << "��������" << cityList->name << endl;
            cout << "�����˿ڣ����ˣ���" << cityList->peopleCount << endl;
            cout << "���������ƽ��ǧ�ף���" << cityList->area << endl;
            cout << "���еȼ���" << cityList->top << endl;
            cout << "����X���꣺" << cityList->x << endl;
            cout << "����Y���꣺" << cityList->y << endl;
            cout << "������ɫ��" << cityList->feature << endl;
            cout << "------------------------------" << endl;
        }
        cityList = cityList->next;
    }
    if (ads == 0)
    {
        cout << "û�з��ϵĳ���" << endl;
    }
}
