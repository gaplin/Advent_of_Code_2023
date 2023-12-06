import java.io.*;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        try (var reader = new BufferedReader(new FileReader("../input/input.txt"))) {
            var timeLine = reader.readLine();
            List<Long> times = Arrays.stream(
                    timeLine.split(":")[1].split(" ")
            ).filter(x -> x != null && !x.isEmpty())
                    .map(Long::parseLong)
                    .toList();

            var distanceLine = reader.readLine();
            List<Long> distances = Arrays.stream(
                            distanceLine.split(":")[1].split(" ")
                    ).filter(x -> x != null && !x.isEmpty())
                    .map(Long::parseLong)
                    .toList();

            long result = 1;
            for(int i = 0; i < times.size(); ++i) {
                var time = times.get(i);
                var distance = distances.get(i);
                var winningTimesCount = 0;
                for(int j = 0; j <= time; ++j) {
                    if((time - j) * j > distance) {
                        ++winningTimesCount;
                    }
                }
                result *= winningTimesCount;
            }
            try (var writer = new BufferedWriter(new FileWriter("../output/out_first.txt"))) {
                writer.write(Long.toString(result));
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}