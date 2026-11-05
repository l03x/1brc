import java.util.HexFormat;

public class Main {
    public static void main(String[] args) {
        long start = System.nanoTime();

        MeasurementsProcessor processor = new MeasurementsProcessor();
        MeasurementsReader reader = new MeasurementsReader(processor);
        reader.read();
        processor.show();

        System.err.printf("\n\ntook %.3f s%n", (System.nanoTime() - start) / 1e9);
    }
}
