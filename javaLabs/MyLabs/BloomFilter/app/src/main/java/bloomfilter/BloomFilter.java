import java.util.ArrayList;

interface MyHash {
    int hash(String s);
}

public class BloomFilter {
    private final int BIT_ARR_SIZE = 96;
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
            hashes.add(new MyHash() {
                @Override
                int hash(String s) {
                    return hashWithParams(s, hardcorePrimes[i], BIT_ARR_SIZE);
                }
            });
        }
    }

    public int hashWithParams(String s, int a, inr p) {
        int result = 0;
        for (char c : s.toCharArray()) {
            result += ((result + c) * a) % p;
        }
        return result;
    }

    public boolean maybeContains(String s) {
        boolean contains = true;
        for (int i = 0; i < hashFuncNumber; i++) {
            int hash = s.hashCode() * StrictMath.pow(HASH_CONST, i);
            int bitArrElem = hash / ARR_ELEM_SIZE;
            contains = ((bitArr[bitArrElem] & hash % 32) == (hash % 32));
            if (!contains) {
                return false;
            }
        }
        return true;
    }

    public void add(String s) {

        for (int i = 0; i < hashFuncNumber; i++) {
            int hash = s.hashCode() * StrictMath.pow(HASH_CONST, i);
            int bitArrElem = hash / ARR_ELEM_SIZE;
            bitArr[bitArrElem] = bitArr[bitArrElem] | (hash % 32);
        }
    }
}
