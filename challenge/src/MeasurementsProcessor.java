import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

public class MeasurementsProcessor {
    Map<String, Double> averages = new TreeMap<>();
    Map<String, Long> averagesNum = new HashMap<>();
    Map<String, Double> mins = new HashMap<>();
    Map<String, Double> maxes = new HashMap<>();

    public void process(String line) {
        int index = line.indexOf(';');
        String city = line.substring(0, index);
        String tempString = line.substring(index + 1);
        double temp = Utils.measurementsTempToDouble(tempString);

        // determining the min
        if (!mins.containsKey(city) || mins.get(city) > temp) {
            mins.put(city, temp);
        }

        // determining the max
        if (!maxes.containsKey(city) || maxes.get(city) < temp) {
            maxes.put(city, temp);
        }

        // determining the avg
        if (!averages.containsKey(city)) {
            averagesNum.put(city, 1L);
            averages.put(city, temp);
        } else {
            Long num = averagesNum.get(city);
            averagesNum.compute(city, (k, n) -> n + 1L);
            averages.compute(city, (k, v) -> (1.0 / (num + 1)) * (num * v + temp));
        }
    }

    public void show() {
        for (String city: averages.keySet()) {
            System.out.printf("%s=%.1f/%.1f/%.1f\n", city, mins.get(city), averages.get(city), maxes.get(city));
        }
    }
}
