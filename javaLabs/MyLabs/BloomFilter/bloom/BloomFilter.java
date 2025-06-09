import java.util.ArrayList;

interface MyHash {
    public int hash(String s);
}

public class BloomFilter {
    private final int BIT_ARR_SIZE = 32000;
    private final int ARR_ELEM_SIZE = 32;
    private final int HASH_CONST = 31;
    private final int hashFuncNumber = 3;
    private int[] bitArr = new int[BIT_ARR_SIZE / 32];

    private final int[] hardcorePrimes = new int[hashFuncNumber];
    {
        hardcorePrimes[0] = 3;
        hardcorePrimes[1] = 5;
        hardcorePrimes[2] = 7;
    }

    private ArrayList<MyHash> hashes = new ArrayList<>();
    {
        for (int i = 0; i < hashFuncNumber; i++) {
            final int prime = hardcorePrimes[i];
            hashes.add(new MyHash() {
                @Override
                public int hash(String s) {
                    return hashWithParams(s, prime, BIT_ARR_SIZE);
                }
            });
        }
    }

    /*MyHash h = (s) -> {
        return hashWithParams(s, x, BIT_ARR_SIZE);
    };*/
    public int hashWithParams(String s, int a, int p) {
        int result = 0;
        for (char c : s.toCharArray()) {
            result += ((result + c) * a) % p;
        }
        return result;
    }

    public boolean maybeContains(String s) {
        for (MyHash hashFunction : hashes) {
            int hash = hashFunction.hash(s);
            int bitArrElem = hash / ARR_ELEM_SIZE;
            int bitPos = hash % ARR_ELEM_SIZE;
            if ((bitArr[bitArrElem] & (1 << bitPos)) == 0) {
                return false;
            }
        }
        return true;
    }

    public void add(String s) {
        for (MyHash hashFunction : hashes) {
            int hash = hashFunction.hash(s);
            int bitArrElem = hash / ARR_ELEM_SIZE;
            int bitPos = hash % ARR_ELEM_SIZE;
            bitArr[bitArrElem] |= (1 << bitPos);
        }
    }
}
