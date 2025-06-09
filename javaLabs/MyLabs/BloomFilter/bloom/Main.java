
public class Main {
    public static void main(String[] args) throws Exception {
        ThreadPool threadPool = new ThreadPool(100);

        for (int i = 0; i < 100; ++i) {
            threadPool.addTaskToQueue(() -> {
                System.out.println("I am thread id = " + Thread.currentThread().getId());
            });
        }

        threadPool.run();
        for (int i = 0; i < 100; ++i) {
            threadPool.addTaskToQueue(() -> {
                System.out.println("I am thread id = " + Thread.currentThread().getId());
            });
        }
        //threadPool.joinAll();
        Thread.currentThread().sleep(1000);
        threadPool.stopThreadPool();
    }
}
