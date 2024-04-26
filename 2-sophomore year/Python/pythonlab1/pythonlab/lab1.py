import pandas as pd
import wx.grid
import matplotlib.dates as mdates
import mplfinance as mpf
import threading
import requests
import json
import re
import pandas
import matplotlib.pyplot as plt
import wx
import mpl_finance
from tkinter import *
import tkinter.messagebox as messagebox
from bug import insert_hisq_data,  findall_hisq_data, findselect_hisq_data ,fetchData,pot_candlestick_ohlc
class MyWork(Frame):

    def __init__(self,master=None):
        Frame.__init__(self,master)
        self.pack()
        self.createWidgets()

    def createWidgets(self):
        self.helloLabel=Label(self,text='小秦的python作业喔')
        self.helloLabel.pack()
        self.quitButton=Button(self,text='name',command=self.who)
        self.quitButton.pack()
        self.quitButton=Button(self,text='major',command=self.what1)
        self.quitButton.pack()
        self.quitButton=Button(self,text='class',command=self.what2)
        self.quitButton.pack()

    def who(self):
        messagebox.showinfo('name','秦雅欣')
    def what1(self):
        messagebox.showinfo('major','化学化工学院-应用化学')
    def what2(self):
        messagebox.showinfo('class','应化2201')
mywork=MyWork()
mywork.master.title('hello')
mywork.mainloop()
column = ['日期', '开盘', '最高', '最低', '收盘', '涨跌额', '成交量(手)', '成交金额(万元)']

cookies = {
    'IPLOC': 'CN1200',
    'SUV': '230427083048JSFW',
    'clt': '1682555456',
    'cld': '20230427083056',
    'reqtype': 'pc',
    'gidinf': 'x099980109ee16eb87f14cc490001fc46aa6f8cd1299',
    'BIZ_MyLBS': 'cn_000568%2C%u6CF8%u5DDE%u8001%u7A96%7Ccn_002647%2C%u4EC1%u4E1C%u63A7%u80A1%7Ccn_688081%2C%u5174%u56FE%u65B0%u79D1%7Ccn_688478%2C%u6676%u5347%u80A1%u4EFD%7Ccn_000002%2C%u4E07%u79D1%uFF21',
    't': '1683170711989',
}

headers = {
    'authority': 'q.stock.sohu.com',
    'accept': '*/*',
    'accept-language': 'zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6',
    # 'cookie': 'IPLOC=CN1200; SUV=230427083048JSFW; clt=1682555456; cld=20230427083056; reqtype=pc; gidinf=x099980109ee16eb87f14cc490001fc46aa6f8cd1299; BIZ_MyLBS=cn_000568%2C%u6CF8%u5DDE%u8001%u7A96%7Ccn_002647%2C%u4EC1%u4E1C%u63A7%u80A1%7Ccn_688081%2C%u5174%u56FE%u65B0%u79D1%7Ccn_688478%2C%u6676%u5347%u80A1%u4EFD%7Ccn_000002%2C%u4E07%u79D1%uFF21; t=1683170711989',
    'referer': 'https://q.stock.sohu.com/cn/000568/lshq.shtml',
    'sec-ch-ua': '"Chromium";v="112", "Microsoft Edge";v="112", "Not:A-Brand";v="99"',
    'sec-ch-ua-mobile': '?0',
    'sec-ch-ua-platform': '"Windows"',
    'sec-fetch-dest': 'script',
    'sec-fetch-mode': 'no-cors',
    'sec-fetch-site': 'same-origin',
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36 Edg/112.0.1722.58',
}

response = requests.get(
    'https://q.stock.sohu.com/hisHq?code=cn_000568&stat=1&order=D&period=d&0.25251595627443435',
    cookies=cookies,
    headers=headers,
)

# print(response.text)
# print(type(response.text))
# print(response.text[18:-123])
data_list = json.loads(response.text[18:-125])
# print(data_list)
print(type(data_list))
data=[]
for data in data_list:
    rows = re.search(
    r'\[\'(\w+-\w+-\w+)\'\, \'(\w*.\w*)\'\, \'(\w*.\w*)\'\, \'(.\w*.\w*)\'\, \'(.\w*.\w*%)\'\, \'(\w+.\w+)\'\, \'(\w+.\w+)\'\, \'(\w+)\'\, \'(\w+.\w+)\'\, \'(\w*.\w*%)\'\]',
        str(data_list))
    fields={}
    fields['日期'] = rows.group(1)
    fields['开盘'] = float(rows.group(2))
    fields['收盘'] = float(rows.group(3))
    fields['涨跌额'] = float(rows.group(4))
    s1 = rows.group(5).replace('%', '')
    fields['涨跌幅'] = float(s1)
    fields['最低'] = float(rows.group(6))
    fields['最高'] = float(rows.group(7))
    fields['成交量'] = int(rows.group(8))
    fields['成交金额'] = float(rows.group(9))
    s2 = rows.group(10).replace('%', '')
    fields['换手率'] = float(s2)
    data.append(fields)
    # print(fields)
# insert_hisq_data(fields)
# findall_hisq_data()
# findselect_hisq_data('03', '03', '04', '04')
# fetchData('03', '03', '04', '04')
# plt.rcParams['font.family']=['SimHei']
# plt.rcParams['axes.unicode_minus'] =False

# pot_candlestick_ohlc(fetchData('03', '03', '04', '04'))
class MyGridTable(wx.grid.GridTableBase):
    def __init__(self, data):
        super().__init__()
        # 表头
        self.colLabels = column
        # 表格数据
        self.data = data

    # 返回网格行数
    def GetNumberRows(self):
        return len(self.data)

    # 返回网格列数
    def GetNumberCols(self):
        return len(column)

    # 返回单元格的值
    def GetValue(self, row, col):
        return self.data[row][col]

    # 返回列名
    def GetColLabelValue(self, col):
        return self.colLabels[col]
class MyFrame2(wx.Frame):
    def __init__(self,  savapath, savepath1, savepath2, savepath3, savepath4):
        super().__init__(parent=None, title='股票行情图像', pos=(2000, 2000), size=(2500, 1500))

        self.bmps = [wx.Bitmap(savapath, wx.BITMAP_TYPE_PNG),
                     wx.Bitmap(savapath, wx.BITMAP_TYPE_PNG),
                     wx.Bitmap(savepath2, wx.BITMAP_TYPE_PNG),
                     wx.Bitmap(savepath1, wx.BITMAP_TYPE_PNG),
                     wx.Bitmap(savepath3, wx.BITMAP_TYPE_PNG),
                     wx.Bitmap(savepath4, wx.BITMAP_TYPE_PNG)]
        fnt = wx.Font(pointSize=10, family=wx.ROMAN, style=wx.NORMAL, weight=wx.NORMAL)
        self.Maximize(True)
        self.Centre()  # 设置窗口居中
        self.panel = wx.Panel(parent=self)
        # 创建垂直方向的Box布局管理器对象
        hbox = wx.BoxSizer(wx.HORIZONTAL)
        image0_sbitmap = wx.StaticBitmap(self.panel, -1)
        # hbox1 = wx.BoxSizer(wx.HORIZONTAL)
        statictext = wx.StaticText(parent=self.panel, label='欢迎使用QWQ')
        fnt1 = wx.Font(pointSize=15, family=wx.ROMAN, style=wx.NORMAL, weight=wx.NORMAL)
        statictext.SetFont(fnt1)

        label1 = "OHLC柱状图"
        b1 = wx.Button(parent=self.panel, id=1, label='蜡烛图')
        b12 = wx.Button(parent=self.panel, id=2, label='多日图')
        b13 = wx.Button(parent=self.panel, id=3, label='均线图')
        b2 = wx.Button(self.panel, id=4, label='折线图')
        b3 = wx.Button(self.panel, id=5, label=label1)
        b4 = wx.Button(self.panel, id=6, label='返回')
        self.Bind(wx.EVT_BUTTON, self.on_click, id=1, id2=6)
        b1.SetFont(fnt)
        b12.SetFont(fnt)
        b13.SetFont(fnt)
        b2.SetFont(fnt)
        b3.SetFont(fnt)
        b4.SetFont(fnt)

        self.image = wx.StaticBitmap(self.panel, -1, self.bmps[0])

        # 添加标控件到Box布局管理器
        # vbox.Add(self.finnalresult, proportion=1, flag=wx.CENTER)
        # vbox.Add(self.tcfin, proportion=1, flag=wx.CENTER)
        hbox.Add(b1, proportion=1, flag=wx.CENTER)
        hbox.Add(b12, proportion=1, flag=wx.CENTER)
        hbox.Add(b13, proportion=1, flag=wx.CENTER)
        hbox.Add(b2, proportion=1, flag=wx.CENTER)
        hbox.Add(b3, proportion=1, flag=wx.CENTER)
        #hbox.Add(b4, proportion=1, flag=wx.CENTER)
        #self.panel.SetSizer(hbox)
        vbox = wx.BoxSizer(wx.VERTICAL)
        vbox.Add(statictext, proportion=1, flag=wx.ALIGN_CENTER_HORIZONTAL)
        vbox.Add(image0_sbitmap, proportion=2, flag=wx.ALIGN_CENTER_HORIZONTAL)
        vbox.Add(hbox, proportion=2, flag=wx.CENTER)
        vbox.Add(b4, proportion=1, flag=wx.CENTER)
        vbox.Add(self.image, proportion=1, flag=wx.CENTER | wx.FIXED_MINSIZE)
        self.panel.SetSizer(vbox)


    def on_click(self, event):
        event_id = event.GetId()
        if event_id == 1:
            self.image.SetBitmap(self.bmps[1])
            self.panel.Layout()
        elif event_id == 4:
            self.image.SetBitmap(self.bmps[2])
            self.panel.Layout()
        elif event_id == 5:
            self.image.SetBitmap(self.bmps[3])
            self.panel.Layout()
        elif event_id == 2:
            self.image.SetBitmap(self.bmps[4])
            self.panel.Layout()
        elif event_id == 3:
            self.image.SetBitmap(self.bmps[5])
            self.panel.Layout()
        else:
            self.Close()
            self.Destroy()
            workthread = threading.Thread(target=workthread_body(), name='WorkThread')
            workthread.start()

# 自定义窗口类MYFrame1
class MyFrame1(wx.Frame):
    def __init__(self):
        super().__init__(parent=None, title='股票行情查询', size=(800, 200))
        self.Centre()  # 设置窗口居中
        self.SetMinSize((750, 310))
        #self.Maximize(True)
        self.panel = wx.Panel(parent=self)
        image0_sbitmap = wx.StaticBitmap(self.panel, -1)
        # hbox1 = wx.BoxSizer(wx.HORIZONTAL)
        statictext = wx.StaticText(parent=self.panel, label='欢迎使用')
        fnt = wx.Font(pointSize=15, family=wx.ROMAN, style=wx.NORMAL, weight=wx.NORMAL)
        statictext.SetFont(fnt)
        # 预定义变量
        self.text = ['', '', '', '']  # 初始月份，初始日期，结束月份，结束日期
        # self.tablename = ['']  # 数据库表名
        self.data = []  # 爬取的数据
        self.savepath = ''
        self.savepath1 = 'his_bar' + self.savepath

        statictext2 = wx.StaticText(self.panel, label='         开始月份')
        list2 = ['', '01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12']
        self.ch2 = wx.Choice(self.panel, -1, choices=list2)
        self.Bind(wx.EVT_CHOICE, self.on_choice2, self.ch2)

        statictext3 = wx.StaticText(self.panel, label='         开始日期')
        list3 = ['', '01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '31']
        self.ch3 =wx.Choice(self.panel, -1, choices=list3)
        self.Bind(wx.EVT_CHOICE, self.on_choice3, self.ch3)
        # hbox2.Add(statictext2, 1, flag=wx.LEFT | wx.RIGHT | wx.FIXED_MINSIZE, border=5)
        # hbox2.Add(ch2, 1, flag=wx.ALL | wx.FIXED_MINSIZE)

        statictext4 = wx.StaticText(self.panel, label='         结束月份')
        list4 = ['', '01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12']
        self.ch4 = wx.Choice(self.panel, -1, choices=list4)
        self.Bind(wx.EVT_CHOICE, self.on_choice4, self.ch4)

        statictext5 = wx.StaticText(self.panel, label='         结束日期')
        list5 = ['', '01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '31']
        self.ch5 = wx.Choice(self.panel, -1, choices=list5)
        self.Bind(wx.EVT_CHOICE, self.on_choice5, self.ch5)

        b1 = wx.Button(parent=self.panel, label='查询数据')  # 按钮控件
        b1.Bind(wx.EVT_BUTTON, self.showdata, b1)  # 绑定事件

        b2 = wx.Button(parent=self.panel, label='展示图表')  # 按钮控件
        b2.Bind(wx.EVT_BUTTON, self.showfig, b2)  # 绑定事件

        self.showPanel = wx.Panel(parent=self.panel, size=(1200, 800))  # 展示面板
        self.gridpanel = None   #网格面版
        self.kpanel = None      # 图表面版

        # 设置布局

        # 创建水平方向的Box布局管理器对象
        hbox = wx.BoxSizer(wx.HORIZONTAL)

        # 添加控件到水平Box布局管理

        hbox.Add(statictext2, proportion=1, flag=wx.EXPAND)
        hbox.Add(self.ch2, proportion=1, flag=wx.ALIGN_LEFT)

        hbox.Add(statictext3, proportion=1, flag=wx.EXPAND)
        hbox.Add(self.ch3, proportion=1, flag=wx.ALIGN_LEFT)

        hbox.Add(statictext4, proportion=1, flag=wx.EXPAND)
        hbox.Add(self.ch4, proportion=1, flag=wx.ALIGN_LEFT)

        hbox.Add(statictext5, proportion=1, flag=wx.EXPAND)
        hbox.Add(self.ch5, proportion=1, flag=wx.ALIGN_LEFT)

        hbox1 = wx.BoxSizer(wx.HORIZONTAL)
        hbox1.Add(b1, proportion=1, flag=wx.ALIGN_CENTER)
        hbox1.Add(b2, proportion=1, flag=wx.ALIGN_CENTER)

        # 创建垂直方向的Box布局管理对象
        vbox = wx.BoxSizer(wx.VERTICAL)

        # 添加控件到垂直Box布局管理器
        vbox.Add(statictext, proportion=1, flag=wx.ALIGN_CENTER_HORIZONTAL)
        vbox.Add(image0_sbitmap, proportion=2, flag=wx.ALIGN_CENTER_HORIZONTAL)
        vbox.Add(hbox, proportion=1, flag=wx.ALIGN_LEFT)
        vbox.Add(hbox1, proportion=1, flag=wx.ALIGN_CENTER)
        vbox.Add(self.showPanel, proportion=10, flag=wx.EXPAND)

        self.panel.SetSizer(vbox)


    # 获取用户选择的开始月份
    def on_choice2(self, event):
        self.text[0] = self.ch2.GetStringSelection()

    # 获取用户选择的开始日期
    def on_choice3(self, event):
        self.text[1] = self.ch3.GetStringSelection()

    def on_choice4(self, event):
        self.text[2] = self.ch4.GetStringSelection()

    def on_choice5(self, event):
        self.text[3] = self.ch5.GetStringSelection()

    # 查询表格按钮
    def showdata(self, event):
        datafile = fetchData(self.text[0], self.text[1], self.text[2], self.text[3])
        self.data = pd.read_csv(datafile, sep=',').values

        # 将数据展示
        if self.gridpanel:
            self.gridpanel.Destroy()
        if self.kpanel:
            self.kpanel.Destroy()

        self.gridpanel = self.creategridpanel(self.showPanel)
        self.gridpanel.Show()


    # 查询图表按钮
    def showfig(self, event):

        # 设置中文字体
        plt.rcParams['font.family'] = ['SimHei']
        plt.rcParams['axes.unicode_minus'] = False

        datafile = fetchData(self.text[0], self.text[1], self.text[2], self.text[3])
        data = findselect_hisq_data(self.text[0], self.text[1], self.text[2], self.text[3])
        self.savepath = self.text[0]+'-'+self.text[1] + 'to' + self.text[2] +'-'+ self.text[3] +' '+ '.png'

        # 成交量折线图
        # 从date中提取成交量数据
        volume_map = map(lambda it: it['成交量'], data)
        # 蒋volume_map转换为成交量列表
        volume_list = list(volume_map)

        # 从data中提取日期数据
        data_map = map(lambda it: it['日期'], data)
        # 将date_map转换为日期列表
        date_list = list(data_map)
        # 设置图表大小
        plt.figure(figsize=(14, 4))

        # pot_hisvolume(date_list, volume_list)
        dates = date_list
        volumes = volume_list
        # 绘制线段
        plt.plot(dates, volumes)
        plt.setp(plt.gca().get_xticklabels(), rotation=20, horizontalalignment='right')

        plt.title('股票历史成交量', fontsize=20)  # 添加图表标题
        plt.ylabel('成交量', fontsize=20)  # 添加y轴标题
        plt.xlabel('交易日期', fontsize=20)  # 添加x轴标题

        self.savepath2 = 'pot' + self.savepath
        plt.savefig(self.savepath2)

        def pot_his_bar(date_list, p_list, ylabel):
            """绘制OHLC柱状图"""

            # 绘制柱状图
            plt.bar(date_list, p_list)

            plt.title('股票历史成交量')  # 添加图表标题
            plt.ylabel(ylabel)  # 添加y轴标题
            plt.xlabel('交易日期')  # 添加x轴标题

        # 从data中提取日期数据
        date_map = map(lambda it: it['日期'], data)
        # 将date_map转换为日期列表
        date_list = list(date_map)

        # 从data中提取开盘价数据
        open_map = map(lambda it: it['开盘'], data)
        # 将open_map转换为开盘价列表
        open_list = list(open_map)

        # 从data中提取最高价数据
        high_map = map(lambda it: it['最高'], data)
        # 将high_map转换为最高价列表
        high_list = list(high_map)

        # 从data中提取最低价数据
        low_map = map(lambda it: it['最低'], data)
        # 将low_map转换为最低价列表
        low_list = list(low_map)

        # 从data中提取收盘价数据
        close_map = map(lambda it: it['收盘'], data)
        # 将close_map转换为收盘价列表
        close_list = list(close_map)

        # 设置图表大小
        plt.figure(figsize=(12, 5))

        plt.subplot(411)
        pot_his_bar(date_list, open_list, '开盘价')
        plt.setp(plt.gca().get_xticklabels(), rotation=15, horizontalalignment='right')

        plt.subplot(412)
        pot_his_bar(date_list, close_list, '收盘价')
        plt.setp(plt.gca().get_xticklabels(), rotation=15, horizontalalignment='right')

        plt.subplot(413)
        pot_his_bar(date_list, high_list, '最高价')
        plt.setp(plt.gca().get_xticklabels(), rotation=15, horizontalalignment='right')

        plt.subplot(414)
        pot_his_bar(date_list, low_list, '最低价')
        plt.setp(plt.gca().get_xticklabels(), rotation=15, horizontalalignment='right')

        plt.tight_layout()  # 调整布局
        plt.savefig('his_bar' + self.savepath)

        self.savepath1 = 'his_bar' + self.savepath




        """绘制阴阳烛图1"""
        # 从CSV文件中读取数据到DataFrame数据结构中
        quotes = pandas.read_csv(datafile,
                                 index_col=0,
                                 parse_dates=True,
                                 infer_datetime_format=True)

        # 绘制一个子图，并设置子图大小
        fig, ax = plt.subplots(figsize=(15, 5))
        # 调整子图参数SubplotParams
        fig.subplots_adjust(bottom=0.2)

        mpl_finance.candlestick_ohlc(ax, zip(mdates.date2num(quotes.index.to_pydatetime()),
                                             quotes['开盘'], quotes['最高'],
                                             quotes['最低'], quotes['收盘']),
                                     width=1, colorup='r', colordown='g', alpha=0.6)
        ax.xaxis_date()
        ax.autoscale_view()
        quotes['日成交量中位数'] = (quotes['最高'] + quotes['最低']) / 2
        plt.plot(quotes.index, quotes['开盘'], 'r-', label='开盘价')
        plt.plot(quotes.index, quotes['收盘'], 'g-', label='收盘价')
        # plt.plot(quotes.index, quotes['最高'], 'b-', label='最高价')
        # plt.plot(quotes.index, quotes['最低'], 'y-', label='最低价')
        plt.plot(quotes.index, quotes['日成交量中位数'], 'cyan', label='日成交量中位数')
        plt.legend(loc='best', fontsize=16)
        plt.setp(plt.gca().get_xticklabels(), rotation=20, horizontalalignment='right')

        plt.savefig(self.savepath)

        """绘制阴阳烛图2"""
        # 从CSV文件中读取数据到DataFrame数据结构中
        quotes1 = pandas.read_csv(datafile,     
                                  index_col=0,
                                  parse_dates=True,
                                  infer_datetime_format=True)
        # print(quotes)
        quotes1.reset_index(inplace=True)
        quotes1 = quotes1[['日期', '开盘', '收盘', '最低', '最高', '成交量']]
        quotes1.columns = ['datetime', 'open', 'close', 'low', 'high', 'volume']

        quotes1["datetime"] = pandas.to_datetime(quotes1["datetime"])

        quotes1.set_index("datetime", inplace=True)

        s = mpf.make_mpf_style(base_mpf_style='yahoo', rc={'font.family': 'SimHei'})
        mpf.plot(
            data=quotes1,
            type="candle",
            # title="蜡烛图与三五日均线图",
            ylabel="金额(￥)",
            style=s,
            figsize=(14, 5),
            mav=(3, 5),  # 整数，或包含整数的列表/元组
            volume=True,
            savefig='蜡烛图2' + self.savepath,
            ylabel_lower="成交量",
            figscale=2
        )
        self.savepath3 = '蜡烛图2' + self.savepath

        """绘制阴阳烛图3"""
        s1 = mpf.make_mpf_style(base_mpf_style='default', rc={'font.family': 'SimHei'})
        mpf.plot(
            data=quotes1,
            type="candle",
            # title="蜡烛图+两日均线图",
            ylabel="金额(￥)",
            style=s1,
            figsize=(15, 5),
            mav=(2),  # 整数，或包含整数的列表/元组
            volume=True,
            savefig='蜡烛图3' + self.savepath,
            ylabel_lower="成交量",
            figscale=2
        )

        self.savepath4 = '蜡烛图3' + self.savepath

        self.Close()
        self.Destroy()

        frame = MyFrame2(self.savepath, self.savepath1, self.savepath2, self.savepath3, self.savepath4)
        frame.Show()

    # 创建表格
    def creategridpanel(self, parent):
        panel = wx.Panel(parent, size=(1000, 600))
        grid = wx.grid.Grid(panel, name='grid', size=(1000, 600))
        self.initGrid()

        box = wx.BoxSizer()
        box.Add(grid, 1, flag=wx.ALL | wx.EXPAND, border=0)
        panel.SetSizer(box)

        return panel

    # 初始化表格
    def initGrid(self):
        grid = self.FindWindowByName('grid')
        table = MyGridTable(self.data)
        grid.SetTable(table, True)

        # 设置行列宽
        rowsizeinfo = wx.grid.GridSizesInfo(30, [])
        grid.SetRowSizes(rowsizeinfo)

        colsizeinfo = wx.grid.GridSizesInfo(0, [200, 140, 140, 140, 140, 140, 140, 180, 220, 180, 180])
        grid.SetColSizes(colsizeinfo)

        return grid   
class MyFrame(wx.Frame):
    def __init__(self):
        super().__init__(parent=None, title='股票行情查询', size=(300, 400))
        self.Centre()  # 设置窗口居中
        panel = wx.Panel(parent=self)
        fnt1 = wx.Font(pointSize=15, family=wx.ROMAN, style=wx.NORMAL, weight=wx.NORMAL)
        fnt = wx.Font(pointSize=20, family=wx.ROMAN, style=wx.NORMAL, weight=wx.NORMAL)
        # 创建垂直方向的Box布局管理器
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        image0_sbitmap = wx.StaticBitmap(panel, -1)

        self.statictext = wx.StaticText(parent=panel, label="Let's start?", style=wx.ALIGN_CENTER_HORIZONTAL)
        self.statictext.SetFont(fnt)
        b1 = wx.Button(parent=panel, label='Yes')
        # b1 = wx.ToggleButton(panel, -1, 'Yes')
        self.Bind(wx.EVT_BUTTON, self.on_click, b1)

        b2 = wx.Button(parent=panel, label='No')
        self.Bind(wx.EVT_BUTTON, self.on_click1, b2)

        b1.SetFont(fnt1)
        b2.SetFont(fnt1)

        b3 = wx.BitmapButton(panel, -1)
        self.Bind(wx.EVT_BUTTON, self.on_click, b3)

        # 添加静态文本和按钮到Box布局管理器
        self.sizer.Add(100, 10, proportion=1, flag=wx.CENTER | wx.FIXED_MINSIZE)
        self.sizer.Add(self.statictext, proportion=1, flag=wx.CENTER | wx.FIXED_MINSIZE)
        self.sizer.Add(image0_sbitmap, proportion=2, flag=wx.CENTER | wx.FIXED_MINSIZE)
        self.sizer.Add(b1, proportion=1, flag=wx.CENTER | wx.EXPAND)
        self.sizer.Add(b2, proportion=1, flag=wx.CENTER | wx.EXPAND)
        self.sizer.Add(b3, proportion=3, flag=wx.CENTER | wx.EXPAND)

        panel.SetSizer(self.sizer)

    def on_click(self, event):

        # 跳转到新界面
        self.Close()
        self.Destroy()
        workthread = threading.Thread(target=workthread_body(), name='WorkThread')
        workthread.start()

    def on_click1(self, event):
        wx.MessageBox("感谢使用")
        self.Close()
        self.Destroy()

class App1(wx.App):

    def OnInit(self):
        # 创建窗口对象
        frame = MyFrame1()
        frame.Show()
        return True

class App(wx.App):

    def OnInit(self):
        # 创建窗口对象
        frame = MyFrame()
        frame.Show()
        return True

def workthread_head():
    app = App()
    app.MainLoop()   # 进入主事件循环

def workthread_body():
    global result
    app = App1()
    app.MainLoop()  # 进入主事件循环

if __name__ == '__main__':
    workthread = threading.Thread(target=workthread_head(), name='WorkThread')
    workthread.start()
    # app = App()
    # app.MainLoop()
    