using Range = (long Begin, long End);

var lines = await File.ReadAllLinesAsync("../../../../input/input.txt");

var seeds = lines[0].Split(":")[1]
    .Split(" ", StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
    .Select(long.Parse)
    .ToList();

List<List<Map>> maps = [];

for (int i = 1; i < lines.Length; ++i)
{
    var line = lines[i];
    if (line.Contains('-'))
    {
        List<Map> entry = [];
        ++i;
        while (i < lines.Length && !string.IsNullOrWhiteSpace(lines[i]))
        {
            var mapValues = lines[i].Split(" ", StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
                .Select(long.Parse)
                .ToList();
            entry.Add(
                new Map(
                    new Range(mapValues[1], mapValues[1] + mapValues[2] - 1),
                    new Range(mapValues[0], mapValues[0] + mapValues[2] - 1)
                    )
                );
            ++i;
        }
        maps.Add(entry);
    }
}
long result = long.MaxValue;

foreach (var seed in seeds)
{
    long currentValue = seed;
    foreach (var mapEntries in maps)
    {
        foreach (var map in mapEntries)
        {
            if (map.Source.Begin <= currentValue && map.Source.End >= currentValue)
            {
                currentValue = map.Target.Begin + (currentValue - map.Source.Begin);
                break;
            }
        }
    }
    result = Math.Min(result, currentValue);
}

File.WriteAllText("../../../../output/out_first.txt", result.ToString());

readonly struct Map(Range Source, Range Target)
{
    public readonly Range Source = Source;
    public readonly Range Target = Target;
}