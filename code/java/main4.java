import java.util.Scanner;

interface CalculateAverage { // 接口ComputerAverage的代码
    public double average(double x[]);
}

class Diving implements CalculateAverage {
    public double average(double x[]) {
        double ans = 0;
        double ans2 = 0;
        double maxtemp;
        double mintemp;
        maxtemp = x[0];
        mintemp = x[0];
        for (int i = 0; i < x.length; i++) {

            if (x[i] > maxtemp) {
                maxtemp = x[i];

            }

            if (x[i] < mintemp) {
                mintemp = x[i];

            }
            ans = ans + x[i];

        }
        ans2 = (ans - (maxtemp + mintemp)) / (x.length - 2);
        return ans2;

    }

}

class exam implements CalculateAverage {
    public double average(double x[]) {
        double ans = 0;
        for (int i = 0; i < x.length; i++) {
            ans = ans + x[i];

        }
        double ans2 = ans / x.length;
        return ans2;

    }

}

public class main4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入跳水评委打分人数：");
        int n = sc.nextInt();
        double a[] = new double[n];
        for (int i = 0; i < n; i++) {
            System.out.println("请输入第" + (i + 1) + "个跳水评委所打分数：");
            a[i] = sc.nextDouble();
        }
        Diving diving = new Diving();
        System.out.println("跳水最终成绩:" + diving.average(a));
        System.out.println("请输入考试人数：");
        int m = sc.nextInt();
        double b[] = new double[m];
        for (int i = 0; i < n; i++) {
            System.out.println("请输入第" + (i + 1) + "个人的考试分数：");
            b[i] = sc.nextDouble();
        }
        exam exam1 = new exam();
        System.out.println("考试平均成绩:" + exam1.average(b));
        sc.close();

    }
}
