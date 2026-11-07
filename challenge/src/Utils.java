import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.LinkedList;
import java.util.List;

public class Utils {
    public static final List<String> STRING_POISON = new LinkedList<>();
    public static final MyMap OUT_POISON = new MyMap();
    public static final int WORKERS = 7;
    public static final int READER_QUEUE_BATCH_SIZE = 10_000;

    static FileChannel ch;
    static long[] bounds;

    static {
        try {
            ch = FileChannel.open(Path.of("measurements.txt"), StandardOpenOption.READ);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        try {
            bounds = split(ch);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    static long[] split(FileChannel ch) throws IOException {
        long size = ch.size();
        long[] bounds = new long[Utils.WORKERS + 1];
        bounds[Utils.WORKERS] = size;
        ByteBuffer one = ByteBuffer.allocate(1);
        for (int i = 1; i < Utils.WORKERS; i++) {
            long pos = size * i / Utils.WORKERS;
            while (pos < size) {
                one.clear();
                ch.read(one, pos++);
                if (one.get(0) == '\n') break;
            }
            bounds[i] = pos;
        }
        return bounds;
    }
}
