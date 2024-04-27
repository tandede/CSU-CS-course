
import java.util.Scanner;
 
public class String3 {
 
	public static void main(String[] args) {
 
		Scanner in = new Scanner(System.in);
		System.out.print("请输入第一个字符串：");
		String num1 = in.next();
		System.out.print("请输入第二个字符串：");
		String num2 = in.next();
		
		num1=num1.replace("", "-"); //每个字符加个-
		String[] first=num1.split("-");
		num2=num2.replace("", "-"); //每个字符加个-
		String[] second=num2.split("-");
		
		for (int i = 0; i < first.length; i++) {
			for (int j = 0; j < second.length; j++) {
				if(first[i].equals(second[j])){
					num1=num1.replace(first[i], "");
				}
			}
		}
		System.out.println("删除后，第一个字符串为："+num1.replace("-", "" ));
		in.close();
		
	}
 
}