import java.util.Scanner;

public class tielu {
    public static void main(String[] args) {
        Scanner input= new Scanner(System.in);
        double weight;//货物重量(t)
        double distance;//路程(km)
        double freight = 0;//运费（元）
        System.out.println("请输入货物重量(t)和路程(km):");
        weight = input.nextDouble();
        distance = input.nextDouble();
        if(distance <= 100)freight = weight * distance * 1.0;
        else if(distance > 100 && distance <= 300)freight = weight * distance * 0.9;
        else if(distance > 300 && distance <= 500)freight = weight * distance * 0.8;
        else if(distance > 500 && distance <= 1000)freight = weight * distance * 0.7;
        else if(distance > 1000)freight = weight * distance * 0.6;
        System.out.println("需要的运费为："+freight+"元");
        input.close();
    }
    
}
