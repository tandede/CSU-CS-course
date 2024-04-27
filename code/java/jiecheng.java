public class jiecheng {
    public static void main(String[] args) {
        int sum=0;
        int x=1;
        for(int i=1;i<=10;i++)
        {
            x*=i;
            sum+=x;
        }
        System.out.println("阶乘之和为："+sum);
    }
}
