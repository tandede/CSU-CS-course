import numpy as np
import matplotlib.pyplot as plt

# 读取数据
data = np.loadtxt('ex1data1.txt', delimiter=',')
X = data[:, 0]  # 城市人口数
y = data[:, 1]  # 利润

# 添加偏置项
X = np.column_stack((np.ones_like(X), X))

# 定义梯度下降函数
def gradient_descent(X, y, theta, learning_rate, iterations):
    m = len(y)
    for _ in range(iterations):
        # 计算预测值
        predictions = np.dot(X, theta)
        # 计算误差
        error = predictions - y
        # 更新参数
        theta -= (learning_rate / m) * np.dot(X.T, error)
    return theta

# 初始化参数
theta = np.zeros(2)
learning_rate = 0.01
iterations = 1500

# 运行梯度下降算法
theta = gradient_descent(X, y, theta, learning_rate, iterations)

# 输出参数
print("参数 a: {:.2f}".format(theta[1]))
print("参数 b: {:.2f}".format(theta[0]))

# 绘制已知数据的散点图和拟合的直线
plt.figure()
plt.scatter(data[:, 0], data[:, 1], marker='x', color='red', label='Training Data')
plt.plot(X[:, 1], np.dot(X, theta), label='Linear Regression')
plt.xlabel('Population of City in 10,000s')
plt.ylabel('Profit in $10,000s')
plt.legend()
plt.title('Profit Prediction')
plt.show()