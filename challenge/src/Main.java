public class Main {
    public static void main(String[] args) {
        MeasurementsProcessor processor = new MeasurementsProcessor();
        MeasurementsReader reader = new MeasurementsReader(processor);
        reader.read();
        processor.show();
    }
}
