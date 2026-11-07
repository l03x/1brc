import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

public class MeasurementsProcessor {
    private final BlockingQueue<MyMap> outQueue;
    private final ExecutorService exec;

    public MeasurementsProcessor(BlockingQueue<MyMap> outQueue, ExecutorService exec) {
        this.outQueue = outQueue;
        this.exec = exec;
    }

    Future<?> init(long start, long end) {
        return exec.submit(() -> {
            MyMap data = new MyMap();

            try {
                MappedByteBuffer chunk = Utils.ch.map(FileChannel.MapMode.READ_ONLY, start, end - start);
                byte[] stationName = new byte[128];

                while (chunk.hasRemaining()) {
                    int nameLength = 0;
                    int nameHash = 0;
                    byte current;

                    while ((current = chunk.get()) != ';') {
                        stationName[nameLength++] = current;
                        nameHash = 31 * nameHash + current;
                    }

                    boolean negative = false;
                    int tenths = 0;

                    while ((current = chunk.get()) != '\n') {
                        if (current == '-') negative = true;
                        else if (current != '.') tenths = tenths * 10 + (current - '0');
                    }

                    double temperature = (negative ? -tenths : tenths) / 10.0;
                    data.processTemp(stationName, nameLength, nameHash, temperature);
                }
            } catch (IOException e) {
                throw new UncheckedIOException(e);
            }

            try {
                outQueue.put(data);
                outQueue.put(Utils.OUT_POISON);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
    }
}
