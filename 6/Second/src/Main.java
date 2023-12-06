import java.io.*;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        try (var reader = new BufferedReader(new FileReader("../input/input.txt"))) {
            var timeLine = reader.readLine();
            var time = Long.parseLong(
                    Arrays.stream(
                            timeLine.split(":")[1].split(" ")
                    ).filter(x -> x != null && !x.isEmpty())
                    .reduce("", (x, y) -> x + y)
            );

            var distanceLine = reader.readLine();
            var distance = Long.parseLong(
                    Arrays.stream(
                            distanceLine.split(":")[1].split(" ")
                    ).filter(x -> x != null && !x.isEmpty())
                    .reduce("", (x, y) -> x + y)
            );

            long result = 0;
            for(int j = 0; j <= time; ++j) {
                if((time - j) * j > distance) {
                    ++result;
                }
            }
            try (var writer = new BufferedWriter(new FileWriter("../output/out_second.txt"))) {
                writer.write(Long.toString(result));
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}