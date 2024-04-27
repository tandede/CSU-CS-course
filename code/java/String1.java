import java.util.Scanner;

public class String1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入一个字符串：");
        String s = sc.next();
        StringBuffer sb = new StringBuffer();
        if (s != null) {
            for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if (Character.isLowerCase(c)) {
                    sb.append(Character.toUpperCase(c));
                } else if (Character.isUpperCase(c)) {
                    sb.append(Character.toLowerCase(c));
                }
                else
                {
                    sb.append(c);
                }
            }
            sc.close();
        }
        System.out.println(sb);
    }

}
