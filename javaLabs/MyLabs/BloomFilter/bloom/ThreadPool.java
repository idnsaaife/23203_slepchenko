import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class ThreadPool {

    private Queue<Runnable> taskQueue = new LinkedList<>();
    ArrayList<Thread> threads = new ArrayList<>();
    private int numThreads;

    class WorkerThread implements Runnable {
        @Override
        public void run() {
            while (!Thread.currentThread().isInterrupted()) {
                Runnable task;
                synchronized (taskQueue) {
                    if (taskQueue.isEmpty()) {
                        try {
                            taskQueue.wait();
                        } catch (InterruptedException e) {

                        }
                        
                        continue;
                    }
                    task = taskQueue.poll();
                }
                task.run();
            }
        }
    }

    public ThreadPool(int numThreads) {
        this.numThreads = numThreads;
        assert (numThreads > 0);
        threads = new ArrayList<>(numThreads);
    }

    public void addTaskToQueue(Runnable r) {
        synchronized (taskQueue) {
            taskQueue.add(r);
            taskQueue.notify();
        }
    }

    public void run() {
        for (int i = 0; i < numThreads; i++) {
            Thread t = new Thread(new WorkerThread());
            threads.add(t);
        }

        for (int i = 0; i < numThreads; i++) {
            Thread t = threads.get(i);
            t.start();
        }
    }

    public void joinAll() {
        for (int i = 0; i < numThreads; i++) {
            Thread t = threads.get(i);
            try {
                t.join();
            } catch (InterruptedException e) {

            }
        }
    }

    public void stopThreadPool() {
        for (int i = 0; i < numThreads; i++) {
            Thread t = threads.get(i);
            t.interrupt(); //!!!!!!!!!!!!!! не убивает не тормозит просто взводит флаг ОСТАНОВИСЬ ПОЖАЛУЙСТА
        }
    }

}
