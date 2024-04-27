
public class Test{
   public static void main(String[] args) {
      long f=1;
      for(int i=1;i<10;i++)
      {
         int j=i;
         while(j>1)
         f*=j--;
         System.out.println(f);
      }
   }
}
