import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.concurrent.*;

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
                MappedByteBuffer bb = Utils.ch.map(FileChannel.MapMode.READ_ONLY, start, end - start);
                byte[] line = new byte[128];
                int len = 0;
                while (bb.hasRemaining()) {
                    byte b = bb.get();
                    if (b == '\n') {
                        data.processTemp(new String(line, 0, len, StandardCharsets.UTF_8));
                        len = 0;
                    } else {
                        line[len++] = b;
                    }
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
