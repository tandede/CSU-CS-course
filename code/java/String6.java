import java.util.Scanner;;

public class String6 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入一串数字:");
        StringBuffer sb = new StringBuffer(scanner.next());
        int index = sb.indexOf(".") >= 0 ? sb.indexOf(".") : sb.length();

        for (int i = index - 3; i > 0; i -= 3) {
            sb.insert(i, ",");
        }
        System.out.println(sb.toString());
        scanner.close();
    }
}