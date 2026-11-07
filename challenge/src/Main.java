import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.*;

public class Main {

    public static void main(String[] args) throws ExecutionException, InterruptedException {
        long start = System.nanoTime();
        BlockingQueue<MyMap> outQueue = new LinkedBlockingQueue<>(1000);

        ExecutorService exec = Executors.newVirtualThreadPerTaskExecutor();

        List<Future<?>> processors = new ArrayList<>();
        for (int i = 0; i < Utils.WORKERS; i++) {
            MeasurementsProcessor processor = new MeasurementsProcessor(outQueue, exec);
            processors.add(processor.init(Utils.bounds[i], Utils.bounds[i + 1]));
        }


        OutputCollector collector = new OutputCollector(outQueue);
        Future<?> collectorOut = exec.submit(() -> {
            try {
                collector.compile();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });

        collectorOut.get();
        for (var p : processors) p.get();
        System.err.printf("\n\ntook %.3f s%n", (System.nanoTime() - start) / 1e9);
    }
}
