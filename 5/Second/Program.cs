using Range = (long Begin, long End);

var lines = await File.ReadAllLinesAsync("../../../../input/input.txt");

var seeds = lines[0].Split(":")[1]
    .Split(" ", StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
    .Select(long.Parse)
    .ToList();

List<MapEntry> maps = [];

var level = -1;
for (int i = 1; i < lines.Length; ++i)
{
    var line = lines[i];
    if (line.Contains('-'))
    {
        level += 1;
        ++i;
        while (i < lines.Length && !string.IsNullOrWhiteSpace(lines[i]))
        {
            var mapValues = lines[i].Split(" ", StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
                .Select(long.Parse)
                .ToList();
            var map =
                new Map(
                    new Range(mapValues[1], mapValues[1] + mapValues[2] - 1),
                    new Range(mapValues[0], mapValues[0] + mapValues[2] - 1)
                    );
            maps.Add(new MapEntry(level, map));
            ++i;
        }
    }
}

long result = long.MaxValue;
for (int i = 0; i < seeds.Count; i += 2)
{
    var seedRange = new Range(seeds[i], seeds[i] + seeds[i + 1] - 1);
    var seedResult = GetMinValueForRange(seedRange, maps, 0, 0, maps[^1].Level);
    result = Math.Min(result, seedResult);
}

File.WriteAllText("../../../../output/out_second.txt", result.ToString());

long GetMinValueForRange(Range range, List<MapEntry> maps, int level, int mapIdx, int maxLevel)
{
    if (level > maxLevel || mapIdx >= maps.Count)
    {
        return range.Begin;
    }
    var mapEntry = maps[mapIdx];
    if (mapEntry.Level != level)
    {
        return GetMinValueForRange(range, maps, level, mapIdx + 1, maxLevel);
    }

    var lastEntryInLevel = mapIdx == maps.Count - 1 || maps[mapIdx + 1].Level > maps[mapIdx].Level;
    var newMissLevel = level;
    if (lastEntryInLevel)
    {
        ++newMissLevel;
    }
    var newHitLevel = level + 1;

    var intersection = GetIntersection(range, mapEntry.Map.Source);
    if (intersection.Begin > intersection.End)
    {
        return GetMinValueForRange(range, maps, newMissLevel, mapIdx + 1, maxLevel);
    }

    long leftSide = long.MaxValue;
    long rightSide = long.MaxValue;
    long intersectionSide = long.MaxValue;
    if (intersection.Begin != range.Begin)
    {
        leftSide = GetMinValueForRange(new Range(range.Begin, intersection.Begin - 1), maps, newMissLevel, mapIdx + 1, maxLevel);
    }
    if (intersection.End != range.End)
    {
        rightSide = GetMinValueForRange(new Range(intersection.End + 1, range.End), maps, newMissLevel, mapIdx + 1, maxLevel);
    }
    var map = mapEntry.Map;
    var newRangeStart = map.Target.Begin + (intersection.Begin - map.Source.Begin);
    var newRangeEnd = newRangeStart + (intersection.End - intersection.Begin);
    intersectionSide = GetMinValueForRange(new Range(newRangeStart, newRangeEnd), maps, newHitLevel, mapIdx + 1, maxLevel);

    return Math.Min(leftSide, Math.Min(intersectionSide, rightSide));
}

Range GetIntersection(Range a, Range b)
{
    var begin = Math.Max(a.Begin, b.Begin);
    var end = Math.Min(a.End, b.End);

    return new Range(begin, end);
}

readonly struct Map(Range Source, Range Target)
{
    public readonly Range Source = Source;
    public readonly Range Target = Target;
}

record struct MapEntry(int Level, Map Map);