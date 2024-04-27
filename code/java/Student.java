public class Student {
    int sNo;
	String sName;
	String sSex;
	int sAge;
	int sJava;
	public Student(int no,int age,String Name,String sex,int java){
		super();
		sNo = no;
		sName = Name;
		sSex = sex;
		sAge = age;
		sJava = java;
	}
	public int getNo(){
		return sNo;
	}
	public String getName(){
		return sName;
	}
	public String getSex(){
		return sSex;
	}
	public int getAge(){
		return sAge;
	}
	public int getJava(){
		return sJava;
	}
	public static void main(String[] args){
		int min=100,max=0;
        Student[] s =new Student[2];
        s[0] = new Student(222,22,"多的","男",99);
        s[1] = new Student(22,22,"少的","男",29);
        for(int i=0;i<s.length;i++){
			System.out.println("学号："+s[i].sNo+" 年龄："+s[i].sAge+" "+s[i].sName+" "+s[i].sSex+" "+s[i].sJava);}
        System.out.println("两名同学的平均成绩为："+(s[0].sJava+s[1].sJava)/2);
		Student[] sd = new Student[5];
		sd[0] = new Student(1,18,"张三","女",85);
		sd[1] = new Student(2,19,"李四","男",86);
		sd[2] = new Student(3,20,"王五","女",87);
		sd[3] = new Student(4,21,"赵六","男",88);
		sd[4] = new Student(5,22,"孙七","女",89);
		for(int i=0;i<sd.length;i++){
			System.out.println("学号："+sd[i].sNo+" 年龄："+sd[i].sAge+" "+sd[i].sName+" "+sd[i].sSex+" "+sd[i].sJava);
			if(sd[i].sJava<min){
				min = sd[i].sJava;
			}
			if(sd[i].sJava>max){
				max = sd[i].sJava;
			}
		}
		System.out.println("五名同学中最小值是："+min+"  最大值是："+max);
	}
}
