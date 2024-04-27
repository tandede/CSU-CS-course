import java.util.Scanner;
 
public class Triangle {
	public static void main(String[] args) {
		Scanner num = new Scanner(System.in);
		System.out.println("请输入三角形的三边：");
		System.out.print("请输入第一条边:");
		double a = num.nextDouble();
		System.out.print("请输入第二条边:");
		double b = num.nextDouble();
		System.out.print("请输入第三条边:");
		double c = num.nextDouble();
 
		if ((a + b) > c && (a + c) > b && (b + c) > a && (a + b) != c) {
			System.out.println("可以构成三角形，三边长度分别是：" + a + " " + b + " " + c + ".");
		} else
			System.out.println(a + " " + b + " " + c + "，不可以构成三角形。");
        num.close();
	}
}