public class Thread2 {
    public static void main(String[] args) throws InterruptedException {
        NewOneThread one = new NewOneThread();
        one.start();
        TwoThread two = new TwoThread();
        two.start();
    }

    /**
     * 求100以内素数，求出后休眠一个随机时间
     */
    public static class NewOneThread extends Thread {
        public NewOneThread() {
            super();
        }

        public NewOneThread(String str) {
            super(str);
        }

        public void run() {
            System.out.println("100以内素数:1");
            System.out.println("100以内素数:2");
            System.out.println("100以内素数:3");
            for (int i = 4; i <= 100; i++) {
                for (int j = 2; j <= i / 2; j++) {
                    if (i % j == 0) {
                        break;
                    }
                    if (j == i / 2) {
                        System.out.println("100以内素数:" + i);
                    }
                }
            }
            long time = (long) (1000 + Math.random() * 3000);
            System.out.println("100以内素数计算完毕，该线程将休眠" + time + "毫秒");
            try {
                super.sleep(time);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
            System.out.println("100以内素数，该线程结束");
        }
    }

    /**
     * 求100以内能被3整除的数，求出后休眠一个随机时间
     */
    public static class TwoThread extends Thread {
        public TwoThread() {
            super();
        }

        public TwoThread(String str) {
            super(str);
        }

        public void run() {
            for (int i = 0; i <= 100; i++) {
                if (i % 3 == 0) {
                    System.out.println("被3整除的数:" + i);
                }
            }
            long time = (long) (1000 + Math.random() * 3000);
            System.out.println("100以内能被3整除的数计算完毕，该线程将休眠" + time + "毫秒");
            try {
                super.sleep(time);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
            System.out.println("100以内能被3整除的数，该线程结束");
        }
    }
}