import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

//lock, myspinlock

//свой примитив синхронизации

class MyLock {
    //volatile boolean flag = false;
    AtomicBoolean atomicFlag = new AtomicBoolean(false);
    void lock() {
       while (atomicFlag.compareAndSet(false, true) == false);
       // atomicFlag.set(true);
        

    }

    void unlock() {
        atomicFlag.set(false);
        //atomicFlag.compareAndSet(true,false);
    }
}

public class ParallelInt {
    static int X = 0;

    static class MyRunnable implements Runnable {
        @Override
        public void run() {
            long id = Thread.currentThread().getId();
            // System.out.println(id);
            // System.out.println("Hello from Thread id = " + id);
            for (int i = 0; i < NUM_ITERATIONS; ++i) {
                lock.lock();
                X++;
                lock.unlock();
                // synchronized (monitor) {
                //ATOMIC_X.incrementAndGet();
                // }
            }
        }
    }

    static final int NUM_THREADS = 100;
    static final int NUM_ITERATIONS = 10000;
    // static final Object monitor = new Object();
    static final AtomicInteger ATOMIC_X = new AtomicInteger();
    static MyLock lock = new MyLock();
    public static void main(String[] args) throws Exception {
        long id = Thread.currentThread().getId();
        System.out.println(id);

        ArrayList<Thread> threads = new ArrayList<>();
        for (int i = 0; i < NUM_THREADS; ++i) {
            Thread t = new Thread(new ParallelInt.MyRunnable());
            threads.add(t);
        }

        long timestamp = System.currentTimeMillis();
        for (int i = 0; i < NUM_THREADS; ++i) {
            threads.get(i).start();
            // threads.get(i).join();
        }

        for (int i = 0; i < NUM_THREADS; ++i) {
            // threads.get(i).start();
            threads.get(i).join();
        }

        long time = System.currentTimeMillis() - timestamp;
        System.out.println("Result = " + X + " time = " + time);

    }
}

// volatile модель памяти, если переменная будет модифицирована то резульиаи
// этой операции точно будет виден другим потокам