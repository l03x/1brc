import java.util.*;


public class MyMap {
    private static final int SIZE = 1 << 15;

    private final TempData[] data = new TempData[SIZE];
    private final String[] names = new String[SIZE];
    private final List<String> namesList = new ArrayList<>();


    private int calcSlot(int hash) {
        int h = hash ^ (hash >>> 16);
        return h & (SIZE - 1);
    }

    private int findSlot(String name, int hash) {
        int slot = calcSlot(hash);
        while (names[slot] != null && !names[slot].equals(name)) {
            slot = (slot + 1) & (SIZE - 1);
        }
        return slot;
    }

    public void processTemp(String tempString) {
        IndexReturn r = Utils.index(tempString, ';');
        int slot = findSlot(r.name(), r.hash());
        double temp = Utils.measurementsTempToDouble(tempString, r.index() + 1);

        TempData dataPoint = data[slot];
        if (dataPoint == null) {
            names[slot] = r.name();
            namesList.add(r.name());
            data[slot] = new TempData(temp, temp, temp, 1);
        } else {
            dataPoint.setMinMax(temp);
            dataPoint.incrementCount();
            dataPoint.addSum(temp);
        }
    }

    public TempData get(String name) {
        int slot = findSlot(name, Utils.hash(name));
        return data[slot];
    }

    public void put(String name, TempData dataPoint) {
        int slot = findSlot(name, Utils.hash(name));
        data[slot] = dataPoint;
        names[slot] = name;
        namesList.add(name);
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
