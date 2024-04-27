// import java.io.*;
// import java.util.Scanner;

// public class ExceptionSeven {
//     //  问题一
//     //  求2~200之间的所有素数，将求得的结果保存到PRIME.DAT文件中
//     public void One() throws FileNotFoundException, IOException {
//         FileOutputStream fos = new FileOutputStream("C:\\Users\\Dell\\Desktop\\code\\java\\PRIME.DAT");
//         int temp = 2;
//         fos.write(String.valueOf(temp).getBytes());
//         fos.write(" ".getBytes());
//         temp = 3;
//         fos.write(String.valueOf(temp).getBytes());
//         fos.write(" ".getBytes());
//         for (int i = 3; i <= 100; i++) {
//             for (int j = 2; j <= i / 2; j++) {
//                 if (i % j == 0) {
//                     break;
//                 }
//                 if (j == i / 2) {
//                     fos.write(String.valueOf(i).getBytes());
//                     fos.write(" ".getBytes());
//                 }
//             }
//         }
//         fos.close();
//     }

//     //  问题二
//     //  检查C盘根目录下CONFIG..SYS文件是否存在，
//     //  若在则显示该文件的名称和内容。
//     public void Two() throws FileNotFoundException, IOException {
//         String filePath1 = "C:\\CONFIG.SYS";
//         String filePath3 = "C:\\Users\\Dell\\Desktop\\code\\java\\PRIME.DAT";
//         File fi1 =new File(filePath1);
//         if (fi1.exists()) {
//             System.out.println("文件名称为：" + fi1.getName());
//             FileInputStream fis = new FileInputStream(fi1);
//             byte[] data = new byte[(int) fi1.length()];
//             fis.read(data);
//             fis.close();
//             String msg = new String(new String(data));
//             System.out.println("文件内容为：");
//             System.out.println(msg);
//         } else {
//             System.out.println("文件不存在");
//         }
//         File fi = new File(filePath3);

//         if (fi.exists()) {
//             System.out.println("文件名称为：" + fi.getName());
//             FileInputStream fis = new FileInputStream(fi);
//             byte[] data = new byte[(int) fi.length()];
//             fis.read(data);
//             fis.close();
//             String msg = new String(new String(data));
//             System.out.println("文件内容为：");
//             System.out.println(msg);
//         } else {
//             System.out.println("文件不存在");
//         }
//     }

//     public void ThreeAndFour() throws FileNotFoundException, IOException {
//         // 五名学生的信息：
//         int i, j;
//         int sum = 0;
//         String[] Sno = new String[5];
//         String[] Name = new String[5];
//         double[][] Score = new double[5][3];
//         double[] sumScore = new double[5];
//         Scanner sc=new Scanner(System.in);
//         for (i = 0; i < 5; i++) {
//             System.out.println("请输入第"+(i+1)+"个学生的学号：");
//             String sno=sc.next();
//             Sno[i]=sno;
//             System.out.println("请输入第"+(i+1)+"个学生的姓名：");
//             String name=sc.next();
//             Name[i]=name;
//             for (j = 0; j < 3; j++) {
//                 System.out.println("请输入第"+(i+1)+"个学生的第"+(j+1)+"科成绩：");
//                 double score= sc.nextDouble();
//                 Score[i][j]=score;
//                 sum += Score[i][j];
//             }
//             sumScore[i] = sum;
//             sum = 0;
//         }
//         sc.close();
//         // 五名学生的学号、姓名、总成绩存入文件中
//         String filePath = "C:\\Users\\Dell\\Desktop\\code\\java\\STUDENT.DAT";
//         File file = new File(filePath);
//         OutputStream fos = new FileOutputStream(file);
//         DataOutputStream dos = new DataOutputStream(fos);
//         for (i = 0; i < 5; i++) {
//             dos.writeUTF(Sno[i]);
//             dos.writeUTF(Name[i]);
//             dos.writeDouble(sumScore[i]);
//         }
//         dos.close();
        
//         // 读取数据
//         String[] newSno = new String[5];
//         String[] newName = new String[5];
//         double[] newSum = new double[5];
//         InputStream fis = new FileInputStream(file);
//         DataInputStream dis = new DataInputStream(fis);
//         double max=0;
//         String maxsno="";
//         String maxname="";
//         for (i = 0; i < 5; i++) {
//             newSno[i] = dis.readUTF();
//             newName[i] = dis.readUTF();
//             newSum[i] = dis.readDouble();
//             if(newSum[i]>max)
//             {
//                 max=newSum[i];
//                 maxsno=newSno[i];
//                 maxname=newName[i];
//             }
//         }
//         System.out.print("最高分的学号为："+maxsno + " 姓名为：" + maxname + " 平均分为：");
//         System.out.printf("%.1f\n", max / 3.0);
//         dis.close();
//     }

//     public static void main(String[] args) throws IOException {
//         ExceptionSeven exec = new ExceptionSeven();
//         exec.One();
//         exec.Two();
//         exec.ThreeAndFour();
        
//     }

// }