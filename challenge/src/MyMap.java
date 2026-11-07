import java.nio.charset.StandardCharsets;
import java.util.*;


public class MyMap {
    private static final int SIZE = 1 << 15;

    private final TempData[] data = new TempData[SIZE];
    private final List<String> namesList = new ArrayList<>();
    private final byte[][] keys = new byte[SIZE][];



    private int calcSlot(int hash) {
        int h = hash ^ (hash >>> 16);
        return h & (SIZE - 1);
    }

    private int findSlot(byte[] name, int len, int hash) {
        int slot = calcSlot(hash);
        while (keys[slot] != null && !Arrays.equals(keys[slot], 0, keys[slot].length, name, 0, len)) {
            slot = (slot + 1) & (SIZE - 1);
        }
        return slot;
    }

    public void processTemp(byte[] name, int len, int hash, double temp) {
        int slot = findSlot(name, len, hash);
        TempData dataPoint = data[slot];
        if (dataPoint == null) {
            keys[slot] = Arrays.copyOf(name, len);
            String s = new String(name, 0, len, StandardCharsets.UTF_8);   // once per station
            namesList.add(s);
            data[slot] = new TempData(temp, temp, temp, 1);
        } else {
            dataPoint.setMinMax(temp);
            dataPoint.incrementCount();
            dataPoint.addSum(temp);
        }
    }

    public TempData get(String name) {
        byte[] k = name.getBytes(StandardCharsets.UTF_8);
        return data[findSlot(k, k.length, hash(k))];
    }

    public void put(String name, TempData dataPoint) {
        byte[] k = name.getBytes(StandardCharsets.UTF_8);
        int slot = findSlot(k, k.length, hash(k));
        data[slot] = dataPoint;
        keys[slot] = k;
        namesList.add(name);
    }

    private static int hash(byte[] k) {
        int h = 0;
        for (byte b : k) h = 31 * h + b;
        return h;
    }

    public void merge(MyMap another) {
        for (String name : another.namesList) {
            TempData dataPoint = another.get(name);
            TempData old = get(name);
            if (old == null) {
                put(name, dataPoint);
            } else {
                old.setMin(Math.min(old.getMin(), dataPoint.getMin()));
                old.setMax(Math.max(old.getMax(), dataPoint.getMax()));
                old.setCount(dataPoint.getCount() + old.getCount());
                old.addSum(dataPoint.getSum());
            }
        }
    }

    public List<String> getNamesList() {
        return namesList;
    }
}
