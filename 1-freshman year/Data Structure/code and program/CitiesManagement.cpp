/*
*文件名称：				CitiesManagement.cpp
*项目名称：				线性表
*创建者：				谭哲文
*创建时间：				2023.4.6
*最后修改时间：			2023.4.26
*功能：					作为程序入口
*文件中的函数：主函数（与用户交互的控制），菜单函数（显示程序的功能序列）
*与其他文件的依赖关系：	需要头文件Citiesmanagement.h
*程序的目的和主要数据结构：
    1.目的是实现城市单链表的一系列操作
    2.主要使用的数据结构为单链表
*/

#include "Citiesmanagement.h"
using namespace std;

/*
 *函数名称：菜单函数
 *功能描述：清屏并显示菜单
 *预备条件：无
 *参数列表：无
 *后置条件：控制台显示菜单
 */
void menu()
{
    system("cls");
    cout << "******** 城市信息管理系统 *****" << endl;
    cout << "********* 1. 添加城市 *********" << endl;
    cout << "********* 2. 删除城市 *********" << endl;
    cout << "********* 3. 修改城市 *********" << endl;
    cout << "********* 4. 查询城市 *********" << endl;
    cout << "********* 5. 坐标查询 *********" << endl;
    cout << "********* 6. 退出程序 *********" << endl;
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
        cout << "请输入你的选择：";
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
            cout << "输入错误请重新输入" << endl;
            system("pause");
            goto begin;
        }
        }
        system("pause");
    }
}