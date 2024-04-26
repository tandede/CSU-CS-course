#include <bits/stdc++.h>
using namespace std;
#define max 1000

// int search(int nums[], int size, int target)
// {
//     int left = 0;
//     int right = size - 1;
//     while (left < right) {	//left <= right 修改为 left < right,其他不变
//         int middle = left + ((right - left) / 2);
//         if (nums[middle] > target) {
//             right = middle - 1;
//         } else if (nums[middle] < target) {
//             left = middle + 1;
//         } else {
//             return middle;
//         }
//     }
//     //没有找到目标值
//     return -1;
// }

int binarySearch(int a[], int x, int left, int right)
{
	int mid = (left + right) / 2;
	if (a[mid] == x)
		return mid;
	else if (left == right)
		return -1; // 表示没有找到
	else if (a[mid] < x)
		binarySearch(a, x, mid + 1, right);
	else if (a[mid > x])
		binarySearch(a, x, left, mid - 1);
}

void quickSort(int a[], int low, int high)
{
	if (low < high) // 判断是否满足排序条件，递归的终止条件
	{
		int i = low, j = high; // 把待排序数组元素的第一个和最后一个下标分别赋值给i,j，使用i,j进行排序；
		int x = a[low];		   // 将待排序数组的第一个元素作为哨兵，将数组划分为大于哨兵以及小于哨兵的两部分
		while (i < j)
		{
			while (i < j && a[j] >= x)
				j--; // 从最右侧元素开始，如果比哨兵大，那么它的位置就正确，然后判断前一个元素，直到不满足条件
			if (i < j)
				a[i++] = a[j]; // 把不满足位次条件的那个元素值赋值给第一个元素，（也即是哨兵元素，此时哨兵已经保存在x中，不会丢失）并把i的加1
			while (i < j && a[i] <= x)
				i++; // 换成左侧下标为i的元素开始与哨兵比较大小，比其小，那么它所处的位置就正确，然后判断后一个，直到不满足条件
			if (i < j)
				a[j--] = a[i]; // 把不满足位次条件的那个元素值赋值给下标为j的元素，（下标为j的元素已经保存到前面，不会丢失）并把j的加1
		}
		a[i] = x;				  // 完成一次排序，把哨兵赋值到下标为i的位置，即前面的都比它小，后面的都比它大
		quickSort(a, low, i - 1); // 递归进行哨兵前后两部分元素排序 ， low,high的值不发生变化，i处于中间
		quickSort(a, i + 1, high);
	}
}

int main()
{
	while (1)
	{
		cout << "请输入数组大小：";
		int n;
		cin >> n;
		int list[max] = {0};
		for (int i = 0; i < n; i++)
		{
			cout << "请输入第" << i + 1 << "个数:";
			cin >> list[i];
		}
		quickSort(list, 0, n);
		int x;
		cout << "请输入要查找的数: ";
		cin >> x;
		if (binarySearch(list, x, 0, n) == -1)
			cout << "没有这个数" << endl;
		else
			cout << "这个数在第" << binarySearch(list, x, 0, n) << "位" << endl;
	}
}