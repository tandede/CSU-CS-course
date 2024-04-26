#include <bits/stdc++.h>
using namespace std;
#define max 1000

// int search(int nums[], int size, int target)
// {
//     int left = 0;
//     int right = size - 1;
//     while (left < right) {	//left <= right �޸�Ϊ left < right,��������
//         int middle = left + ((right - left) / 2);
//         if (nums[middle] > target) {
//             right = middle - 1;
//         } else if (nums[middle] < target) {
//             left = middle + 1;
//         } else {
//             return middle;
//         }
//     }
//     //û���ҵ�Ŀ��ֵ
//     return -1;
// }

int binarySearch(int a[], int x, int left, int right)
{
	int mid = (left + right) / 2;
	if (a[mid] == x)
		return mid;
	else if (left == right)
		return -1; // ��ʾû���ҵ�
	else if (a[mid] < x)
		binarySearch(a, x, mid + 1, right);
	else if (a[mid > x])
		binarySearch(a, x, left, mid - 1);
}

void quickSort(int a[], int low, int high)
{
	if (low < high) // �ж��Ƿ����������������ݹ����ֹ����
	{
		int i = low, j = high; // �Ѵ���������Ԫ�صĵ�һ�������һ���±�ֱ�ֵ��i,j��ʹ��i,j��������
		int x = a[low];		   // ������������ĵ�һ��Ԫ����Ϊ�ڱ��������黮��Ϊ�����ڱ��Լ�С���ڱ���������
		while (i < j)
		{
			while (i < j && a[j] >= x)
				j--; // �����Ҳ�Ԫ�ؿ�ʼ��������ڱ�����ô����λ�þ���ȷ��Ȼ���ж�ǰһ��Ԫ�أ�ֱ������������
			if (i < j)
				a[i++] = a[j]; // �Ѳ�����λ���������Ǹ�Ԫ��ֵ��ֵ����һ��Ԫ�أ���Ҳ�����ڱ�Ԫ�أ���ʱ�ڱ��Ѿ�������x�У����ᶪʧ������i�ļ�1
			while (i < j && a[i] <= x)
				i++; // ��������±�Ϊi��Ԫ�ؿ�ʼ���ڱ��Ƚϴ�С������С����ô��������λ�þ���ȷ��Ȼ���жϺ�һ����ֱ������������
			if (i < j)
				a[j--] = a[i]; // �Ѳ�����λ���������Ǹ�Ԫ��ֵ��ֵ���±�Ϊj��Ԫ�أ����±�Ϊj��Ԫ���Ѿ����浽ǰ�棬���ᶪʧ������j�ļ�1
		}
		a[i] = x;				  // ���һ�����򣬰��ڱ���ֵ���±�Ϊi��λ�ã���ǰ��Ķ�����С������Ķ�������
		quickSort(a, low, i - 1); // �ݹ�����ڱ�ǰ��������Ԫ������ �� low,high��ֵ�������仯��i�����м�
		quickSort(a, i + 1, high);
	}
}

int main()
{
	while (1)
	{
		cout << "�����������С��";
		int n;
		cin >> n;
		int list[max] = {0};
		for (int i = 0; i < n; i++)
		{
			cout << "�������" << i + 1 << "����:";
			cin >> list[i];
		}
		quickSort(list, 0, n);
		int x;
		cout << "������Ҫ���ҵ���: ";
		cin >> x;
		if (binarySearch(list, x, 0, n) == -1)
			cout << "û�������" << endl;
		else
			cout << "������ڵ�" << binarySearch(list, x, 0, n) << "λ" << endl;
	}
}