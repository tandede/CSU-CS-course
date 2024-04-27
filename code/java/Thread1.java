import java.util.Date;
import java.util.Random;

public class Thread1 extends Thread {

    private String name;

    public Thread1(String n) {
        name = n;
    }

    public void run() {
        Date date = new Date();
        System.out.println(this.name + "开始于：" + date);
        Random rand = new Random();
        int randnum = rand.nextInt(100, 10000);
        try {
            Thread.sleep(randnum);
            Date date2 = new Date();
            System.out.println(this.name + "结束于：" + date2);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    public static void main(String[] args) {

        Thread1 mThread1 = new Thread1("线程1");
        Thread1 mThread2 = new Thread1("线程2");
        Thread1 mThread3 = new Thread1("线程3");

        mThread1.start();
        mThread2.start();
        mThread3.start();
    }
}