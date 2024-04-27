import java.util.Scanner;
public class npan {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.print("请输入需要判断的数字：");
        try{
            int a = Integer.parseInt(sc.nextLine());
        if(a>0&&a<=9999)
            System.out.println("这是一个"+determine(a)+"位数");
        else
         System.out.println("出现异常，数字溢出！"); 
        } 
    catch (NumberFormatException e) {
        System.out.println("出现异常，输入非数字！");
    } 
    sc.close();
    }
        
    public static int determine(int a){
        int s=0;
        int n=a;
        while (n>0){
            s++;
            n/=10;
        }
        return s;
        
    }
}