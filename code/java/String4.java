
import java.util.Scanner;

public class String4 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("请输入字符串：");
        String s = scan.nextLine();
        StringBuilder sb = new StringBuilder(s);
        for (int i = 0; i < sb.length() - 1; i++) {
            for (int j = i + 1; j < sb.length(); j++) {
                if (sb.charAt(i) == sb.charAt(j)) {
                    sb.deleteCharAt(j);
                    j--;
                }
            }
        }
        System.out.println("删除后的字符串: " + sb);
        scan.close();
    }
}
