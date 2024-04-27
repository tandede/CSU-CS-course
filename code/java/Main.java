import java.util.Scanner;

public class Main {
	public static void main(String args[]) 
	{
		Scanner sc =new Scanner(System.in);		
		Point p1 = new Point(0, 0);
		Point p2 = new Point(4, 0);
		Point p3 = new Point(0, 3);
		Trianglee t1 = new Trianglee(p1, p2, p3);
		System.out.println("初始三角形的面积：" + t1.getArea());
		System.out.println("初始三角形的周长：" + t1.getPerimeter());
		System.out.println("请输入第一个点：");
		double x1= sc.nextDouble();
		double y1=sc.nextDouble();
		System.out.println("请输入第二个点：");
		double x2= sc.nextDouble();
		double y2=sc.nextDouble();
		System.out.println("请输入第三个点：");
		double x3= sc.nextDouble();
		double y3=sc.nextDouble();
		Point p4 = new Point(x1, y1);
		Point p5 = new Point(x2, y2);
		Point p6 = new Point(x3, y3);
		t1.setTri(p4, p5, p6);
		System.out.println("更改后三角形的面积：" + t1.getArea());
		System.out.println("更改后三角形的周长：" + t1.getPerimeter());
		sc.close();
	}
}
class Point
{
	double x, y;
	public Point(double x, double y)
	{
		this.x = x;
		this.y = y;
	}
}
class Trianglee
{
	private Point point1, point2, point3;
	private double a, b, c;
	public Trianglee() {

	}
	public Trianglee(Point point11, Point point22, Point point33)
	{
		setTri(point11, point22, point33);		
	}
	public void setTri(Point point11, Point point22, Point point33)
	{
		this.point1 = point11;
		this.point2 = point22;
		this.point3 = point33;
		a = Math.sqrt(Math.pow((point2.x - point1.x), 2) + Math.pow((point2.y - point1.y), 2));
		b = Math.sqrt(Math.pow((point3.x - point2.x), 2) + Math.pow((point3.y - point2.y), 2));
		c = Math.sqrt(Math.pow((point3.x - point1.x), 2) + Math.pow((point3.y - point1.y), 2));
		if ((a + b) > c && (a + c) > b && (b + c) > a && (a + b) != c) {
			System.out.println("可以构成三角形，三边长度分别是：" + a + " " + b + " " + c + ".");
		} else
			{System.out.println("不可以构成三角形。");

		}
	}
	public double getArea()
	{
		double p = (a + b + c) / 2.0;
		if ((a + b) > c && (a + c) > b && (b + c) > a && (a + b) != c)
		return Math.sqrt(p * (p-a)* (p-b) * (p-c));
		else
		return 0;
	}
	public double getPerimeter()
	{
		if ((a + b) > c && (a + c) > b && (b + c) > a && (a + b) != c)
		return a + b + c;
		else
		return 0;
	}
}