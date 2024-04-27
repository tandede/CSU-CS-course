import java.util.Scanner;

public class ThirdDemo {
 
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入圆的半径：");
        double r1 = sc.nextDouble();
        System.out.println("请输入圆柱的高：");
        double h1 = sc.nextDouble();
        Circle cir = new Circle(r1);
        cir.disp();
        Cylinder cyl = new Cylinder(r1,h1);
        cyl.disVol();
        sc.close();
    }
    
    private static class Circle{//圆Circle类
        private double radius;
        public Circle(){//构造方法，将半径置0
            radius = 0;
        }
        public Circle(double r){//构造方法，创建Circle对象时将半径初始化为r
            radius = r;
        }
        public double getRadius(){//获得圆的半径值
            return radius;
        }
        public double getPerimeter(){//获得圆的周长
            return 2*3.14159*radius;
        }
        public void disp(){//将圆的半径、圆的周长和圆的面积输出到屏幕
            System.out.println("圆的半径为："+radius);
            System.out.println("圆的周长为："+2*3.14159*radius);
            System.out.println("圆的面积为："+3.14159*radius*radius);
        }
    }
 
    public static class Cylinder extends Circle{//继承圆Circle类，派生圆柱体类Cylinder
        private double height;//圆柱体的高
        public Cylinder(){//构造方法
            super();
            height = 0;
        }
        public Cylinder(double r,double h){//构造方法
            super(r);
            height = h;
        }
        public double getHeight(){//获得圆柱体的高
            return height;
        }
        public double getVol(){//获得圆柱体的体积
            return 3.1415*super.getRadius()*super.getRadius()*height;
        }
        public void disVol(){//将圆柱体的体积输出到屏幕
            System.out.println("圆柱的体积为："+this.getVol());
        }
    }
}