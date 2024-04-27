class Number implements Runnable {
    private int number = 1;// Object obj = new Object();

    public void run() {
        while (true) {
            synchronized (this) {// obj
                notify();
                if (number < 100) {
                    System.out.println(Thread.currentThread().getName() + ":" + number);
                    number++;
                    // try{wait();}
                    // catch(Exception ex){}
                } else {
                    break;
                }
            }
        }
    }
}

public class tee {
    public static void main(String[] args) {
        Number number = new Number();
        Thread t1 = new Thread(number);
        Thread t2 = new Thread(number);
        t1.setName("Thread 1");
        t2.setName("Thread 2");
        t1.start();
        t2.start();
    }
}