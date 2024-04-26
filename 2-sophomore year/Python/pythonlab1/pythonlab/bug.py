import pymysql
import csv
import pandas 
import matplotlib.dates as mdates
import mpl_finance
import matplotlib.pyplot as plt

def pot_candlestick_ohlc(datafile):
    quotes = pandas.read_csv(datafile,
                                 index_col=0,
                                 parse_dates=True,
                                 infer_datetime_format=True)

    # 绘制一个子图，并设置子图大小
    fig, ax = plt.subplots(figsize=(30, 10))
        # 调整子图参数SubplotParams
    fig.subplots_adjust(bottom=0.2)

    mpl_finance.candlestick_ohlc(ax, zip(mdates.date2num(quotes.index.to_pydatetime()),
                                             quotes['开盘'], quotes['最高'],
                                             quotes['最低'], quotes['收盘']),
                                     width=1, colorup='r', colordown='g', alpha=0.6)
    ax.xaxis_date()
    ax.autoscale_view()
    plt.setp(plt.gca().get_xticklabels(),rotation=45, horizontalalignment=
             'right')
    plt.show()


def fetchData(startmonth, startday, endmonth, endday):

    data = findselect_hisq_data( startmonth, startday, endmonth, endday)
    print('data='+str(data))

    # 列名
    colsname = ['日期', '开盘', '最高', '最低', '收盘', '涨跌额', '成交量', '成交金额']
    # 临时数据文件名
    datafile = '  from '+startmonth+'-'+startday+'to '+endmonth+'-'+endday+' '+'temp.csv'
    # 写入数据到临时数据文件
    with open(datafile, 'w', newline='', encoding='utf-8') as wf:
        writer = csv.writer(wf)
        writer.writerow(colsname)
        for quotes in data:
            row = [quotes['日期'], quotes['开盘'], quotes['最高'],
                   quotes['最低'], quotes['收盘'], quotes['涨跌额'], quotes['成交量'], quotes['成交金额']]
            writer.writerow(row)
    return datafile

def findselect_hisq_data(startmonth, startday, endmonth, endday):

    # 1.建立数据库连接
    connection = pymysql.connect(host='localhost',
                                 user='root',
                                 password='tzw20010126',
                                 database='bug',
                                 charset='utf8')

    # 要返回的数据
    data = []
    starttime = '2023-'+startmonth+'-'+startday
    print('starttime'+starttime)
    endtime = '2023-'+endmonth+'-'+endday
    print('endtime'+endtime)

    try:
        # 2.创建游标对象
        with connection.cursor() as cursor:

            # # 3.执行SQL操作
            sql = """select ' \
                  'HDate, Open, Close, changeamount, changerate, Low, High, Volume, Volumeamount, turnoverrate ' \
                  'from historicalquote where  HDate between '%s' and '%s' """\
                  % (starttime, endtime)  # 注意要加引号，不然无法查询数据
            cursor.execute(sql)
            # 3.执行SQL操作
            sql = 'select ' \
                  'HDate, Open, Close, changeamount, changerate, Low, High, Volume, Volumeamount, turnoverrate ' \
                  'from historicalquote where   hdate between %s and %s'
            cursor.execute(sql, [starttime, endtime])

            # 4.提取结果集
            result_set = cursor.fetchall()
            # print(result_set)

            for row in result_set:
                fields = {}
                fields['日期'] = str(row[0])
                fields['开盘'] = float(row[1])
                fields['收盘'] = float(row[2])
                fields['涨跌额'] = float(row[3])
                fields['涨跌幅'] = float(row[4])
                fields['最低'] = float(row[5])
                fields['最高'] = float(row[6])
                fields['成交量'] = float(row[7])
                fields['成交金额'] = float(row[8])
                fields['换手率'] = float(row[9])
                data.append(fields)
        print(data)

        # with 代码块结束  5.关闭游标
    except pymysql.DatabaseError as error:
        print('数据查询失败' + error)
    finally:
        # 6.关闭数据库连接
        connection.close()

    # 返回字典列表
    return data


def findall_hisq_data():

    # 1.建立数据库连接
    connection = pymysql.connect(host='localhost',
                                 user='root',
                                 password='tzw20010126',
                                 database='bug',
                                 charset='utf8')

    # 要返回的数据
    data = []

    try:
        # 2.创建游标对象
        with connection.cursor() as cursor:

            # 3.执行SQL操作
            sql = """
                  select 
                  HDate, Open, Close, changeamount, changerate, Low, High, Volume, Volumeamount, turnoverrate
                  from historicalquote 
                  """
            cursor.execute(sql)

            # 4.提取结果集
            result_set = cursor.fetchall()
            print("查询成功")
            for row in result_set:
                fields = {}
                fields['日期'] = row[0]
                fields['开盘'] = float(row[1])
                fields['收盘'] = float(row[2])
                fields['涨跌额'] = float(row[3])
                fields['涨跌幅'] = float(row[4])
                fields['最低'] = float(row[5])
                fields['最高'] = float(row[6])
                fields['成交量'] = float(row[7])
                fields['成交金额'] = float(row[8])
                fields['换手率'] = float(row[9])
                data.append(fields)                
        # print(data)

        # with 代码块结束  5.关闭游标
    except pymysql.DatabaseError as error:
        print('数据查询失败' + error)
    finally:
        # 6.关闭数据库连接
        connection.close()

    # 返回字典列表
    return data


def insert_hisq_data(row):
    """在股票历史价格表中传入数据"""

    # 1.建立数据库连接
    # 打开数据库连接
    connection = pymysql.connect(host='localhost',
                                 user='root',
                                 password='tzw20010126',
                                 database='bug',
                                 charset='utf8')

    try:
        # 2.创建游标对象
        with connection.cursor() as cursor:

            # 3.执行SQL操作
            sql = 'insert into historicalquote ' \
                  '(HDate,Open,Close,changeamount,changerate,Low,High,Volume,Volumeamount,turnoverrate)' \
                  'values  (%(日期)s,%(开盘)s,%(收盘)s,%(涨跌额)s,%(涨跌幅)s,%(最低)s,%(最高)s,%(成交量)s,%(成交金额)s,%(换手率)s)'

            affectedcount = cursor.execute(sql, row)

            print('影响的数据行数:{0}'.format(affectedcount))
            # 4.提交数据库事务
            connection.commit()

        # with 代码块结束  5.关闭游标
    except pymysql.DatabaseError as error:
        # 4.回滚数据库事务
        connection.rollback()
        print(error)
    finally:
        # 6.关闭数据库连接
        connection.close()
