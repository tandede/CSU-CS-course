import java.util.Scanner;

interface StudentManageInterface {// interface 接口名
	public abstract void setFree(double fee);// 抽象方法

	public abstract double getFree();
}

interface TeacherManageInterface {
	public abstract double getPay();

	public abstract void setPay(double pay);
}

class Graduate implements StudentManageInterface, TeacherManageInterface {// 接口的实现implements
	private String name, sex;
	private int age;
	private double fee, pay;

	Graduate() {
	}

	Graduate(String name, String sex, int age, double fee, double pay) {
		this.name = name;
		this.sex = sex;
		this.age = age;
		this.fee = fee;
		this.pay = pay;
	}

	public String getName() {
		return name;
	}

	public String getSex() {
		return sex;
	}

	public int getAge() {
		return age;
	}

	public void setFree(double fee) {
		this.fee = fee;
	}

	public double getFree() {
		return fee;
	}

	public void setPay(double pay) {
		this.pay = pay;
	}

	public double getPay() {// 对接口的抽象方法必须重写
		return pay;
	}
}

public class main3 {
	public static void main(String[] args) {
		Scanner sc= new Scanner(System.in);
		System.out.println("请输入学生的姓名：");
		String name1 = sc.next();
		System.out.println("请输入学生的性别：");
		String sex1 = sc.next();
		System.out.println("请输入学生的年龄：");
		int age1 = sc.nextInt();
		System.out.println("请输入学生的学费：");
		int fee1 = sc.nextInt();
		System.out.println("请输入学生的工资：");
		int pay1 =sc.nextInt();
		Graduate gr = new Graduate(name1, sex1, age1, fee1, pay1);
		judgeLoan(gr);
		sc.close();;
	}

	public static void judgeLoan(Graduate gr) {// 对象作形参
		if (gr.getPay() * 12 - gr.getFree() * 2 < 2000) {
			System.out.println("You need a loan");
		} else
			System.out.println("You income is enough");
	}
}