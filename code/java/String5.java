import java.util.Scanner;

public class String5 {
	static Scanner sc = new Scanner(System.in);
	public static void main(String[] args) {
		System.out.println("请输入原字符串：");
		String st = sc.next();
		System.out.println("请输入指定字符串：");
		String M = sc.next();
		search(st,M);
        sc.close();
	}
	public static void search(String st,String M) {
		int count = 0;
		while(st.indexOf(M)>=0) {
			st=st.substring(st.indexOf(M)+M.length());
			count++;
		}
		System.out.println("指定字符串在原字符串中出现："+count+"次");
	}
	
}