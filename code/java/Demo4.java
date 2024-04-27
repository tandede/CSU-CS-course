// import java.util.Scanner;

// public class Demo4 {
//     public static void main(String[] args) {
//         Scanner sc = new Scanner(System.in);
//         Square[] squares = new Square[5];

//         for (int i = 0; i <5; i++) {
//             System.out.println("矩形:"+(i+1));
//             System.out.print("\t请输入矩形的宽: ");
//             double width = sc.nextDouble();
//             System.out.print("\t请输入矩形的高: ");
//             double height = sc.nextDouble();
//             System.out.print("\t请输入矩形的颜色: ");
//             String color = sc.next();
//             System.out.print("\t请输入矩形是否被填充（true/false）: ");
//             boolean filled = sc.nextBoolean();
//             squares[i] = new Square(width, height, color, filled);
//         }

//         for (int i = 0; i < 5; i ++) {
//             System.out.println(squares[i].toString());
//             System.out.println();
//         }
//         sc.close();

//     }
//     private static abstract class Shape
//     {
//         public abstract double getArea();
//     }
//     interface Colorable {
//         public abstract void howToColor();
//     }
//     private static class Square extends Shape implements Colorable {
//         private double width;
//         private double height;
//         private boolean filled;
//         private String color1;
//         public Square(double width, double height, String color, boolean filled) {
//             this.color1 = color;
//             this.filled = filled;
//             this.width = width;
//             this.height = height;
//         }
//         public double getArea() {
//             return width * height;
//         }
//         public double getPerimeter() {
//             return 2 * (width + height);
//         }
    
//         @Override
//         public void howToColor() {
//             System.out.println("给所有的四条边着色");
//         }
//         public String toString() {
//             if (filled) {
//                 howToColor();
//             }
//             return "color:"+ color1 + "\nFilled " + filled;
//         }
//     }
//     private static class Rectangle extends Shape
//     {
//         private double length,width;
//         public Rectangle(double length, double width)
//         {
//             this.length=length;
//             this.width=width;
//         }
//         @Override
//         public double getArea()
//         {
//             return length*width;
//         }
//     }
//     private static class Circle extends Shape
//     {
//         private double radius;
//         public Circle(double radius)
//         {
//             this.radius= radius;
//         }
//         @Override
//         public double getArea()
//         {
//             return 3.14159*radius*radius;
//         }
//     }
//     private static class ComparableCircle extends Circle implements Comparable<ComparableCircle> {
//         public ComparableCircle(double radius) {
//             super(radius);
//         }
    
//         public Object max(ComparableCircle o1, ComparableCircle o2) {
//             if (o1.compareTo(o2) > 0)
//                 return o1;
//             else
//                 return o2;
//         }
//         public int compareTo(ComparableCircle o) {
//             if (super.getArea() > o.getArea())
//                 return 1;
//             else if (super.getArea() < o.getArea())
//                 return -1;
//             else
//                 return 0;
//         }
//     }
//      private static class Triangle extends Shape {
//         private double side1;
//         private double side2;
//         private double side3;
//         private boolean filled;
//         private String color;
//         public Triangle(double s1, double s2, double s3,boolean fill1,String color1) {

//             this.side1 = s1;
//             this.side2 = s2;
//             this.side3 = s3;
//             this.filled=fill1;
//             this.color=color1;
//         }  
//         public double getSide1() {
//             return side1;
//         }
    
//         public double getSide2() {
//             return side2;
//         }
    
//         public double getSide3() {
//             return side3;
//         }
    
//        public String getcolor()
//        {
//         return color;
//        }
//        public boolean getfill()
//        {
//         return filled;
//        }
//        @Override
//         public double getArea() {
//             double s = (side1 + side2 + side3) / 2;
//             return Math.pow(s * (s - side1) * (s - side2) * (s - side3),0.5);
            
//         }
//         public double getPerimeter() {
//             return side1 + side2 + side3;
//         }
//         public void disp()
//         {
//             if((getSide1()+getSide2())<=getSide3()||(getSide3()+getSide2())<=getSide1()||(getSide1()+getSide3())<=getSide2())
//             {
//                 System.out.println("您输入的三条边不能构成三角形");
//             }
//             else
//             {//面积、周长、颜色以及真或者假来表明是否被填充。
//                 System.out.println("三角形的面积是："+getArea()+"周长是："+getPerimeter()+"颜色为："+getcolor()+"是否填充"+getfill());
//             }
//         }
// }
// }