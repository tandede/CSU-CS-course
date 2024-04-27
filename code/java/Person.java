import java.util.Scanner;

public class Person {
    public int Age;
    public String name;
    public String sex;

    public int getAge() {
        return Age;
    }

    public static void main(String[] args) throws IllegalAgeException {
        Person p = new Person();
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入年龄：");
        int age1 = sc.nextInt();
        p.setAge(age1);
        System.out.println("请输入年龄：");
        int age2 = sc.nextInt();
        p.setAge(age2);
        sc.close();
    }

    public void setAge(int age) throws IllegalAgeException {
        if (age < 1 || age > 150) {
            throw new IllegalAgeException("年龄应设置为1~150直接");
        } else
            this.Age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSex() {
        return sex;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }
}

class IllegalAgeException extends Throwable {
    public IllegalAgeException(String msg) {
        super(msg);
    }
}
