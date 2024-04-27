import requests
import re
import time
import csv
from bs4 import BeautifulSoup
import pandas as pd
import matplotlib.pyplot as plt
import pandas as pd
string_num='202306'
num_num = int (string_num[4:6])
month=[0,31,28,31,30,31,30,31,31,30,31,30,31]
url=f'http://lishi.tianqi.com/huhehaote/{string_num}.html'
headers={'User-Agent':'Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36',
            'Cookie':'lianjia_uuid=9d3277d3-58e4-440e-bade-5069cb5203a4; UM_distinctid=16ba37f7160390-05f17711c11c3e-454c0b2b-100200-16ba37f716618b; _smt_uid=5d176c66.5119839a; sensorsdata2015jssdkcross=%7B%22distinct_id%22%3A%2216ba37f7a942a6-0671dfdde0398a-454c0b2b-1049088-16ba37f7a95409%22%2C%22%24device_id%22%3A%2216ba37f7a942a6-0671dfdde0398a-454c0b2b-1049088-16ba37f7a95409%22%2C%22props%22%3A%7B%22%24latest_traffic_source_type%22%3A%22%E7%9B%B4%E6%8E%A5%E6%B5%81%E9%87%8F%22%2C%22%24latest_referrer%22%3A%22%22%2C%22%24latest_referrer_host%22%3A%22%22%2C%22%24latest_search_keyword%22%3A%22%E6%9C%AA%E5%8F%96%E5%88%B0%E5%80%BC_%E7%9B%B4%E6%8E%A5%E6%89%93%E5%BC%80%22%7D%7D; _ga=GA1.2.1772719071.1561816174; Hm_lvt_9152f8221cb6243a53c83b956842be8a=1561822858; _jzqa=1.2532744094467475000.1561816167.1561822858.1561870561.3; CNZZDATA1253477573=987273979-1561811144-%7C1561865554; CNZZDATA1254525948=879163647-1561815364-%7C1561869382; CNZZDATA1255633284=1986996647-1561812900-%7C1561866923; CNZZDATA1255604082=891570058-1561813905-%7C1561866148; _qzja=1.1577983579.1561816168942.1561822857520.1561870561449.1561870561449.1561870847908.0.0.0.7.3; select_city=110000; lianjia_ssid=4e1fa281-1ebf-e1c1-ac56-32b3ec83f7ca; srcid=eyJ0Ijoie1wiZGF0YVwiOlwiMzQ2MDU5ZTQ0OWY4N2RiOTE4NjQ5YmQ0ZGRlMDAyZmFhODZmNjI1ZDQyNWU0OGQ3MjE3Yzk5NzFiYTY4ODM4ZThiZDNhZjliNGU4ODM4M2M3ODZhNDNiNjM1NzMzNjQ4ODY3MWVhMWFmNzFjMDVmMDY4NWMyMTM3MjIxYjBmYzhkYWE1MzIyNzFlOGMyOWFiYmQwZjBjYjcyNmIwOWEwYTNlMTY2MDI1NjkyOTBkNjQ1ZDkwNGM5ZDhkYTIyODU0ZmQzZjhjODhlNGQ1NGRkZTA0ZTBlZDFiNmIxOTE2YmU1NTIxNzhhMGQ3Yzk0ZjQ4NDBlZWI0YjlhYzFiYmJlZjJlNDQ5MDdlNzcxMzAwMmM1ODBlZDJkNmIwZmY0NDAwYmQxNjNjZDlhNmJkNDk3NGMzOTQxNTdkYjZlMjJkYjAxYjIzNjdmYzhiNzMxZDA1MGJlNjBmNzQxMTZjNDIzNFwiLFwia2V5X2lkXCI6XCIxXCIsXCJzaWduXCI6XCIzMGJlNDJiN1wifSIsInIiOiJodHRwczovL2JqLmxpYW5qaWEuY29tL3p1ZmFuZy9yY28zMS8iLCJvcyI6IndlYiIsInYiOiIwLjEifQ=='
            }

def get_page(url,headers):
    html=requests.get(url,headers=headers)
    if html.status_code==200:
        html.encoding=html.apparent_encoding
        return html.text
    else:
        return None
date_box=[]
max_temp=[]
min_temp=[]
weh=[]
wind=[]
week_box=[]
tem_low=[]
tem_high=[]
html=get_page(url,headers)
bs=BeautifulSoup(html,'html.parser')
data=bs.find_all(class_='thrui')
date=re.compile('class="th200">(.*?)</')
tem=re.compile('class="th140">(.*?)</')
time=re.findall(date,str(data))
for item in time:
    week=item[10:]
    week_box.append(week)
    date_box.append(item[:10])
temp=re.findall(tem, str(data))
for i in range(month[num_num]):
    max_temp.append(temp[i*4+0])
    min_temp.append(temp[i*4+1])
    weh.append(temp[i*4+2])
    wind.append(temp[i*4+3])
datas=pd.DataFrame({'日期':date_box,'星期':week_box,'最高温度':max_temp,'最低温度':min_temp,'天气':weh,'风向':wind})
# print(datas)


path=r'C:/Users/Dell/Desktop/code/python/lishitianqi.csv'
colsname = ['日期',  '最高温度','最低温度','天气',  '风向风力',  '星期',]
 # 写入数据到临时数据文件
with open(path, 'w', newline='', encoding='utf-8') as wf:
        writer = csv.writer(wf)
        writer.writerow(colsname)
        for i in range(0,month[num_num]):
            row = [date_box[i], max_temp[i],min_temp[i],weh[i], wind[i], week_box[i]]
            writer.writerow(row)
        wf.close()
import plotly.graph_objects as go

def tem_curve_high():
    # 假设有一个包含每天温度的列表，每个元素代表一天的温度值

# 假设有一个包含每天的日期的列表，对应于温度列表中的每个元素
    dates = list(range(1, month[num_num] + 1))
    fig = go.Figure(data=go.Scatter(x=dates, y=max_temp))
    fig.update_layout(
        title="一个月的最高温度变化",
        xaxis_title="日期",
        yaxis_title="温度(摄氏度)",
        )
    fig.show()
tem_curve_high()
def tem_curve_low():
    # 假设有一个包含每天温度的列表，每个元素代表一天的温度值

# 假设有一个包含每天的日期的列表，对应于温度列表中的每个元素
    dates = list(range(1, month[num_num] + 1))
    fig = go.Figure(data=go.Scatter(x=dates, y=min_temp))
    fig.update_layout(
        title="一个月的最低温度变化",
        xaxis_title="日期",
        yaxis_title="温度(摄氏度)",
        )
    fig.show()
tem_curve_low()
def tem_curve():
    """温度曲线绘制"""
    for i in range(0,month[num_num]):
        tem_low.append (int(min_temp[i][0:2]))
        tem_high.append (int(max_temp[i][0:2]))
    dates = list(range(1, len(tem_high) + 1))
    # 创建一个绘图窗口
    plt.figure()
    # 绘制温度变化曲线
    plt.plot(dates, tem_high)
    # 设置横轴标签和纵轴标签
    plt.xlabel("date")
    plt.ylabel('tem')
    # 设置标题
    plt.title('change')
    # 显示网格线
    plt.grid(True)
    # 显示图形
    plt.show()
tem_curve()