import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class MeasurementsReader {
    final String MEASUREMENTS_FILE = "measurements.txt";
    private final MeasurementsProcessor processor;

    public MeasurementsReader(MeasurementsProcessor processor) {
        this.processor = processor;
    }

    public void read() {
        try (BufferedReader reader = Files.newBufferedReader(Path.of(MEASUREMENTS_FILE), StandardCharsets.UTF_8)) {
            String line;
            while ((line = reader.readLine()) != null) {
                processor.process(line);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
