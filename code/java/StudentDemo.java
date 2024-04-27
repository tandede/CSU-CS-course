import java.util.Scanner;

public class StudentDemo{
	 public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入本科生的姓名：");
        String name1 = sc.next();
        System.out.println("请输入本科生的学号：");
        int ID1 =sc.nextInt();
        System.out.println("请输入本科生的三门课的成绩：");
        double c1=sc.nextDouble();
        double c2=sc.nextDouble();
        double c3=sc.nextDouble();
		Undergraduate U=new Undergraduate(name1,ID1,c1,c2,c3);
		U.dispass();
        System.out.println("请输入研究生的姓名：");
        String name2 = sc.next();
        System.out.println("请输入本科生的学号：");
        int ID2 =sc.nextInt();
        System.out.println("请输入研究生的三门课的成绩：");
        double d1=sc.nextDouble();
        double d2=sc.nextDouble();
        double d3=sc.nextDouble();
		Graduate P=new Graduate(name2,ID2,d1,d2,d3);
		P.dispass();
        sc.close();
	 }	
    private static class Student {
	private String name;
    private int ID;
	private double class1,class2,class3;
	public Student(String name,int ID,double class1,double class2,double class3) {
		this.name=name;
        this.ID=ID;
		this.class1=class1;
		this.class2=class2;
		this.class3=class3;
	}
public int getID()
{
    return ID;
}
public String getName() {
	return name;
}
public double getAverage() {
	return (class1+class2+class3)/3;
}
	}
 //本科生类
 public static class Undergraduate extends Student{
	 public Undergraduate(String name,int ID,double class1,double class2,double class3) {
		 super(name,ID,class1,class2,class3);
	 }
	 public void dispass() {
		 if(getAverage()>=60)
			 System.out.println("本科生"+getName()+"学号"+getID()+" 平均分："+getAverage()+",可以拿到学士学位");
		 else
			 System.out.println("本科生"+getName()+"学号"+getID()+" 三科平均分："+getAverage()+",不能拿到学士学位");
	 }
 }
 //研究生
 public static class Graduate extends Student{
	 public Graduate(String name,int ID,double class1,double class2,double class3) {
		 super(name,ID,class1,class2,class3);
	 }
	 public void dispass() {
		 if(getAverage()>=80)
			 System.out.println("研究生"+getName()+" 学号"+getID()+" 三科平均分："+getAverage()+",可以拿到硕士学位");
		 else
			 System.out.println("研究生"+getName()+" 学号"+getID()+" 三科平均分："+getAverage()+",不能拿到硕士学位");
	 }
 }
}
