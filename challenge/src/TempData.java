
public class TempData {
    private double min;
    private double max;
    private double sum;
    private int count;

    public TempData(double min, double max, double sum, int count) {
        this.min = min;
        this.max = max;
        this.sum = sum;
        this.count = count;
    }

    public double getMin() {
        return min;
    }

    public void setMin(double min) {
        this.min = min;
    }

    public double getMax() {
        return max;
    }

    public void setMax(double max) {
        this.max = max;
    }

    public double getSum() {
        return sum;
    }

    public void setSum(double sum) {
        this.sum = sum;
    }

    public void addSum(double temp) {
        this.sum += temp;
    }

    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
    }

    public void incrementCount() {
        this.count += 1;
    }

    public void setMinMax(double temp) {
        if (temp < min) {
            min = temp;
        } else if (temp > max) {
            max = temp;
        }
    }

    @Override
    public String toString() {
        return String.format("%.1f/%.1f/%.1f", min, sum/count, max);
    }
}
