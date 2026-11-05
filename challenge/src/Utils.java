public class Utils {
    /**
     * This makes a lot of assumptions, it assumes that the temperature follows this format '(-)xx,x'
     * @param tempString temperature as a String
     * @return temperature as a double
     */
    public static double measurementsTempToDouble(String tempString) {
        double t = 0.0;
        boolean negative = tempString.charAt(0) == '-';
        int offset = negative ? 1 : 0;
        int commaPosition = tempString.charAt(offset + 1) == '.' ? offset + 1 :
                tempString.charAt(offset + 2) == '.' ? offset + 2 : 0;

        if (commaPosition == 0) {
            throw new RuntimeException("Temp doesn't follow format " + tempString);
        }

        for (int i = 1; i <= commaPosition - offset; i++) {
            switch (i - offset) {
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
}
