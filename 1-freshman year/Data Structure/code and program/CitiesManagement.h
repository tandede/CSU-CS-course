/*
*文件名称：				Citiesmanagement.h
*项目名称：				线性表
*创建者：				谭哲文
*创建时间：				2023.4.6
*最后修改时间：			2023.4.26
*功能：					城市数据的初始化和城市相关信息的存储和计算
*文件中的类与结构体：   经纬度坐标结构体，城市类
*文件中的独立函数：     添加函数（用于添加新城市），删除函数（用于删除链表中已有城市），
                        更新函数（修改已有城市相关信息），显示函数（显示链表中已有所有城市）
                        范围函数（统计一定距离范围内的所有城市）
*与其他文件的依赖关系：	具体使用在Citiesmanagement.cpp文件中
*/
#pragma once
#include <iostream>
#include <string>
using namespace std;

// 构建城市链表
/**
 * 城市的属性：
 *  name：城市名
 *  area：城市的面积
 *  peopleCount：城市人口的数量
 *  top：城市的排行
 *  x：x轴距离
 *  y：y轴距离
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
 *函数名称：添加函数
 *功能描述：在链表插入一个新城市结点
 *预备条件：链表不为空
 *参数列表：待插入结点
 *后置条件：链表元素和长度发生改变
 */
void CityList::addCity()
{
    City *newCity = new City();
    City *temp = this->head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    cout << "----------- 添加一个城市 ----------" << endl;
    cout << "请输入城市名：";
    cin >> newCity->name;
    cout << "请输入面积（平方千米）：";
    cin >> newCity->area;
    cout << "请输入人口数(万人)：";
    cin >> newCity->peopleCount;
    cout << "请输入城市X坐标:";
    cin >> newCity->x;
    cout << "请输入城市y坐标:";
    cin >> newCity->y;
    cout << "请输入城市等级：[1-5]:";
    cin >> newCity->top;
    while (newCity->top > 5 || newCity->top < 1)
    {
        cin.clear();
        cin.ignore();
        cout << "城市等级输入错误,请重新输入：";
        cin >> newCity->top;
    }
    cout << endl;
    cout << "请输入城市特色：";
    cin >> newCity->feature;
    newCity->next = NULL;
    temp->next = newCity;
    cout << "添加成功!" << endl;
}

/*
 *函数名称：遍历函数
 *功能描述：从头到尾遍历结点并显示
 *预备条件：无
 *参数列表：无
 *后置条件：控制台显示链表所有城市
 */
int CityList::showCity()
{
    City *temp = head->next;
    if (temp == NULL)
    {
        cout << "城市为空，无法输出!" << endl;
        return -1;
    }
    cout << "---------- 正在生成城市清单 ---------" << endl;
    while (temp != NULL)
    {
        cout << "城市名：" << temp->name << endl;
        cout << "城市人口（万人）：" << temp->peopleCount << endl;
        cout << "城市面积（平方千米）：" << temp->area << endl;
        cout << "城市等级：" << temp->top << endl;
        cout << "城市X坐标：" << temp->x << endl;
        cout << "城市Y坐标：" << temp->y << endl;
        cout << "城市特色：" << temp->feature << endl;
        cout << "------------------------------" << endl;
        temp = temp->next;
    }
    return 0;
}

/*
 *函数名称：删除函数
 *功能描述：在指定位置删除一个已有城市
 *预备条件：指定位置不能大于表长也不能小于1
 *参数列表：无
 *返回值  ：删除成功输出0，删除失败输出-1
 *后置条件：链表元素和长度发生改变
 */
int CityList::delCity()
{
    if (this->head->next == NULL)
    {
        cout << "城市链表为空，请先添加城市。。。" << endl;
        return -1;
    }
    cout << "------------------------------" << endl;
    string cityName;
    char choose;
    cout << "请输入你要删除的城市名：";
    cin >> cityName;
    // 找到要删除城市的前一个城市
    City *ctemp = head;
    while (ctemp->next->name != cityName)
    {
        ctemp = ctemp->next;
        if (ctemp->next == NULL)
        {
            cout << "没有此城市" << endl;
            return -1;
        }
    }
    City *temp = head;      // 删除城市的前一个城市
    City *del = head->next; // 删除城市
    cout << "你将删除的城市信息：" << endl;
    cout << "城市名：" << del->name << endl;
    cout << "城市人口（万人）：" << del->peopleCount << endl;
    cout << "城市面积（平方千米）：" << del->area << endl;
    cout << "城市等级：" << del->top << endl;
    cout << "城市X坐标：" << del->x << endl;
    cout << "城市Y坐标：" << del->y << endl;
    cout << "城市特色：" << del->feature << endl;
    cout << "------------------------------" << endl;
    cout << "你确定要删除[Y-N]：";
    cin >> choose;
    if (choose == 'Y')
    {
        temp->next = del->next;
        free(del);
        cout << "删除成功" << endl;
        return 0;
    }
    else
    {
        cout << "删除取消" << endl;
        return -1;
    }
}

/*
 *函数名称：更新函数
 *功能描述：修改指定位置的城市信息
 *预备条件：链表不为空
 *参数列表：无
 *返回值  ：删除成功输出0，删除失败输出-1
 *后置条件：相应城市结点的内容改变
 */
int CityList::updateCity()
{
    if (this->head->next == NULL)
    {
        cout << "城市链表为空，请先添加城市。。。" << endl;
        return -1;
    }
    cout << "<--- 这里是修改城市信息服务! --->" << endl;
    string name;
    cout << "请输入你要修改城市的名字：";
    cin >> name;
    City *ctemp = head;
    while (ctemp->name != name)
    {
        ctemp = ctemp->next;
        if (ctemp == NULL)
        {
            cout << "没有此城市，将退出此功能。。。" << endl;
            return -1;
        }
    }
    cout << "----------- 修改城市信息 ----------" << endl;
    cout << "请输入城市名：";
    cin >> ctemp->name;
    cout << "请输入面积（平方千米）：";
    cin >> ctemp->area;
    cout << "请输入人口数(万人)：";
    cin >> ctemp->peopleCount;
    cout << "请输入城市X坐标:";
    cin >> ctemp->x;
    cout << "请输入城市y坐标:";
    cin >> ctemp->y;
    cout << "请输入城市等级：[1-5]:";
    cin >> ctemp->top;
    while (ctemp->top > 5 || ctemp->top < 1)
    {
        cout << "城市等级输入错误,请重新输入：";
        cin >> ctemp->top;
    }
    cout << "请输入城市特色：";
    cin >> ctemp->feature;
    cout << "******** 修改信息成功 ********" << endl;
    return 0;
}

/*
 *函数名称：范围函数
 *功能描述：统计一定距离范围内的所有城市
 *预备条件：链表不为空
 *参数列表：无
 *后置条件：链表不变
 */
void CityList::length()
{
    if (this->head->next == NULL)
    {
        cout << "城市链表为空，请先添加城市。。。" << endl;
        return;
    }
    City *cityList = head->next;
    cout << "********* 搜索范围之内的城市 *********" << endl;
    int x, y, D;
    cout << "请输入坐标：" << endl;
    cout << "x =";
    cin >> x;
    cout << "y =";
    cin >> y;
    cout << "请输入距离 D：";
    cin >> D;
    cout << "正在为你返回符合城市：" << endl;
    cout << "----------*************----------" << endl;
    int ads = 0;
    while (cityList != NULL)
    {
        if (((cityList->x - x) * (cityList->x - x)) + ((cityList->y - y) * (cityList->y - y)) <= D * D)
        {
            ads++;
            cout << "城市名：" << cityList->name << endl;
            cout << "城市人口（万人）：" << cityList->peopleCount << endl;
            cout << "城市面积（平方千米）：" << cityList->area << endl;
            cout << "城市等级：" << cityList->top << endl;
            cout << "城市X坐标：" << cityList->x << endl;
            cout << "城市Y坐标：" << cityList->y << endl;
            cout << "城市特色：" << cityList->feature << endl;
            cout << "------------------------------" << endl;
        }
        cityList = cityList->next;
    }
    if (ads == 0)
    {
        cout << "没有符合的城市" << endl;
    }
}
