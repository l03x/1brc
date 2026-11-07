import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.charset.StandardCharsets;
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
            bounds = split(ch, WORKERS);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * This makes a lot of assumptions, it assumes that the temperature follows this format '(-)xx,x'
     * @param tempString temperature as a String
     * @return temperature as a double
     */
    public static double measurementsTempToDouble(String tempString, int startIndex) {
        double t = 0.0;
        boolean negative = tempString.charAt(startIndex) == '-';
        int offset = negative ? 1 : 0;
        int base = startIndex + offset;
        int commaPosition = tempString.charAt(base + 1) == '.' ? base + 1 :
                tempString.charAt(base + 2) == '.' ? base + 2 : 0;

        if (commaPosition == 0) {
            throw new RuntimeException("Temp doesn't follow format " + tempString);
        }

        for (int i = 1; i <= commaPosition - base; i++) {
            switch (i - 1) {
                case 0:
                    t += tempString.charAt(commaPosition - i) - '0';
                    break;
                case 1:
                    t += (tempString.charAt(commaPosition - i)  - '0') * 10;
                    break;
            }
        }

        t += (tempString.charAt(commaPosition + 1) - '0') * 0.1;
        return negative ? -1 * t : t;
    }

    public static IndexReturn index(String string, char c) {
        int i = string.indexOf(c);
        if (i < 0) i = string.length();
        String name = string.substring(0, i);
        return new IndexReturn(i, name.hashCode(), name);
    }

    static long[] split(FileChannel ch, int n) throws IOException {
        long size = ch.size();
        long[] bounds = new long[n + 1];
        bounds[n] = size;
        ByteBuffer one = ByteBuffer.allocate(1);
        for (int i = 1; i < n; i++) {
            long pos = size * i / n;
            while (pos < size) {
                one.clear();
                ch.read(one, pos++);
                if (one.get(0) == '\n') break;
            }
            bounds[i] = pos;
        }
        return bounds;
    }

    public static int hash(String str) {
        return str.hashCode();
    }
}
