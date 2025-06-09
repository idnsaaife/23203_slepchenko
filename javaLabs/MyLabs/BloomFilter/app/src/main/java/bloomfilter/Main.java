import java.main.bloomfilter;

public class Main {
    public static void main(String[] args) {
        String[] strings = { "abc", "xyz" };

        BloomFilter bloomFilter;

        for (String s : strings) {
            bloomFilter.add(s);
        }

        for (String s : strings) {
            System.out.println(bloomFilter.maybeContains(s));
        }

        System.out.println(bloomFilter.maybeContains("1234374"));
    }
}
