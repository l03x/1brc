import java.util.Collections;
import java.util.List;
import java.util.concurrent.BlockingQueue;

public class OutputCollector {
    private final BlockingQueue<MyMap> inQueue;
    private final MyMap data = new MyMap();

    public OutputCollector(BlockingQueue<MyMap> inQueue) {
        this.inQueue = inQueue;
    }

    void compile() throws InterruptedException {
        int finished = 0;
        while (finished < Utils.WORKERS) {
            MyMap item = inQueue.take();
            if (item.equals(Utils.OUT_POISON)) {
                finished++;
                continue;
            };

            data.merge(item);
        }

        List<String> list = data.getNamesList();
        Collections.sort(list);
        System.out.print("{");
        String name;
        for (int i = 0; i < list.size() - 1; i++) {
            name = list.get(i);
            System.out.printf("%s=%s, ", name, data.get(name));
        }
        name = list.getLast();
        System.out.printf("%s=%s}", name, data.get(name));
    }
}
